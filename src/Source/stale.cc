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


#include "Source.ih"

bool Source::stale()
{
	if(!FileSystem::fileExists(filename()))
		return true;

	if(Options::md5)
		return changed();

	return d_modTime == 0 || d_modTime != FileSystem::modTime(filename());
}
