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

#include "source.ih"

void Source::genDeps()
{
	//If we already have deps, we are done.
	if(d_depsDone)
		return;
  
  d_apiLock.set();

	if(d_depsDone)
		return;


  d_depsDone = true; //TODO Use an atomic variable for these kinds of checks?
  
  
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
	  std::string iname(directory() + "/" + *li);
	  _debugLevel4("Loading source for local include: " << iname);
	 	Source *s = sources[iname];

	 	if(s == this)
	 	{
	 	  cerrLock.set();
	 		cerr << "ccbuild: Recursive include encountered in '" << filename() << "'\n";
	 		cerr << "ccbuild:   ignoring self dependency.\n";
	 	  cerrLock.unset();
	 		continue;
	 	}
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
	 	d_deps.push_back(s);
	}
	
  _debugLevel2("genDeps done: " << d_deps.size() << " local, " << d_globalDeps.size() << " global, and " << d_ignored.size() << " ignored includes\n\t for file " << d_filename);
  
	//Trigger generation of sub-source dependencies: copy pointers, unlock api, call sub-generation
	vector<Source *> deps(d_deps.begin(), d_deps.end());
  d_apiLock.unset();
	__foreach(dep, deps)
	  (*dep)->genDeps();

	//All sources we _directly_ depend on now have d_deps filled and genDeps ran.	
}

