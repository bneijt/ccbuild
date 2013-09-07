/*
  This file is part of ccbuild.

  ccbuild is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  ccbuild is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with ccbuild.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "system.ih"

#define CATCH_AND_SHOW_AND_INC_ERRORS catch(const bneijt::Problem &p) \
{ \
  cerrLock.set(); \
    cerr << "ccbuild: Problem " << p.id() << ": " << p.what() << "\n"; \
    cerrLock.unset(); \
    ++errors; \
} \
catch(const std::exception &e) \
{ \
  cerrLock.set(); \
  cerr << "Caught std::exception (" << typeid(e).name() << "): " << e.what(); \
  cerr << "\nPlease report this as a bug.\n"; \
  cerrLock.unset(); \
    ++errors; \
}


namespace {
bool byMTime(Source const *a, Source const *b) {
    return FileSystem::modTime(a->filename()) < FileSystem::modTime(b->filename());
}
bool sourceIsBinaryTarget(Source const *src) {
    return src->isBinTarget();
}
}// Anon namespace


void System::build(Source *source) {
    Compiler cc;
    build(source, cc);
}

void System::build(Source *source, Compiler &cc) {
    if(!source->hasSourceExtension() and !Options::noWarn) {
        cerr << "Warning: main source file \""<< source->filename() << "\" does not have a known source extension.\n"
             << "\tBut I'll try to parse it because you want me to." << endl;
    }

    bool needLink = Options::defaultUpdate || forceLink;

    vector<Source *> srcList, objectTargets, localHeaders, internalHeaders;

    srcList.push_back(source);
    collectTargets(srcList); //Recursive search for all sources we need

    //Remove any of the sources that are binTargets because they would introduce a second main at link time
    std::vector<Source *>::iterator last = remove_if(srcList.begin(), srcList.end(), sourceIsBinaryTarget); //I want lambda functions... I want lambda functions..
    srcList.erase(last, srcList.end());//TODO do a real check for memory leaks on this, but I think Sources will track this.
    srcList.push_back(source);//Add the root binTarget again

    //Seperate sources into lists
    __foreach(src, srcList) {
        if((*src)->isObjectTarget()) {
            objectTargets.push_back(*src);
        } else if((*src)->isInternalHeader()) {
            internalHeaders.push_back(*src);
        } else if((*src)->isHeader()) {
            localHeaders.push_back(*src);
        }
        //TODO: Maybe use a target identifier bitset (can be both object and main) and a switch
    }
    srcList.clear();


    if(Options::precompile) {
        //Also do local headers
        //It is not possible to stupidly multi-process this, because these headers
        //  depend on each other (or may depend on each other), there will be a
        //  race condition with half completed gchs being used by other precompilations.
        //This will only slow the build down if the source tree uses internal headers already
        if(Options::precompileAll)
            __foreach(src, localHeaders) {
            _debugLevel4("Precompiling: " << (*src)->filename());
            (*src)->build(cc);
            cc.rmCompileOptions();
        }

        //Precompile all internal headers.
        //  We can do multi-processing here as none of the internal headers should depend on other internal headers.
        vector<Compiler> compilers(internalHeaders.size(), cc);
        size_t errors(0);
#ifdef _OPENMP
        #pragma omp parallel for
#endif
        for(vector<Source *>::size_type i = 0; i < internalHeaders.size(); ++i) {
            if(errors) {
                continue;
            }
            try {
                internalHeaders[i]->build(compilers[i]);
            }
            CATCH_AND_SHOW_AND_INC_ERRORS;
        }

        if(errors) {
            throw Problem(Problem::Subfailure, "Bail out during pre-compilation");
        }

        //The compiler does not need to be influenced here, so we can just destroy the compilers list
    } else {
        //If we don't precompile, make sure we remove any precompiled headers in our tree
        //This will slow down the total build process... so maybe we shouldn't???
        //However, having a broken build is even worse then anything else, YES??
        //Whahaha... I say it IS.
        __foreach(src, localHeaders)
        FileSystem::rmIfExists((*src)->outputFilename());

        __foreach(src, internalHeaders)
        FileSystem::rmIfExists((*src)->outputFilename());
    }

    //Sort objects by mtime
    sort(objectTargets.rbegin(), objectTargets.rend(), byMTime);

    //Add new option to clobber the compiler: place as many .cc files as possible and use --save-temps to store them in /tmp/tempdir
    // Then collect the .o files into the normal ccbuild structure
    //  This does not allow for multi-processing and is not handy when it comes to small updates
    //  in /tmp/tempdir run: g++ -Wl,--version -save-temps ~/program/ccbuild/src/fileSystem/*.cc
    //  and then collect the o files from /tmp/tempdir
    if(Options::batch) {
        //Batch compile objects that need update
        vector<Source const*> batchList;
        set<std::string> baseNames;
        __foreach(src, objectTargets)
        if(!(*src)->upToDate()) {
            //Don't allow files of the same basename into the batch
            std::string unique = (*src)->basenameWithoutExtension();
            if(baseNames.count(unique)) {
                continue;
            }
            baseNames.insert(unique);
            batchList.push_back(*src);
        }
        //Batch compile the given batch of objects
        batchCompile(batchList, cc);
    }

    //Build the objects and add them as links to the compiler
    {
        //Encaps iterator
        //GOD I WANT OpenMP 3 to be here already! F the single-nowait trick, back to index...
        vector<Compiler> compilers(objectTargets.size(), cc);
        size_t numNeedLink = 0;
        size_t errors = 0;
#ifdef _OPENMP
        #pragma omp parallel for
#endif
        for(vector<Source *>::size_type i = 0; i < objectTargets.size(); ++i) {
            if(errors) {
                continue;
            }

            //_debugLevel4("Building: " << (*src)->filename());
            if(!objectTargets[i]->upToDate()) {
                ++numNeedLink;
            }

            try {
                objectTargets[i]->build(compilers[i]);
            }
            CATCH_AND_SHOW_AND_INC_ERRORS;
        }

        if(errors) {
            throw Problem(Problem::Subfailure, "Bail out during compilation");
        }

        //Test whether linking is needed
        needLink = (numNeedLink > 0 ? true : needLink);

        //Acuumulate the compilers
        cc = accumulate(compilers.begin(), compilers.end(), cc);

    }//encaps iter
    //Build the binTarget object if needed
    needLink = (source->upToDate() ? needLink : true);



    //Re-link if any object is newer then the link target
    string outputFilename = FileSystem::cleanPath(source->directory() + "/" + source->basenameWithoutExtension());
    if(! FileSystem::fileExists(outputFilename)) {
        needLink = true;
    }

    if(needLink) {
        forceLink = true;   //Force linking of other builds
        if(Options::interAr) {
            //Archive, clear object, add archive, links
            FileSystem::ensureDirectory(Options::cacheRoot);
            std::string arName( Options::cacheRoot + "/" + FileSystem::absolutePath(source->filename()).substr(1) + ".a");
            cc.ar(arName);
            cc.rmObjects();

            //Add archive as object to compiler
            cc.addObject(arName);
        }

        cc.link(source->directory(), outputFilename);
    } else {
        cerrLock.set();
        if(Options::clearPerCommand) {
            cerr << "\33[H\33[2J";
        }
        cerr << "[DONE]\t" << source->filename() << "\n";
        cerrLock.unset();
    }
}
