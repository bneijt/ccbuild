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

Resolver::Resolver()
{
	//Load commandline given extra resolution files
	_foreach(xr, Options::extraResolutions)
		loadIfExists(*xr, true);//Load if exists, reporting errors

	//Load default
	loadIfExists("./ccResolutions");


	//Load global resolution files
	if(Options::loadGlobalRes)
	{
		_debugLevel3("Loading global resolution files");
		loadIfExists(expand("~/.ccbuild/ccResolutions"));

		//The ccResolutions directory
		vector<string> files;

		FileSystem::globFilesInto(&files, "~/.ccbuild/ccResolutions.d/*", true);

		_foreach(file, files)
			loadIfExists(*file);
	}
	
	Globals &gl = Globals::getInstance();
	
	//ANSI C++ headers...
	static char const * const ccHeaders[] = {
			"algorithm",
  		"bitset",
  		"deque",
  		"exception",
  		"fstream",
  		"functional",
  		"iomanip",
  		"ios",
  		"iosfwd",
  		"iostream",
  		"istream",
  		"iterator",
  		"limits",
  		"list",
  		"locale",
  		"map",
  		"memory",
  		"new",
  		"numeric",
  		"ostream",
  		"queue",
  		"set",
  		"sstream",
  		"stack",
  		"stdexcept",
  		"streambuf",
  		"string",
  		"typeinfo",
  		"utility",
  		"valarray",
  		"vector",

	//C++ equivalent of ANSI C headers...
			"cassert",
			"cctype",
			"cerrno",
			"cfloat",
			"ciso646",
			"climits",
			"clocale",
			"cmath",
			"csetjmp",
			"csignal",
			"cstdarg",
			"cstddef",
			"cstdio",
			"cstdlib",
			"cstring",
			"ctime",
			"cwchar",
			"cwtype",
			0};

	for(unsigned i = 0; ccHeaders[i]; ++i)
		if(d_staticLinks.count(gl[ccHeaders[i]]) == 0)
			d_staticLinks[gl[ccHeaders[i]]] = &d_empty;

}

Resolver::~Resolver()
{
	//Todo: cleanup using unique_copy etc.
	set<std::string *> pointers;
	
	_foreach(link, d_staticLinks)
			pointers.insert((*link).second);

	pointers.erase(&d_empty);
	
	_foreach(pointer, pointers)
		delete (*pointer);
	
}