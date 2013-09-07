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

#include "MD5Info.ih"

void MD5Info::save(std::string const &filename, std::string const &hash) {

    //Save information out of current
    std::string hashFilename = hashFilenameFor(filename);
    _debugLevel2("Saving hash information to disk for " << filename << "\n\tto " << hashFilename);

    d_oldLock.set();
    d_old[filename] = hash;
    d_oldLock.unset();


    //Ensure directory
    FileSystem::ensureDirectory(FileSystem::directoryName(hashFilename));

    //Open and write file
    std::ofstream file(hashFilename.c_str(), ios::trunc);

    if(!file.is_open()) {
        cerr << "ccbuild: Warning: Unable to write MD5 info to '" << hashFilename << "'.\n";
        return;
    }

    file << hash << "\n";
    file.close();
}

