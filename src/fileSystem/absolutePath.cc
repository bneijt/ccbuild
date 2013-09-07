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

std::string FileSystem::absolutePath(std::string const &filename) {
    /*
    if file exists
      char * p = realpath(filename.c_str(), 0);
      if(not p)
        throw Problem(Problem::Unable, "Unable to create an absolute path from " + filename);
      std::string pf(p);
      delete p;
      return pf;
    */
    //If it is already absolute, return it cleaned
    if(filename[0] == '/') {
        return FileSystem::cleanPath(filename);
    }
    //It is not root yet, so make it relative to cwd and clean it.
    return FileSystem::cleanPath(FileSystem::cwd() +"/"+ filename);
}
