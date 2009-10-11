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


void MD5Hash::fromHex(std::string const &word)
{
	d_loaded = true;
	if(word.size() < 32)
	{
		_debugLevel2("Failed '" << word << "'");
		clear();
		return;
	}
	_debugLevel4("Load from '" << word << "'");
	for(unsigned i = 0; i < d_size; ++i)
	{
		d_hash[i] = 16 * hex(word[i*2]);
		d_hash[i] += hex(word[(i*2)+1]);
	}
	_debugLevel4("Got  " << *this);
}
