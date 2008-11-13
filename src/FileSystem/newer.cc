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
