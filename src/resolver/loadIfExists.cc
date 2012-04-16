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

#include "resolver.ih"
bool Resolver::loadIfExists(std::string const &confFile, bool report)
{

	//Load a configuration file if it exists
  ifstream file(confFile.c_str());
  _debugLevel1("Loading: '" << confFile << "'");
  std::vector<string> lines;
  
	map<string, string *> expandCache;
	Globals &globs = Globals::getInstance();
	
  if(!file.is_open())
  {
  	_debugLevel1("Unable to open: " << confFile);
  	if(report)
  		cerr << "ccbuild: Unable to open: '" << confFile << "'\n";
  	return false;
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

    if(i == string::npos) //Try to recover with a space seperation
	    i = line.find_first_of(" ");

		global = line.substr(0, i);

		arguments = "";
		if(i != string::npos)
  		arguments = line.substr(i + 1);

		System::trim(&global);
		System::trim(&arguments);
		
		string const *globalPointer = globs[global];

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

  if(Options::verbose)
    cerr << "Loaded resolutions file: " << confFile << "\n";


	//Clean up expand cache??
	//NO The pointer part is stored in d_staticLinks
	// and will be deleted when the Resolver is destroyed.
	return true;
}
