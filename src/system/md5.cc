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
void System::md5(Source *source) {
    vector<Source *> srcList;
    srcList.push_back(source);
    collectTargets(srcList);
    MD5Info &md5i = MD5Info::getInstance();
    __foreach(src, srcList) {
        cout << md5i.contentHash((*src)->filename()) << "  " << (*src)->filename() << "\n";
    }
}

void System::md5() {
    vector<string> files;

    Sources &s = Sources::getInstance();

    FileSystem::globSourceFilesInto(&files, ".");

    __foreach(file, files) {
        Source *target = s[*file];

        //Error loading source??
        if(target == 0) {
            cerr << "Error loading '" << *file << "'\n";
            continue;
        }

        System::inspect(target);

        //isBinTarget test can only be done after the inspect
        if(!target->isBinTarget()) {
            continue;
        }
        cerr << "[md5 " << target->filename() << "]\n";
        System::md5(target);
    }
}
