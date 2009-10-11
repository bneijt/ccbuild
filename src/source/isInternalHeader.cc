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
bool Source::isInternalHeader() const
{
	if(d_srcType != Unknown)
		return d_srcType == InternalHeader;

	//Return true if this source has an .ih extension
  if(d_filename.size() > 2 && d_filename.compare(d_filename.size() -3 , 3, ".ih") == 0)
  	d_srcType = InternalHeader;

 	return d_srcType == InternalHeader;
}
