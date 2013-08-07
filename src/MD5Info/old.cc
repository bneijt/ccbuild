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

#include "MD5Info.ih"

std::string const &MD5Info::old(std::string const &filename)
{
  d_oldLock.set();
	bool available = (d_old.count(filename) > 0);
  d_oldLock.unset();
	//Try to load it from disk
	if(not available)
  	load(filename);
	
  OpenMP::ScopedLock lock(d_oldLock);
  _debugLevel3("Found old content hash: " << d_old[filename]);
	return d_old[filename];
}
