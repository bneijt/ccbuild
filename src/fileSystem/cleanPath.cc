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
std::string FileSystem::cleanPath(string const &filename) {
    //TODO Use a standard function for this, I might overlook something here
    //Strip filename of excess ../ parts
    _debugLevel2("Clean path from: " << filename);
    istringstream f(filename);
    size_t partNum = 0;
    vector<string> path;
    //Split path into parts
    while(true) {
        string part;
        getline(f, part, '/');
        ++partNum;
        if(!f) {
            break;
        }

        //Double slash lower in the path is ignored ("//" or "/hello//something")
        //  but we can not ignore the first empty part, so we keep partNum as a reference
        if(part.empty() && partNum != 1) {
            continue;
        }

        //Skip pushing a single .
        if(part == ".") {
            continue;
        }

        //If it's .. , then pop the last pushed part if that part is not '..'
        if(part == ".." && path.size() > 0 && path.back() != "../") {
            _debugLevel3("Popping " << path.back() << " from path.");
            path.pop_back();
            continue;
        }

        _debugLevel4("Push " << part << "/");
        path.push_back(part + "/");
    }
    string clean = accumulate(path.begin(), path.end(), string());

    //Strip last "/" if it is not the first slash
    if(clean.size() > 1) {
        clean = clean.substr(0, clean.length() -1);
    }

    //Strip superfluous './' for local path
    if(clean[0] == '.' && clean[1] == '/') {
        clean = clean.substr(2);
    }
    //Return a single "." if we want the current path
    if(clean.empty()) {
        clean = ".";
    }
    _debugLevel2("Cleaned path to: " << clean);

    return clean;
}
