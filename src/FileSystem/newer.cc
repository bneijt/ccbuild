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

#include "FileSystem.ih"
bool FileSystem::newer(string const &file1, string const &file2)
{
  struct stat stat1, stat2;
  if(stat(file1.c_str(), &stat1) != 0)
    return false;
  if(stat(file2.c_str(), &stat2) != 0)
    return false;
  return stat1.st_mtime > stat2.st_mtime;
}
