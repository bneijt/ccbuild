/*
	ccbuild - A strict developer's build utility
	Copyright (C) 2005  A. Bram Neijt <bneijt@gmail.com>

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; version 2
	of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef _Problem_HH_INCLUDED_
#define	_Problem_HH_INCLUDED_

#include <string>

namespace bneijt
{

class Problem: public std::exception
{
		int d_stat;
		std::string d_msg;

		
	public:
		enum Id
		{
			Subfailure = 1,		///<Subprocess failure: return code nonzero
			Suberror,					///<Subprocess error: non normal exit
			Missing,					///<Anything which is missing
			Unknown,					///<Anything which is unknown and thus a problem
			Unable,					  ///<Anything which is just not doable and thus a problem
		};

		/** \brief Internal problem exception
		\param id The Id of the given problem, should be used as the return status of the program.
		\param message The human readable version of the problem.
		\param status If available the status of the subprocess or subfunction.
		*/
		Problem(Id id, std::string const &message, int status = 0) throw();
		
		~Problem() throw()
		{}
		
		char const *what() const throw()
		{
			return d_msg.c_str();
		}
		
		unsigned stat() const throw()
		{
			return d_stat;
		}

		unsigned id() const throw()
		{
			return d_id;
		}
		
	private:
		Id d_id;
};

}//namespace
#endif

