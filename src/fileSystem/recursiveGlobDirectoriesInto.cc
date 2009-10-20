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

#include "fileSystem.ih"


void FileSystem::recursiveGlobDirectoriesInto(vector<string> *list, string const &directory)
{
	stack<string> directoryStack;
	directoryStack.push(directory);
	set<string> directories;

	while(directoryStack.size() > 0)
	{
		vector<string> list;
		string dir = directoryStack.top();
		directoryStack.pop();

		FileSystem::globDirectoriesInto(&list, dir + "/*");
		__foreach(d, list)
			if(!directories.count(*d))
				directoryStack.push(*d);
				
		directories.insert(dir);
	}
	
	copy(directories.begin(), directories.end(), back_inserter(*list));
}
