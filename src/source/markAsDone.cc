/*
  This file is part of ccbuild.

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

void Source::markAsDone() const
{
  //If this is not MD5, then everything should be automatic
	if(Options::md5)
	{
		MD5Info &md5i = MD5Info::getInstance();
		string collectedHash = md5i.contentHash(filename());
		
		vector<Source *> srcList;
		dependencies(srcList);
		__foreach(src, srcList)
			collectedHash += md5i.contentHash((*src)->filename());
		md5i.save(filename(), collectedHash);
	}
}
