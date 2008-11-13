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


//Globals map singleton. There to make sure globals only have one pointer to their name

#ifndef _Globals_H_INCLUDED_
#define _Globals_H_INCLUDED_
#include <sys/types.h>
#include <string>
#include <map>

namespace bneijt
{

///\brief Globals singleton. List of all loaded Globals
///
class Globals
{
		static Globals *s_instance;	///<Static pointer to the instance
    std::map<std::string, std::string *> d_map;
	public:
		///\brief Get the instance of the Globals class
		static Globals &getInstance();

		///\brief Destroy the instance
		static void destroy();
		
		///\brief Overwrite the index operator of map
		std::string * const operator[](std::string const &global);
		
		std::map<std::string, std::string *>::iterator begin()
		{
		  return d_map.begin();
		}

		std::map<std::string, std::string *>::iterator end()
		{
		  return d_map.end();
		}
		
	private:
		Globals();
		~Globals();

		///\brief Not implemented
		Globals(Globals const &other);						//NI

		///\brief Not implemented
		Globals &operator=(Globals const &other);	//NI
};
}//namespace

#endif
