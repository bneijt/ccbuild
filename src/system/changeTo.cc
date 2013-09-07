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

bool System::changeTo(string const &targetpath) {
    string path = trimmed(targetpath);
    if(chdir(path.c_str()) != 0) {
        cerr << "ccbuild: Error: Unable to change to '" << path << "'\n";
        return false;
    }
    cerr << "Entering '" << path << "'\n";
    return true;
}

