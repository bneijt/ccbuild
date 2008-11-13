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



#include "SourceScanner.ih"
void SourceScanner::includes(std::vector < std::string > *local,
			      std::vector < std::string > *global, std::vector < std::string > *ignore)
{
  local->resize(d_locals.size());
  copy(d_locals.begin(), d_locals.end(), local->begin());
  
  global->resize(d_globals.size());
 	copy(d_globals.begin(), d_globals.end(), global->begin());
 	
	//If exists: Resize Write
	if(ignore)
	{
	  ignore->resize(d_ignore.size());
  	copy(d_ignore.begin(), d_ignore.end(), ignore->begin());
  }
  
}
