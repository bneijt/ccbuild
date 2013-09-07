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

void System::depsFor(ostream &str) {
    vector<string> files;

    Sources &s = Sources::getInstance();

    FileSystem::globSourceFilesInto(&files, ".");

    __foreach(file, files) {
        Source *target = s[*file];

        //Error loading source??
        if(target == 0) {
            cout << "Error loading '" << *file << "'\n";
            continue;
        }

        System::depsFor(target, str);
    }
}

void System::depsFor(Source * s, ostream &str) {
    vector<Source *> srcList;
    vector<std::string const*> globalList;
    set<std::string> globalSet; //Used for verbose
    vector<std::string> ignored;
    if(Options::verbose) {
        //If verbose is given, then collect ALL targets needed for a complete compile
        //And list their global and local sources
        vector<Source *> deepList;
        deepList.push_back(s);
        collectTargets(deepList);
        //Each source has already been inspected by collectTargets
        __foreach(src, deepList) {
            //Collect additions
            (*src)->dependencies(srcList, globalList);
            (*src)->ignoredDeps(ignored);
        }

        //Create a unique set of each
        vector<Source *>::iterator srcEnd = unique(srcList.begin(), srcList.end());
        srcList.erase(srcEnd, srcList.end());
        __foreach(gl, globalList)
        globalSet.insert(**gl);//Insert string value
        globalList.clear();
        __foreach(gl, globalSet)
        globalList.push_back(&(*gl)); //Insert pointers to set values
    } else {
        System::inspect(s);
        s->dependencies(srcList, globalList);
        s->ignoredDeps(ignored);
    }

    __foreach(src, srcList) {
        //Local headers
        if((*src)->isLocalHeader()) {
            str << (*src)->filename() << " ";
        }
    }
    str << "\n";
    __foreach(src, srcList) {
        //Local source
        if((*src)->hasSourceExtension()) {
            str << (*src)->filename() << " ";
        }
    }
    str << "\n";
    //Global headers
    __foreach(src, globalList)
    str << (**src) << " ";
    str << "\n";
}
