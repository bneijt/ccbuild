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

bool Source::reload()
{
  d_inoDev = make_pair(0,0);
  d_depsDone = false;
  d_hasMainFunction = false;
  d_done =false;
  d_srcType = Unknown;

  d_filename = FileSystem::cleanPath(d_filename);
  
 	struct stat a;

 	if(stat(d_filename.c_str(), &a) == 0)
 	{
		d_inoDev.first = a.st_dev;
		d_inoDev.second = a.st_ino;
		d_modTime = a.st_mtime;

	}
	
	//Clear vectors
	d_deps.clear();
	d_globalDeps.clear();
	return d_inoDev != InodeDevPair(0,0);
}
