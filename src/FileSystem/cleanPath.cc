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

#include "FileSystem.ih"
std::string FileSystem::cleanPath(string const &filename)
{
	//TODO Use a standard function for this, I might overlook something here

	
 	//Strip filename of excess ../ parts
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
		if(part == ".." && path.size() > 0 && path.back() != "./")
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

  return clean;
}
