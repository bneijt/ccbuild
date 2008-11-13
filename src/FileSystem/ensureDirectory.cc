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

void FileSystem::ensureDirectory(std::string const &directoryName)
{
		
		//Check for object directory existence (exists("o"))
	  if(!fileExists(directoryName))
		{
			//S_IRUSR    00400     owner has read permission
	    //S_IWUSR    00200     owner has write permission
	    //S_IXUSR    00100     owner has execute permission
	    cerr << "[MKDIR] " << directoryName << "\n";

	    if(!Options::simulate)
				if(mkdir(directoryName.c_str(), S_IRUSR | S_IWUSR | S_IXUSR) != 0 )
					cerr << "ccbuild: Warning: Unable to create directory \"" << directoryName << "\"\n";
		}
}
