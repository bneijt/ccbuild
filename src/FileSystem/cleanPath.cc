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






#include "FileSystem.ih"
std::string FileSystem::cleanPath(string const &filename)
{
	//TODO Use a standard function for this, I might overlook something here
	
 	//Strip filename of excess ../ parts
 	_debugLevel2("Clean path from: " << filename);
 	istringstream f(filename);

 	vector<string> path;
	
 	while(true)
 	{
		string part;
		getline(f, part, '/');

		if(!f)
			break;
			
		//Delete the last part, before the ".." with the ".." if
		//the last pushed part isn't "."
		if(part == ".." && path.size() > 0 && path.back() != "./" && path.back() != "../")
 	  {
			if(!path.empty())
				path.pop_back();
			continue;
		}

		path.push_back(part + "/");
	}
	string clean = accumulate(path.begin(), path.end(), string());

 	//Strip last "/"
 	clean = clean.substr(0, clean.length() -1);
 	//Strip superflourous './' for local path
 if(clean[0] == '.' && clean[1] == '/')
 	  clean = clean.substr(2);
 	_debugLevel2("Clean path from: " << filename);
  _debugLevel2("Cleaned path to: " << clean);
  
  return clean;
}
