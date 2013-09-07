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

#include "fileSystem.ih"

bool FileSystem::rmDirectoryIfExists(std::string const &dir) {
    if(! FileSystem::fileExists(dir)) {
        return false;
    }

    cerrLock.set();
    cerr << "[RMDIR] " << dir << "\n";
    cerrLock.unset();

    fsLock.set();
    int retValue = rmdir(dir.c_str());
    fsLock.unset();
    if(retValue != 0 && FileSystem::fileExists(dir)) {
        cerrLock.set();
        cerr << "Non zero exit status for rmdir: status " << retValue << "\n";
        cerr << "    could not remove: " << dir << "\n";
        cerrLock.unset();
        return false;
    }
    return true;
}
