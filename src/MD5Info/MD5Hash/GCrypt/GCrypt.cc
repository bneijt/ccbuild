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

GCrypt::GCrypt(int algo)
	:
	d_value(),
	d_hash(0),
	d_raw(0),
	d_algo(algo)
{
	gcry_md_open(&d_hash, d_algo, 0);
	assert(gcry_md_is_enabled(d_hash, d_algo));
	d_raw = new unsigned char[size()];
}

GCrypt::GCrypt(const bneijt::GCrypt& o)
	:
	d_value(),
	d_hash(0),
	d_raw(0),
	d_algo(o.d_algo)
{
  gcry_md_copy(&d_hash, o.d_hash);
	d_raw = new unsigned char[o.size()];
	o.rawInto(d_raw);
}

GCrypt::~GCrypt()
{
	gcry_md_close(d_hash);
	delete[] d_raw;
}
