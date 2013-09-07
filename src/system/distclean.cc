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

bool leaveDirectory(std::string const &rvalue) {
    if(rvalue.size() < 2) {
        return true;
    }
    return rvalue.compare(rvalue.size() -2, 2, "/o") != 0;
}

bool stringLength(std::string const &a, std::string const &b) {
    return a.size() < b.size();
}

void recursivelyRemoveGCH() {
    //Clean everything
    stack<string> directoryStack;
    directoryStack.push(".");
    vector<string> rmList;

    //TODO: Rewrite to rm -rf o (but smarter) and the old rm */*/*.gch

    //Generate a list of directories
    while(directoryStack.size() > 0) {
        vector<string> list;
        string dir = directoryStack.top();
        directoryStack.pop();

        FileSystem::globDirectoriesInto(&list, dir + "/*");
        __foreach(d, list)
        if(find(rmList.begin(), rmList.end(), *d) == rmList.end()) {
            directoryStack.push(*d);
        }

        //Clear local files out of the directory
        vector<string> fileList;
        FileSystem::globFilesInto(&fileList, dir + "/*.gch");

        __foreach(target, fileList) {
            cerr << "[RM] '" << *target << "'\n";
            if(unlink((*target).c_str()) != 0) {
                cerr << "[RM] failed on '" << *target << "'\n";
            }
        }
    }

}
}

void System::distclean() {
    //Remove all GCH files
    recursivelyRemoveGCH();

    //Remove archives
    {
        vector<string> fileList;
        FileSystem::globFilesInto(&fileList, Options::cacheRoot + "/*.a");
        __foreach(target, fileList)
        FileSystem::rmIfExists(*target);
    }

    //Clean everything else in the O directory
    stack<string> directoryStack;
    directoryStack.push(Options::cacheRoot);
    vector<string> rmList;
    vector<string> directoryDeathList;

    //Generate a list of directories
    while(directoryStack.size() > 0) {
        vector<string> list;
        string dir = directoryStack.top();
        directoryStack.pop();

        FileSystem::globDirectoriesInto(&list, dir + "/*");
        __foreach(d, list)
        if(find(rmList.begin(), rmList.end(), *d) == rmList.end()) {
            directoryStack.push(*d);
        }

        //Clear local files out of the directory
        vector<string> fileList;

        //All *.md5 and *.o
        FileSystem::globFilesInto(&fileList, dir + "/*.md5");
        FileSystem::globFilesInto(&fileList, dir + "/*.o");

        __foreach(target, fileList)
        FileSystem::rmIfExists(*target);
        directoryDeathList.push_back(dir);

    }
    vector<string>::iterator end = unique(directoryDeathList.begin(), directoryDeathList.end());
    directoryDeathList.erase(end, directoryDeathList.end());
    sort(directoryDeathList.rbegin(), directoryDeathList.rend(), stringLength);

    __foreach(dir, directoryDeathList) {
        //Remove if directory, will only work when empty
        FileSystem::rmDirectoryIfExists(*dir);
    }
}
