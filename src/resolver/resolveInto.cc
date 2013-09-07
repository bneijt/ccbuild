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
bool Resolver::resolveInto(std::string const *include, Compiler & cc, bool quiet) const {
    string argument = resolve(include);

    //TODO: use exceptions??
    if(argument == "FAIL") {
        if(not Options::noWarn)
            if(! quiet) {
                cerr << "ccbuild: Unable to resolve: \"" << *include << "\"\n";
            }
        return false;
    }
    if(argument.size() > 0) {
        cc.addArgument(argument);
    }
    return true;
}
