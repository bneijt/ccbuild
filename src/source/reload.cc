/*
  This file is part of ccbuild.
  Copyright (C) 2013  A. Bram Neijt <bneijt@gmail.com>

  ccbuild is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  ccbuild is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with ccbuild.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "source.ih"

bool Source::reload()
{
  OpenMP::ScopedLock slock(d_apiLock);
  d_inoDev = make_pair(0,0);
  d_depsDone = false;
  d_hasMainFunction = false;
  
  /* Filename has not changed, so not
  d_srcType = Unknown;

  d_filename = FileSystem::cleanPath(d_filename);
  setType();
  */
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
