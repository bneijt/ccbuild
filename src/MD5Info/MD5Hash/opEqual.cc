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






#include "MD5Hash.ih"

bool const MD5Hash::operator==(MD5Hash const &rvalue) const
{
	//No hash can be equal to an unloaded hash, except for two
	//unloaded hashes
	if(!d_loaded xor !rvalue.isLoaded())
		return false;
	
	for(unsigned i=0; i < d_size; ++i)
		if(rvalue.d_hash[i] != d_hash[i])
			return false;
	return true;
}
