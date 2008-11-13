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


#ifndef _GCrypt_HH_INCLUDED_
#define	_GCrypt_HH_INCLUDED_

#include <gcrypt.h>
#include <string>

namespace bneijt
{
/** \brief Class based libgcrypt interface
Simple wrapper for a few libgcrypt functions.
*/
class GCrypt
{
		std::string d_value;
		gcry_md_hd_t d_hash;
		unsigned char *d_raw;
		int d_algo;
		
	public:
		GCrypt(int algo);
		GCrypt(const GCrypt&);
		~GCrypt();
    
		unsigned size() const
		{
			return gcry_md_get_algo_dlen(d_algo);
		}
		
		void rawInto(unsigned char *target) const
		{
			unsigned int s = size();
			for(unsigned i = 0; i < s; ++i)
				target[i] = d_raw[i];
		}
		
		void from(char const *data, unsigned len, unsigned char* key) const;
		void update(char const *bytes, unsigned numbytes);
		void finalize();
		
		std::string const &value() const;

  private:
    GCrypt& operator=(const bneijt::GCrypt&); //NI

};
}//namespace
#endif

