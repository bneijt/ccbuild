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
void System::resolveTest(Source * s, ostream &str)
{
	set<string> globals;
	resolveTest(s, &globals);
	copy(globals.begin(), globals.end(), ostream_iterator<string>(str, "\t\n"));
}

void System::resolveTest(Source * s, set<string> *globals)
{
	cerr << "ccbuild: Resolving '" << s->filename() << "'" << endl;	//Flush, to get streams
	vector<Source *> srcList, localList;
	srcList.push_back(s);
	vector<string *> globalList;
	
	Resolver const &resolver = Resolver::getInstance();
	
	collectTargets(srcList);
	__foreach(source, srcList)
	{
		(*source)->directDeps(localList, globalList);
		__foreach(gi, globalList)
			if(resolver.resolve(**gi) == "FAIL" && globals->count(**gi) == 0)
			{
				cerr << "ccbuild: Unable to resolve \"" << **gi << "\"\n";
				cerr << "ccbuild:   first found in \"" << (*source)->filename() << "\"\n";
				globals->insert(**gi);
			}
	}
}

void System::resolveTest(ostream &str)
{
	//Resolve all
  vector<string> files;

  Sources &s = Sources::getInstance();
	
  FileSystem::globSourceFilesInto(&files, ".");
	set<string> globals;
  __foreach(file, files)
  {
    Source *target = s[*file];

    //Error loading source??
    if(target == 0)
    {
      cout << "Error loading '" << *file << "'\n";
      continue;
    }

    System::resolveTest(target, &globals);
  }
	copy(globals.begin(), globals.end(), ostream_iterator<string>(str, "\t\n"));
}
