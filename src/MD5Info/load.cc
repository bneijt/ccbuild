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

#include "MD5Info.ih"

void MD5Info::load(std::string const &filename)
{

	//Load a configuration file if it exists
	std::string const confFile = hashFilenameFor(filename);
	
  ifstream file(confFile);
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
    d_oldLock.set();
    d_old[filename] = hashInfo;
    d_oldLock.unset();
  }

  file.close();
  
}
