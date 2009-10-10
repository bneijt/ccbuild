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



#include "system.ih"

std::string System::projectName()
{
	//Find out the project name:
	//1) This directory, if it's not src.
	std::string d = FileSystem::fileName(FileSystem::cwd());

	//2) The directory above this one.
	if(d == "src")
		d = FileSystem::fileName(FileSystem::cleanPath(FileSystem::cwd() + "/.."));

	//TODO Strip any version number
	// Any single occuring _ or - might be the seperator
	// The last of these is the seperation point
	// The version number has at least one point
	return d;
}
