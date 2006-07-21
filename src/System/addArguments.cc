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
bool System::addArguments(int &argc, char ** &argv)
{
	ifstream ccResolutions("ccResolutions");
	if(! ccResolutions.is_open())
	  return false;

	string confLine;
	getline(ccResolutions, confLine);

	//Configuration line ok and starts with "#&" ??
	if(ccResolutions.eof()
			|| confLine.size() < 3
			|| confLine.substr(0,2) != "#&")
	  return false;
	 
	confLine = confLine.substr(2);
	cerr << "ccbuild: Adding ccResolutions arguments.\n";
	_debugLevel1("ccbuild: Arugment line: '" << confLine << "'");
	wordexp_t p;

	int retv = wordexp(confLine.c_str(), &p, 0);
	if(retv != 0)
	{
		cerr << "ccbuild: Error shell expanding '" << confLine << "'.\n";
		cerr << "ccbuild: You might want to check your ccResolutions file.\n";
		//TODO Move this error code to the same as exapand.cc
		switch(retv)
		{
			case WRDE_BADCHAR:
			cerr << "ccbuild: Illegal  occurrence of newline or one of |, &, ;, <, >, (, ), {,}.\n";
			break;
//				case WRDE_BADVAL:
//			cerr << "ccbuild: An undefined shell variable was referenced, and  the  WRDE_UNDEF flag told us toconsider this an error.\n";
//			break;
				case WRDE_CMDSUB:
				cerr << "ccbuild: Command  substitution  occurred, and the WRDE_NOCMD flag told us\n";
				cerr << "ccbuild:   to consider this an error.\n";
				break;
				case WRDE_NOSPACE:
				cerr << "ccbuild: Out of memory.\n";
				break;
				case WRDE_SYNTAX:
				cerr << "ccbuild: Shell syntax error, such as unbalanced parentheses or unmatched quotes.\n";
				break;
	   }
	   
		wordfree(&p);
	   return false;
	}//If retValue != 0
	
	//Create a new arguments array
	char ** newArgs = new char *[argc + p.we_wordc + 1];
		
	//Copy argv values
	for(int i = 0; i < argc; ++i)
	{
	 	newArgs[i] = new char[strlen(argv[i]) + 1];
	 	strcpy(newArgs[i], argv[i]);
	}
		
	//Append wordexp values
	for(unsigned i = 0; i < p.we_wordc; ++i)
	{
	 	newArgs[argc + i] = new char[strlen(p.we_wordv[i]) + 1];
	 	strcpy(newArgs[argc + i], p.we_wordv[i]);
	}
		
	//Argv array must be 0 terminated (Probably 3.6.1 p2 of C++ standard)
	newArgs[argc + p.we_wordc] = 0;

	//Free wordexp values
	wordfree(&p);
		
	//Export values
	//!!! Start of possible memory leak. We new it here, does anybody delete it?
	argv = newArgs;	
	argc += p.we_wordc;
	 	
	return true;
}
