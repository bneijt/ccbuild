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



#include "System.ih"

namespace{

bool leaveDirectory(std::string const &rvalue)
{
	if(rvalue.size() < 2)
		return true;
	return rvalue.compare(rvalue.size() -2, 2, "/o") != 0;
}
}

void System::distclean()
{
	//Clean everything
	stack<string> directoryStack;
	directoryStack.push(".");
	vector<string> rmList;
	
	//TODO: Rewrite to rm -rf o (but smarter) and the old rm */*/*.gch
	
	//Generate a list of directories
	while(directoryStack.size() > 0)
	{
		vector<string> list;
		string dir = directoryStack.top();
		directoryStack.pop();

		FileSystem::globDirectoriesInto(&list, dir + "/*");
		_foreach(d, list)
			if(find(rmList.begin(), rmList.end(), *d) == rmList.end())
				directoryStack.push(*d);

		//Clear local files out of the directory
		vector<string> fileList;
		FileSystem::globFilesInto(&fileList, dir + "/*.gch");

		//All /o/*.md5 and /o/*.o
		FileSystem::globFilesInto(&fileList, dir + "/o/*.md5");
		FileSystem::globFilesInto(&fileList, dir + "/o/*.o");
		FileSystem::globFilesInto(&fileList, dir + "/o/*.rpo");
		
		_foreach(target, fileList)
		{
			cerr << "[RM] '" << *target << "'\n";
			if(unlink((*target).c_str()) != 0)
				cerr << "[RM] failed on '" << *target << "'\n";
		}
		
		//Remove if it's an 'o' directory.
		if(! leaveDirectory(dir))
		{
			cerr << "[RMDIR] " << dir << "\n";
			if(rmdir((dir).c_str()) != 0)
				cerr << "ccbuild: rmdir failed on '" << dir << "'\n";
		}
	}

}
