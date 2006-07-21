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

void FileSystem::globInto(vector<string> *list, string const &pattern, bool sort)
{

	glob_t globbuf;	//Needs to be globfreed at the end

	//Use glob to get canditates
	if(sort)
		::glob(pattern.c_str(), GLOB_TILDE, NULL, &globbuf);
	else
		::glob(pattern.c_str(), GLOB_TILDE | GLOB_NOSORT, NULL, &globbuf);
	

	//Copy all the matches
	copy(&globbuf.gl_pathv[0],
			 &globbuf.gl_pathv[globbuf.gl_pathc],
			 back_inserter(*list)
			 );

	//Cleanup
	globfree(&globbuf);
}
