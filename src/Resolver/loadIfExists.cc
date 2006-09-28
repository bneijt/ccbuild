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
#include <iomanip>
#include "Resolver.ih"
void Resolver::loadIfExists(std::string const &confFile, bool report)
{
	//Load a configuration file if it exists
  ifstream file(confFile.c_str());
  _debugLevel1("Loading: '" << confFile << "'");
  std::vector<string> lines;
  
	map<string, string *> expandCache;
	Globals &globs = Globals::getInstance();
	
  if(!file.is_open())
  {
  	if(report)
  		cerr << "ccbuild: Unable to open: '" << confFile << "'\n";
  	return;
  }

	unsigned linenr=0;
  while(true)
  {
    string line;
   	string global, arguments;

    getline(file, line);
		++linenr;

    if(file.eof())
			break;

  	if(line.size() < 1)	//Empty lines
  		continue;

  	if(line[0] == '#')	//Comment lines
  		continue;

    //Find a seperating tab
    string::size_type i = line.find_first_of("\t");

    if(i == string::npos)
    {
    	cerr << "ccbuild: Error: Non empty configuration line " << linenr << " without tab character,\n";
    	cerr << "ccbuild: Error: in file:  '" << confFile << "'.\n";
      continue;
		}

		global = line.substr(0, i);
		arguments = line.substr(i + 1);

		System::trim(&global);
		System::trim(&arguments);
		
		string *globalPointer = globs[global];

		//Only add link if it isn't mentioned before!
		if(d_staticLinks.count(globalPointer))
			continue;
		

		//Use local expand cache
		if(expandCache.find(arguments) == expandCache.end())
			expandCache[arguments] = new string(expand(arguments));

		if(System::trimmed(*expandCache[arguments]).size() == 0 && arguments.size() > 0)
			cerr << "ccbuild: Warning: Expansion to an empty string,\nccbuild: Warning: from \"" << arguments << "\"\n";

    _debugLevel4("Link: '" << global << "' -> '" << arguments << "'");
    d_staticLinks[globalPointer] = expandCache[arguments];
  }

  file.close();
  
	//Clean up expand cache??
	//NO The pointer part is stored in d_staticLinks
	// and will be deleted when the Resolver is destroyed.
}