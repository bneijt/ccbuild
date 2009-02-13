/*
  ccbuild - A strict developer's build utility
  Copyright (C) 2008  A. Bram Neijt <bneijt@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "System.ih"
 
/** Get information from host 
      #include <sys/utsname.h>
      
      Field is a character which is the same as uname:
      'm' == `uname -m`
      'n' == `uname -n`
*/
std::string System::uname(char const field)
{
  std::string rvalue;
  utsname sysinfo;
  if(::uname(&sysinfo) == 0)
  {
    switch(field)
    {
      case 'm':
        rvalue = sysinfo.machine;
        break;
      case 'n':
        rvalue = sysinfo.nodename;
        break;
      default:
        throw Problem(Problem::Unable, "Not implemented field requisted from uname.");
    }
  }
  return rvalue;
}
