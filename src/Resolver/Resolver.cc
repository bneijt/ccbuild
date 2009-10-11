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






#include "Resolver.ih"

Resolver::Resolver()
  :
  d_staticLinks(),
  d_empty("")
{
	//Load commandline given extra resolution files
	__foreach(xr, Options::extraResolutions)
		loadIfExists(*xr, true);//Load if exists, reporting errors

	//Load default
	//Try hostname dependent, try system name, try architecture dependent, try default
	loadIfExists("./ccResolutions."+ System::uname('n'))
	  || loadIfExists("./ccResolutions."+System::uname('s'))
	  || loadIfExists("./ccResolutions."+System::uname('m'))
	  || loadIfExists("./ccResolutions");


	//Load global resolution files
	if(Options::loadGlobalRes)
	{
		_debugLevel3("Loading global resolution files");
		loadIfExists(expand("~/.ccbuild/ccResolutions"));

		//The ccResolutions directory
		vector<string> files;

		FileSystem::globFilesInto(&files, "~/.ccbuild/ccResolutions.d/*", true);

		__foreach(file, files)
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
	
	__foreach(link, d_staticLinks)
			pointers.insert((*link).second);

	pointers.erase(&d_empty);
	
	__foreach(pointer, pointers)
		delete (*pointer);
	
}
