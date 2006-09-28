/*
	ccbuild - A strict developer's build utility
	Copyright (C) 2005  A. Bram Neijt <bneijt@gmail.com>

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "Source.ih"
bool Source::hasSourceExtension() const
{
	//Return true if this source has an  extension
	// *.cc .cp *.cxx *.cpp *.c++ *.C
	
	
  if(d_filename.size() > 1 && d_filename.substr(d_filename.size() - 2) == ".C")
  	return true;
  if(d_filename.size() > 2 && d_filename.substr(d_filename.size() - 3) == ".cc")
  	return true;
  if(d_filename.size() > 2 && d_filename.substr(d_filename.size() - 3) == ".cp")
  	return true;
  if(d_filename.size() > 3 && d_filename.substr(d_filename.size() - 4) == ".cxx")
  	return true;
  if(d_filename.size() > 3 && d_filename.substr(d_filename.size() - 4) == ".cpp")
  	return true;
  if(d_filename.size() > 3 && d_filename.substr(d_filename.size() - 4) == ".c++")
  	return true;

  return false;
}