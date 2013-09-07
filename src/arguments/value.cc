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






#include "arguments.ih"
namespace {

std::string const spaceAdd(std::string const &rvalue, std::string const &lvalue) {
    _debugLevel4("rvalue.size=" << rvalue.size() << " lvalue.size=" << lvalue.size());
    if(rvalue.size() > 0 && lvalue.size() > 0) {
        return rvalue + " " + lvalue;
    }
    return rvalue + lvalue;
}

}
std::string Arguments::value(std::string const &optionName) const {

    map<string, bool *>::const_iterator fi = d_flags.find(optionName);

    if(fi == d_flags.end()) {
        return d_empty;
    }

    map<bool *, std::vector<std::string> >::const_iterator vi = d_values.find((*fi).second);
    if(vi != d_values.end()) {
        return accumulate((*vi).second.begin(), (*vi).second.end(), string(""), spaceAdd);
    } else {
        return d_empty;
    }
}
