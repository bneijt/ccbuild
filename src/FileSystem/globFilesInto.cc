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




#include "FileSystem.ih"

//Using the path given, add all globstring results to the string vector list
namespace {

bool notFile(string target)
{
	//Return true if the string doesn't point to a normal file
	struct stat statbuf;
	if(stat(target.c_str(), &statbuf) == 0)
		if(S_ISREG(statbuf.st_mode)) //Returns true if the statbuf denotes a regular file
			return false;
	_debugLevel4("NOT regular file: '" << target << "'");
	return true;
}
}//anon namespace

void FileSystem::globFilesInto(vector<string> *list, string const &pattern, bool sort)
{
	globInto(list, pattern, sort);
	_debugLevel3("Globbging '" << pattern << "' matches " << list->size());

	//Remove the not regular file entries that were added
	vector<string>::iterator endOfFiles = remove_if(list->begin(), list->end(), notFile);

	//Delete the elements
	list->erase(endOfFiles, list->end());
}
