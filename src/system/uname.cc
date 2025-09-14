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

/** Get information from host
      #include <sys/utsname.h>

      Field is a character which is the same as uname:
      'm' == `uname -m`
      'n' == `uname -n`
*/
std::string System::uname(char const field) {
    std::string rvalue;
    utsname sysinfo;
    if(::uname(&sysinfo) == 0) {
        switch(field) {
        case 'm':
            rvalue = sysinfo.machine;
            break;
        case 'n':
            rvalue = sysinfo.nodename;
            break;
        case 's':
            rvalue = sysinfo.sysname;
            break;
        default:
            throw Problem(Problem::Unable, "Not implemented field requested from uname.");
        }
    }
    return rvalue;
}
