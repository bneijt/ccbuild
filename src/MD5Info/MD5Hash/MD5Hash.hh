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


//MD5Hash list singleton. There to make sure we only load MD5Hash once

#ifndef _MD5Hash_H_INCLUDED_
#define _MD5Hash_H_INCLUDED_

#include <string>
#include <fstream>

namespace bneijt
{
///\brief Simple one-run MD5 hashing class
class MD5Hash
{
		static unsigned const d_size = 16; ///<The size, in bytes, of the hash
		unsigned char d_hash[d_size];	///<The hash in bytes
		bool d_loaded;	///< Wether the hash was loaded
		
	public:
		///\brief Constructor
		MD5Hash();
		///\brief Initialize using the hash of the given string (calles from(word))
		MD5Hash(std::string const &word);

		///\brief Returns the size of the hash in bytes (16)
		unsigned const size() const
		{
			return d_size;
		}
		
		///\brief Clears the hash to an empty value.
		void clear();
		
		///\brief Returns wether the given hash is smaller then this hash..
		bool operator<(MD5Hash const &rvalue) const;
		
		///\brief Fills the hash with random values.
		void random();

		//Data readers
		///\brief Load the hash from the first 32 hex characters of the given string
		void fromHex(std::string const &word);
		///\brief Load the hash by MD5 hashing the file behind the given filename
		void from(std::string const &filename);


		///\brief Return a const pointer to the 16 bytes of hash data in memory.
		unsigned char const * hash() const;
		
		///\brief Returns wether this hash has ever been set to a value.
		bool isLoaded() const
		{
			return d_loaded;
		}
		
		///\brief Return the ith hash byte
		unsigned char const &operator[](unsigned i) const
		{
			return d_hash[i];
		};
		
		///\brief Equallity check
		bool const operator==(MD5Hash const &rvalue) const;
		
		///\brief Inverted version of the equallity check
		bool const operator!=(MD5Hash const &rvalue) const
		{
			return !((*this) == rvalue);
		}
		
		///\brief Calculate the difference
		double const operator-(MD5Hash const &rvalue) const;

	private:
		///\brief Return the hex value of a given character.
		static unsigned char hex(char c);
				
};

///\brief Extraction operator wrapper for fromHex function
std::istream &operator>>(std::istream &str, MD5Hash &h);

///\brief Insertion opterator wrapper, outputting a base 16 string representation of the hash
std::ostream &operator<<(std::ostream &str, MD5Hash const &h);

}//namespace

#endif
