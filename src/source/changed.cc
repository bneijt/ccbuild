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



#include "source.ih"
bool Source::changed()	const
{
	//Without output, we can't check. So we probably are old
	if(producesOutput() && !FileSystem::fileExists(outputFilename()))
		return true;

	//MD5 check
	if(Options::md5)
	{
		//This file has changed if the first 32 chars of it's contentHash are
		// not the same as the first 32 chars of it's stored hash.
		MD5Info &md5i = MD5Info::getInstance();
		return md5i.old(filename()).compare(0, 32, md5i.contentHash(filename())) != 0;
	}
		
	return FileSystem::newer(filename(), outputFilename());
}
bool Source::changed(std::string const &relativeToThis)	const
{
	//MD5 Checksumming system check here
	assert(Options::md5 == false);

	//Wether we create output or not, we can check our status
	//According to this "relativeToThis" output.
	return FileSystem::newer(filename(), relativeToThis);
}
