/*
  ccbuild - A strict developer's build utility
  Copyright (C) 2008  A. Bram Neijt <bneijt@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/



#include "MD5Info.ih"

void MD5Info::load(std::string const &filename)
{

	//Load a configuration file if it exists
	string confFile = hashFilenameFor(filename);
	
  ifstream file(confFile.c_str());
  _debugLevel1("Loading: '" << confFile << "'");
	

  if(!file.is_open())
  {
  	_debugLevel1("Unable to open: '" << confFile << "'");
  	return;
  }

  while(true)
  {
  	//TODO Optimize or extend with extra options
   	string line;
   	string hashInfo;
		
    getline(file, line);
    if(file.eof())
			break;

		//Try the next line if there aren't enough characters
		if(line.size() < 32)
			continue;
		
		hashInfo = line;

    _debugLevel4("Recall: " << hashInfo << " for '" << filename << "'");
    d_old[filename] = hashInfo;
  }

  file.close();
}
