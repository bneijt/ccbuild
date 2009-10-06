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



#include "Sources.ih"

void Sources::reloadStaleSources()
{
	__foreach(src, d_sources)
	{
	 	if((*src)->stale())
	 	{
			if((*src)->reload())
				continue;

			//Reloading failed!
			_debugLevel1("Reload failed on " << (*src)->filename() << ". Cleaning up all sources.");

			cerr << "ccbuild: Source tree change. Forcing refresh.\n";

			//Forget all memory resident hashes
			MD5Info::destroy();

			//Remove the object of any binary target to ensure relinking
			__foreach(i, d_sources)
			{
				if((*i)->isBinTarget())
				{
					FileSystem::rmIfExists((*i)->outputFilename());
				}
			}
			
			//Cleanup
			//Remove all dependency knowledge because of stale pointers...
			__foreach(i, d_sources)
				delete *i;
			d_sources.clear();
			break;		
		}
	}
}
