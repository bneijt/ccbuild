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


//Sources list singleton. There to make sure we only load sources once

#ifndef _Sources_H_INCLUDED_
#define _Sources_H_INCLUDED_
#include <sys/types.h>
#include <utility>
#include <string>
#include <set>


#include "../Source/Source.hh"

namespace bneijt
{

///\brief Sources singleton. List of all loaded sources
///
class Sources
{
		std::set<Source *> d_sources;	///< A list of all loaded

		static Sources *s_instance;///< Static instance pointer


	public:
		///\brief Get the instance of the sources class
		static Sources &getInstance();

		///\brief Delete the instance
		static void destroy();

		///\brief Get the Source pointer for the given file
		Source* operator[](std::string const &filename	///<Filename of source file
			);
			
		///\brief Remove the given source from the list
		void erase(Source * src);
		
		///\brief Reload all sources which are "stale()"
		///
		///Because sources contain pointers to other sources
		/// if one source needs to be removed, all need to be remove
		///However, if it only needs to be reloaded, then we're ok.
		void reloadStaleSources();
		
		///\brief Get a vector of all currently known sources
		std::set<Source *> const &sources() const
		{
			return d_sources;
		}

	private:
		///\brief Initializer
		Sources();
		///\brief Destructor
		~Sources();

		///\brief Not implemented
		Sources(Sources const &other);						//NI



		///\brief Not implemented
		Sources &operator=(Sources const &other);	//NI
};
}//namespace

#endif
