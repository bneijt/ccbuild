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






#include "GCrypt.ih"

void GCrypt::finalize()
{
	//Finalize hash
	gcry_md_final(d_hash);
	unsigned char *digest = gcry_md_read (d_hash, d_algo);

	//Convert to hex
	std::ostringstream str("");
	for(unsigned i=0; i < gcry_md_get_algo_dlen(d_algo); ++i)
	{
		str << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(digest[i]);
		d_raw[i] = digest[i];
	}
	//Store result
	d_value = str.str();
	_debugLevel1("Finalizing hash with: " << d_value);
	gcry_md_reset(d_hash);
}
