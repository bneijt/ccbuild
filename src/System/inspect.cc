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

#include "System.ih"
void System::inspect()
{
  vector<string> files;

  Sources &s = Sources::getInstance();

  FileSystem::globSourceFilesInto(&files, ".");

  _foreach(file, files)
  {
    Source *target = s[*file];

    //Error loading source??
    if(target == 0)
    {
      cout << "Error loading '" << *file << "'\n";
      continue;
    }

    System::inspect(target);
  }
}

void System::inspect(std::string rootSource)
{
	//Load this source
  Sources & s = Sources::getInstance();
  Source *root = s[rootSource];

  //Error loading source??
  if(root == 0)
  {
    cout << "Error loading source\n";
    return;
  }

  //Push all local and global on the stack
  //Generate source dependencies
  _debugLevel4("Calling genDeps");
  root->genDeps();
}

void System::inspect(Source * root)
{
  _debugLevel4("Calling genDeps");	//Generate source dependencies
  root->genDeps();
}
