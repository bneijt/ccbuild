/*
	This file is part of the metalink program
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



#ifndef _String_HH_INCLUDED_
#define	_String_HH_INCLUDED_

#include <string>
namespace bneijt{
class String: public std::string
{
	public:
		String()
		:
			std::string()
		{}

		String(std::string const & string)
		:
			std::string(string)
		{}
		
		String const &operator=(std::string const &s)
		{
			this->assign(s);
			return *this;
		}

		void strip()
		{
			char const * const trimstring("\x01\x02\x03\x04\x05\x06\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20");
			std::string::size_type pos = this->find_first_not_of(trimstring);
			this->erase(0, pos);
			pos = this->find_last_not_of(trimstring);
			this->erase(pos + 1);
		}
		
		bool endsIn(char const endc)
		{
			return this->size() > 1 && (*this)[this->size() -1] == endc;
		}
		bool endsIn(std::string const &ending)
		{
			return this->size() >= ending.size()
				&&  this->compare(
					this->size() - ending.size(),
					ending.size(),
					ending
					) == 0;
		}
		bool startsWith(std::string const &beginning)
		{
			return this->size() >= beginning.size()
				&&  this->compare(
					0,
					beginning.size(),
					beginning
					) == 0;
		}
		void toUpper();
		
		std::string replace(char from, char to) const;
		std::string replace(std::string const &from, std::string const &to) const;
};
}
#endif

