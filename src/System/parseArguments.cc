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

bool System::parseArguments(Arguments &arg)
{

		//Simple options
	Options::md5 = arg.flagged("md5");
	Options::brute = arg.flagged("brute");
	Options::clearPerCommand = arg.flagged("clearpc");
	Options::precompile = arg.flagged("p");
	Options::defaultUpdate = arg.flagged("f");
  Options::highlight = arg.flagged("highlight");
  Options::loadGlobalRes = ! (arg.flagged("nodefres"));
  Options::xml = arg.flagged("xml");
  Options::interAr = arg.flagged("ar");
  Options::noWarn = arg.flagged("nowarn");

  Options::execOnFail = arg.value("exec-on-fail");
  Options::execOnPass = arg.value("exec-on-pass");
  Options::progVersion = arg.value("pversion");

	//Error handling (simple options contain showCommands, which might help)
	if(arg.errors().size() > 0)
	{
		vector<string> &err = arg.errors();
		__foreach(e, err)
			cerr << "ccbuild: Error: Error parsing command line argument '" << *e << "'\n";
		cerr << "ccbuild:   Use '-h' for help\n";
	
		return true;
	}

  if(arg.flagged("append"))
	  Options::commandAppend = " " + arg.value("append");

	if(arg.flagged("compiler"))
		Options::CC = arg.value("compiler");
		
	if(arg.flagged("verbose"))
	{
		Options::showCommands = true;
		Options::verbose = true;
	}
	if(arg.flagged("precompile-all"))	//Precompile-all
	{
		Options::precompile = true;
		Options::precompileAll = true;
	}
	
  if(arg.flagged("args"))
  	Options::extraArgs = arg.value("args");
  else
  	Options::extraArgs = "-Wall -g";

	if(arg.flagged("I"))
	{
		vector<string> paths = arg.values("I");
		__foreach(path, paths)
		{
			//Strip last slash
			if(path->find_last_of('/') == path->size() -1)
				*path = path->substr(0, path->size() -1);
		
			Options::includePaths.push_back(*path);
			Options::extraArgs += " -I" + (*path);
		}
	}

	if(arg.flagged("s"))	//Simulate
	{
		Options::simulate = true;
		cerr << "[SIMULATION MODE]\n";
	}


  if(arg.flagged("addres"))
  {
  	Options::extraResolutions = arg.values("addres");
  }
  	
	if(arg.flagged("recursive-include"))
	{
		vector<string> paths = arg.values("recursive-include");
		vector<string> &includePaths = Options::includePaths;
		
		__foreach(path, paths)
		{
			//Strip last slash
			if((*path).find_last_of('/') == (*path).size() -1)
				*path = (*path).substr(0, (*path).size() -1);
			
			vector<string> dirList;
			FileSystem::recursiveGlobDirectoriesInto(&dirList, *path);
			__foreach(dir, dirList)
			{
				//Skip "o" directories
			  if(dir->size() > 1 && dir->substr(dir->size() - 2) == "/o")
			  	continue;
			  	
				vector<string> fileList;
				FileSystem::globFilesInto(&fileList, *dir + "/*");

				//Don't add empty directories
				if(fileList.size() == 0)
					continue;
				
				//Add if it's new to the includePaths
				if(find(includePaths.begin(), includePaths.end(), *dir) == includePaths.end())
				{
					includePaths.push_back(*dir);
					Options::extraArgs += " -I" + (*dir);
				}
			}
		}
	}
	
	
	if(arg.flagged("h"))
	{
		cout << "\tccbuild - A strict developer's build utility\n";
		cout << "Version " << Options::version << ", Copyright (C) 2005 A. Bram Neijt <bneijt@gmail.com>\n";
		cout << "ccbuild comes with ABSOLUTELY NO WARRANTY and is licensed under GPL version 2\n";
		cout << "\nCommands:\n";
		cout << " build [source.cc]\tBuild everything or the given source\n";
		cout << " lib [source.cc]\tCreate library of everything or the given source\n";
		cout << " resolve [source.cc]\tList unresolved globals with tabs on stdout\n";
		cout << " md5 [source.cc]\tGenerate list of MD5 sums on stdout\n";
		cout << " deps [source.cc]\tList the dependencies of the sources\n";
		cout << " dot [source.cc]\tGenerate dot graph files for sources\n";
		cout << " makefile [source.cc]\tGenerate a Makefile on stdout\n";
		cout << " aap [source.cc]\tGenerate an a-a-p file on stdout\n";
		cout << " tree [source.cc]\tEXPERIMENTALGenerate an ascii tree of used files\n";
		cout << " check [source.cc]\tShow wether files are up to date\n";
		cout << " icmake [source.cc]\ticmake slave mode: output used directories\n";
		cout << " clean [source.cc]\tClean everything or the given source\n";
		cout << " distclean \t\tRecursively remove 'o' and '.gch' files\n";
		cout << "\nOptions:\n";
		arg.outputOptions(cout);
		cout << "\nThe resolution files link global includes to compiler arguments using:\n";
		cout << " 'something.h<tab> `/usr/bin/pkg-config --libs --cflags package`'\n";
		cout << "'#'=comment start, '#&' at first line appends ccbuild arguments.\n";
		cout << "Resolution files are (in order):\n './ccResolutions' '~/.ccbuild/ccResolutions' '~/.ccbuild/ccResolutions.d/*'\n";



		return true;
	}
	if(arg.flagged("V"))
	{
		cerr << "\tccbuild - A strict developer's build utility\n";
		cerr << " Copyright (C) 2005 A. Bram Neijt <bneijt@gmail.com>\n";
		cerr << " ccbuild comes with ABSOLUTELY NO WARRANTY and is licensed under GPL version 2\n";
		cerr << "Version number is" << endl;
		cout << Options::version << "\n";
		return true; 
	}

	return false;
}


