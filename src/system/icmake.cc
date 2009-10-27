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
#include "system.ih"
void System::icmake()
{
  vector<string> files;

  Sources &s = Sources::getInstance();

  FileSystem::globSourceFilesInto(&files, ".");

  __foreach(file, files)
  {
    Source *target = s[*file];

    //Error loading source??
    if(target == 0)
    {
      cout << "Error loading '" << *file << "'\n";
      continue;
    }


    System::inspect(target);

    if(!target->isBinTarget())
      continue;

    System::icmake(target);
  }
}

void System::icmake(Source *source)
{
	System::inspect(source);

	vector<Source *> srcList;
	srcList.push_back(source);

	collectTargets(srcList);

	//Get the directories for all the files needed by this source
  set<string> dirList;
	__foreach(src, srcList)
	{
	  //icmake only cares about the object files (no header only directories)
	  if((*src)->isObjectTarget())
  		dirList.insert((*src)->directory());
  }
  
	//Never include the local directory "."
	if(dirList.count(".") != 0)
		dirList.erase(".");
  
  //Load the CLASSES file to see which ones we already have
  if(!Options::verbose && FileSystem::fileExists("CLASSES"))
  {
    ifstream classes("CLASSES");
    if(!classes.is_open())
      cerr << "Warning: Unable to open the existing CLASSES file.\n";
    std::string c;
    while(true)
    {
      getline(classes, c);
      if(classes.eof())
        break;
      _debugLevel1("Found \"" << c << "\" in CLASSES");
      //Remove classes that have been listed already
    	if(dirList.count(c) != 0)
    	{
        _debugLevel1("Dropping \"" << c << "\"");
    		dirList.erase(c);      
      }
    }
  }

	coutLock.set();
	copy(dirList.begin(), dirList.end(), ostream_iterator<string>(cout, "\n"));
	coutLock.unset();
}


