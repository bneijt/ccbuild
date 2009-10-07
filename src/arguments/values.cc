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

std::vector<std::string> const &Arguments::values(std::string const &optionName) const
{

	map<string, bool *>::const_iterator fi = d_flags.find(optionName);
	
	if(fi == d_flags.end())
		return d_emptyList;
		
	map<bool *, std::vector<std::string> >::const_iterator vi = d_values.find((*fi).second);
	if(vi != d_values.end())
		return (*vi).second;
	else
		return d_emptyList;
}