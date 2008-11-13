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



#include "Source.ih"

//Non const helper brother
bool Source::upToDate()
{
	vector<Source *> srcList;
	dependencies(srcList);
	return upToDate(srcList);
}

bool Source::upToDate(vector<Source *> const &srcList) const
{
  bool needUpdate = Options::defaultUpdate;

	if(!producesOutput())
		return true;


	if(needUpdate)
		return false;
		

	if(changed())
	{
		_debugLevel2(filename() << " changed.");
		return false;
	}
	

	if(Options::md5)
	{
		//MD5 sum concatenated hash check
		//If the concatenated hash of this and it's deps changed
		//  then we are not up to date
		//TODO Optimize with halfway unequal check.
		
		MD5Info &md5i = MD5Info::getInstance();
		string collectedHash = md5i.contentHash(filename());
		
		_foreach(src, srcList)
			collectedHash += md5i.contentHash((*src)->filename());
		
		needUpdate = (collectedHash != md5i.old(filename()));
	}
	else
	{
		//Normal timestamp check system
		_foreach(src, srcList)
		{
			//General update rule: any newer dependency / changed dependency
			if((*src)->changed(outputFilename()))
			{
				_debugLevel3(filename() << " deps on changed " << (*src)->filename());
				needUpdate = true;
			}	
			if(needUpdate)
				break;
		}
	}
	
	return !needUpdate;
}
