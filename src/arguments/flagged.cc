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



#include "arguments.ih"

bool Arguments::flagged(std::string const &optionName) const
{
	//The options are there, return the value if it is (which it is, because of arguments. But we still want to be const)
	map<string, bool*>::const_iterator flag =  d_flags.find(optionName);
	if(flag != d_flags.end() && (*flag).second)
		return *((*flag).second);
	return false;
}
