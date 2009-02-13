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


#ifndef _Resolver_H_INCLUDED_
#define _Resolver_H_INCLUDED_
#include <sys/types.h>
#include <utility>
#include <string>
#include <map>

#include "../Compiler/Compiler.hh"

namespace bneijt
{

///\brief Gobal header -> compiler arguments resolver
///
///This class will do all header to compiler arguments resolution
class Resolver
{
		std::map<std::string *, std::string *> d_staticLinks; ///< Link global to argument

		std::string d_empty;	///<An empty string

		static Resolver *s_instance;///<Static pointer to the instance
	public:
		///\brief	Get the instance of the Resolver
		static Resolver &getInstance();

		///\brief	Clear the instance of the Resolver
		static void destroy();

		/**\brief Resolve this include into the given compiler
		
		 \param include A pointer to a string containing the name of the include
		 \param cc Use this compiler to store resolves
		 \param quiet Wether or not to output an error message on failure
		 \return True on success, false otherwise
		*/
		bool resolveInto(std::string *include,
										Compiler &cc,
										bool quiet = false
										) const;



		/**\brief Load a configuration file if it exists
		
			\param confFile The configuration file to load
			\param report	Wether to report errors
			\return Wether the file was loaded or not
		*/
		bool loadIfExists(std::string const &confFile, bool report = false);

		/**\brief Resolve the given include and return the commandline options
		
		\param include The global include needed.
		\return Return the resolved value for the given include or "FAIL" otherwise.
		*/
		std::string resolve(std::string const &include) const;

		///\brief This is a dangerous speed up taking an internal Globals pointer
		std::string resolve(std::string *include) const;

	private:
		

		///\brief Call the expand function on this string.
		std::string expand(std::string const &name) const;

		Resolver();
		~Resolver();

		///\brief Not implemented
		Resolver(Resolver const &other);						//NI
		///\brief Not implemented
		Resolver &operator=(Resolver const &other);	//NI
};
}//namespace

#endif
