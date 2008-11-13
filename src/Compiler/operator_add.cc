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

//See GNU manual for options: http://gcc.gnu.org/onlinedocs/gcc/Link-Options.html#Link-Options


#include "Compiler.ih"
Compiler const Compiler::operator+(Compiler const &rvalue)
{
	//Adding two compilers will merge their options
	//Copying only the needed parts.
  //Keep base command: d_baseCommand(other.d_baseCommand),
	//Add objects
	copy(rvalue.d_objects.begin(), rvalue.d_objects.end(), back_inserter(d_objects));
	//Add compiler arguments
	copy(rvalue.d_compile.begin(), rvalue.d_compile.end(), back_inserter(d_compile));
	//Add linking arguments
	copy(rvalue.d_link.begin(), rvalue.d_link.end(), back_inserter(d_link));

	return *this;
}
