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



#include "source.ih"
bool Source::isLocalHeader() const
{
	if(d_srcType != Unknown)
		return d_srcType == LocalHeader;

	//Return true if this source contains is in the local path, and it has a .hh extension
  if(d_filename.size() > 1)
    if(d_filename.substr(d_filename.size() - 2) == ".h"
  			|| d_filename.substr(d_filename.size() - 3) == ".H")
  {
  		d_srcType = LocalHeader;
    	return true;
  }
  if(d_filename.size() > 2
  	&& d_filename.substr(d_filename.size() - 3) == ".hh")
  {
  	d_srcType = LocalHeader;
    return true;
  }
  
  //It's a local header if it doesn't contain a main function
  //And can't be considered anything else by extension
	if(d_hasMainFunction || hasSourceExtension())
		return false;
	
	if(!isInternalHeader())
		d_srcType = LocalHeader;	

	return d_srcType == LocalHeader;
}
