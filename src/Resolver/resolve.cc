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
std::string Resolver::resolve(std::string const &include) const
{
  _debugLevel3("Resolving: " << include);
	Globals &globs = Globals::getInstance();
	
	//Stupid but safe!
	std::string *includePointer = globs[include];

	//Check statics
	std::map<std::string *, std::string *>::const_iterator it = d_staticLinks.find(includePointer);
	if(it != d_staticLinks.end())
			return *(*it).second;


  return "FAIL";

}

std::string Resolver::resolve(std::string *includePointer) const
{
  _debugLevel3("Resolving: " << *includePointer);

	//Check statics
	std::map<std::string *, std::string *>::const_iterator it = d_staticLinks.find(includePointer);
	if(it != d_staticLinks.end())
			return *(*it).second;

  return "FAIL";

}