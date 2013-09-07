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

#include "resolver.ih"
std::string Resolver::resolve(std::string const &include) const {
    _debugLevel3("Resolving: " << include);
    Globals &globs = Globals::getInstance();

    //Stupid but safe!
    std::string const *includePointer = globs[include];

    //Check statics
    std::map<std::string const*, std::string const*>::const_iterator it = d_staticLinks.find(includePointer);
    if(it != d_staticLinks.end()) {
        return *(*it).second;
    }

    return "FAIL";
}

std::string Resolver::resolve(std::string const *includePointer) const {
    _debugLevel3("Resolving: " << *includePointer);

    //Check statics
    std::map<std::string const*, std::string const*>::const_iterator it = d_staticLinks.find(includePointer);
    if(it != d_staticLinks.end()) {
        return *(*it).second;
    }

    return "FAIL";

}
