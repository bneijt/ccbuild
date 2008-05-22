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

#include "Resolver.ih"
bool Resolver::resolveInto(std::string *include, Compiler & cc, bool quiet) const
{
  string argument = resolve(include);

  //TODO: use exceptions??
  if(argument == "FAIL")
  {
    if(not Options::noWarn)
  	  if(! quiet)
	  	  cerr << "ccbuild: Unable to resolve: \"" << *include << "\"\n";
    return false;
  }
  if(argument.size() > 0)
    cc.addArgument(argument);
  return true;
}
