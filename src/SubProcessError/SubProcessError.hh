/*
	ccbuild - A strict developer's build utility
	Copyright (C) 2005  A. Bram Neijt <bneijt@gmail.com>

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

//Options list singleton. There to make sure we only load Options once

#ifndef _SubProcessError_H_INCLUDED_
#define _SubProcessError_H_INCLUDED_

#include <string>


namespace bneijt
{

///\brief Subprocess error exception
class SubProcessError
{
		int d_retValue;	///<Return value
	public:
		///\brief Initialize using value
		SubProcessError(int value)	
			:
			d_retValue(value)
		{};
	
		///\brief Return the return value
		int retValue() const
		{
			return d_retValue;
		};

};
}//namespace

#endif
