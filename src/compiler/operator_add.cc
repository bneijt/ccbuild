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

//See GNU manual for options: http://gcc.gnu.org/onlinedocs/gcc/Link-Options.html#Link-Options


#include "compiler.ih"
Compiler const Compiler::operator+(Compiler const &rvalue)
{
	//Adding two compilers will merge their options
	//Copying only the needed parts.
  //Keep base command: d_baseCommand(other.d_baseCommand),
	//Add objects
	__foreach(object, rvalue.d_objects)
	  if(find(d_objects.begin(), d_objects.end(), *object) == d_objects.end())
	    d_objects.push_back(*object);
	
	//Add compiler arguments
	__foreach(carg, rvalue.d_objects)
	  if(find(d_compile.begin(), d_compile.end(), *carg) == d_compile.end())
	    d_compile.push_back(*carg);
	
	//Add linking arguments
	__foreach(largument, rvalue.d_link)
	  if(find(d_link.begin(), d_link.end(), *largument) == d_link.end())
	    d_link.push_back(*largument);

	return *this;
}
