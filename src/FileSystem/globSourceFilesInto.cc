/*
   ccbuild - A strict developer's build utility

   Copyright (C) 2004 A. Bram Neijt <bneijt@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

*/


#include "FileSystem.ih"

void FileSystem::globSourceFilesInto(vector<string> *list, string const &directory)
{
	//C++ source files
	globFilesInto(list, directory + "/*.cc");
  globFilesInto(list, directory + "/*.cp");
  globFilesInto(list, directory + "/*.cxx");
  globFilesInto(list, directory + "/*.cpp");
  globFilesInto(list, directory + "/*.CPP");
  globFilesInto(list, directory + "/*.c++");
  globFilesInto(list, directory + "/*.C");

  //C source files ???
  //globFilesInto(list, directory + "/*.c");

}
