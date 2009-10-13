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

namespace {

bool sourceIsBinaryTarget(Source const *src)
{
  return src->isBinTarget();
}
}


void System::build(Source *source)
{
	Compiler cc;
	build(source, cc);
}

void System::build(Source *source, Compiler &cc)
{
  bool needLink = Options::defaultUpdate || forceLink;

  vector<Source *> srcList, objectTargets, localHeaders, internalHeaders;
  
	srcList.push_back(source);
	collectTargets(srcList); //Recursive search for all sources we need

  //Remove any of the sources that are binTargets because they would introduce a second main at link time
  auto last = remove_if(srcList.begin(), srcList.end(), sourceIsBinaryTarget);
  srcList.erase(last, srcList.end());//TODO do a real check for memory leaks on this, but I think Sources will track this.
  srcList.push_back(source);//Add the root binTarget again
  
	//Seperate sources into lists
	__foreach(src, srcList)
	{
		if((*src)->isObjectTarget())
			objectTargets.push_back(*src);
		else if((*src)->isInternalHeader())
			internalHeaders.push_back(*src);
		else if((*src)->isHeader())
			localHeaders.push_back(*src);
		//Rest are main targets, leave these out.
	}
	srcList.clear();


	if(Options::precompile)
	{
		//Also do local headers
		//This will slow the build down it the source tree uses internal headers already
		if(Options::precompileAll)
	  __foreach(src, localHeaders)
	  {
    	_debugLevel4("Precompiling: " << (*src)->filename());
      (*src)->build(cc);
      cc.rmCompileOptions();
	  }

	  //Precompile all internal headers
	  __foreach(src, internalHeaders)
	  {
    	_debugLevel4("Precompiling: " << (*src)->filename());
      (*src)->build(cc);
      cc.rmCompileOptions();
	  }
	}
	else
	{
		//If we don't precompile, make sure we remove any precompiled headers in our tree
		//This will slow down the total build process... so maybe we shouldn't???
		//However, having a broken build is even worse then anything else, YES??
		//Whahaha... I say it IS.
		__foreach(src, localHeaders)
			FileSystem::rmIfExists((*src)->outputFilename());
			
		__foreach(src, internalHeaders)
			FileSystem::rmIfExists((*src)->outputFilename());
	}

  //Build the objects and add them as links to the compiler
  {//Encaps iterator
    //GOD I WANT OpenMP 3 to be here already! F the single-nowait trick, back to index...
    vector<Compiler> compilers(objectTargets.size(), cc);
    size_t numNeedLink = 0;
    #pragma omp parallel for
    for(vector<Source *>::size_type i = 0; i < objectTargets.size(); ++i)
    {
      //_debugLevel4("Building: " << (*src)->filename());
      if(!objectTargets[i]->upToDate())
        ++numNeedLink;
      objectTargets[i]->build(compilers[i]);
      compilers[i].rmCompileOptions();
    }
    //Test whether linking is needed
    needLink = numNeedLink > 0 ? needLink : true;
    
    //Acuumulate the compilers
    cc = accumulate(compilers.begin(), compilers.end(), cc);
    
  }//encaps iter

	//Build the binTarget object if needed
  needLink = (source->upToDate()) ? needLink : true;



	//Re-link if any object is newer then the link target
	string outputFilename = FileSystem::cleanPath(source->directory() + "/" + source->basename());
	if(! FileSystem::fileExists(outputFilename))
		needLink = true;

  if(needLink)
  {
  	forceLink = true;	//Force linking of other builds
		if(! cc.objects().empty() && Options::interAr)
		{
	  	//Archive, clear object, add archive, links
  		FileSystem::ensureDirectory(source->directory() + "/o");
			cc.ar(source->directory() + "/o", source->basename() + ".ar.o");
			cc.rmObjects();
			
			//Add archive as object to compiler
  		cc.addObject(source->directory() + "/o/" + source->basename() + ".ar.o");
		}
		
    cc.link(source->directory(), outputFilename);
  }
  else
  {
    cerrLock.set();
  	if(Options::clearPerCommand)
  	  cerr << "\33[H\33[2J";
    cerr << "[DONE]\t" << source->filename() << "\n";
    cerrLock.unset();
  }
}
