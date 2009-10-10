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




#include "source.ih"

void Source::genDeps()
{
	//If we already have deps, we are done.
	if(d_depsDone)
		return;
	d_depsDone = true;
	
	Sources &sources = Sources::getInstance();

  //stack<Source *> srcStack;
  //vector<Source *> srcList;

	vector<string> localIncludes, globalDeps;
  scan(&localIncludes, &globalDeps);

	Globals &globs = Globals::getInstance();
	__foreach(globalDep, globalDeps)
		d_globalDeps.insert(globs[*globalDep]);
		
  __foreach(li, localIncludes)
	{
	 	Source *s = sources[directory() + "/" + *li];
	 	//if it's not there, try it from the local directory (The -I. might be used on the source tree)
    /*This variant is used for header files of your own program. It searches for a file named file first in the directory containing the current file, then in the quote directories and then the same directories used for <file>. You can prepend directories to the list of quote directories with the -iquote option.*/
    
    //-I option for ccbuild local resolution
    vector<string> includePaths(Options::includePaths);
    __foreach(path, includePaths)
    {
    	_debugLevel4("Trying path: " << *path << " for " << *li);
    	if(s != 0)
    		break;
	 		s = sources[*path + "/" + *li];
	 	}
	 	
	 	
	 	if(s == 0)
	 	{
	 		cerr << "ccbuild: Unable to read '" << directory() <<  "/" << *li << "'\n";
	 		cerr << "ccbuild:   mentioned in '" << filename() << "'\n";
	 		continue;
	 	}
	 	s->genDeps();
	 	d_deps.push_back(s);
	}

	//All sources we _directly_ depend on now have d_deps filled and genDeps ran.
}
