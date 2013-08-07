/*
  This file is part of ccbuild.
  Copyright (C) 2013  A. Bram Neijt <bneijt@gmail.com>

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
#include <iostream>


#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <getopt.h>

#define DEBUGLEVEL 3


#define debugLevel2(x) cerr << x << endl;
#define debugLevel4(x) cerr << x << endl;

//Timeofday
#include <sys/time.h>
#include <time.h>
using namespace std;


int main(int argcbbb, char *argvbbb[])
{
	//Use getopt
	while(getopt(argcbbb, argvbbb, "l:b:") != EOF);
	               static struct option long_options[] = {
                   {0, 0, 0, 0}
               };
	//Use getopt_long
	int index;
	while(getopt_long(argcbbb, argvbbb, "l:b:", long_options, &index) != EOF);

	//Normally class members or function arguments

  string argument("-lstdc++ -lpng -lz");
  vector<string> d_link, d_compile;

  //Start of function code

	debugLevel2("Adding argument: " << argument);

	//Trim the string
	string::size_type pos = argument.find_first_not_of(" \t");
	if(pos != string::npos)
		argument = argument.erase(0, pos);

	pos = argument.find_last_not_of(" \t");
	if(pos != string::npos && pos + 1 < argument.size())
		argument = argument.erase(pos + 1);

	//TODO: BASH evaluate and parse arguments!!!
	//Store argument as been seen

	//TODO: BASH evaluate all substrings (like `echo -- -lpng`)!!

	//Create argc, argv
	char skipping = 0;

	//memcpy argument.c_str naar text;
	unsigned textSize = argument.size() +1;
	char *text = new char[textSize];	//For the zero ending ;-)
	strncpy(text, argument.c_str(), textSize);
	debugLevel2("Argument text: " << text);
	//for(unsigned i = 0; i < argument.size(); ++i)
	//	argv[i] = 0;

	unsigned argc = 0;

	for(unsigned i=0; i < argument.size(); ++i)
	{
		//Skip quoted strings
		//SHOULD STILL FIND AND EXPAND QUOTED STRINGS
		if(skipping == 0)
		if(argument[i] == '"' || argument[i] == '\'' || argument[i] == '`')
		{
			skipping = argument[i];
			continue;
		}
		if(argument[i] == '\\')
		{
			//TODO: Escapes are possible and allowed???
			++i;
			continue;
		}
		if(argument[i] == skipping)
		{
			skipping = 0;
			continue;
		}

		if(skipping != 0)
			continue;

		if(argument[i] == ' ')
		{
			text[i] = '\0';
			++argc;
		}
	}
	++argc;

	unsigned argcc = 1;
	char **argv = new char* [argc +1];
	argv[argc] = 0;	//Terminating zero, needed????

	argv[0] = &text[0];
	for(unsigned i=0; i < textSize -1; ++i)
	{
		if(text[i] == '\0')
		{
			++i;
			argv[argcc] = &text[i];
			argcc++;
		}
	}

	//TEST CODE
	debugLevel2("Argc: " << argc);
	for(unsigned i=0; i < argc; ++i)
			debugLevel2("argv[" << i << "] \'" << argv[i] << "\'");


	/*
		Include options:
			-I
			-include
		Linker options:
			-L (directory serach path)
			-l
	ETC!
	*/

	bool done = false;
	while(!done)
	{
		string option;
		//TEST CODE
		debugLevel2("Argc: " << argc);
		for(unsigned i=0; i < argc; ++i)
				debugLevel2("argv[" << i << "] \'" << argv[i] << "\'");

		int c = getopt(argc, argv, "I:i:l:L:D:");

		if(c <= 0xFF)
		{
			option = "-";
			option += static_cast<char>(c);
			option += (optarg ? optarg : "");
		}

    switch (c)
    {
      case '?':
      	cerr << "Unknown option: \'" << optopt << "\'\n";
      	done = true;
      	break;
      case ':':
				cerr << "Missing option value\n";
				done = true;
        break;
    	case EOF:
    		//Hmmm... left with a fes options... dunno what to do here yet
      	//copy(argv + optind, argv + argc, back_inserter(d_argv));
      	done = true;
        break;
      //Compiler options
			case 'I':
				debugLevel2("Add compile option: " << option << "\n");
				if(find(d_compile.begin(), d_compile.end(), option) == d_compile.end())
					d_compile.push_back(option);
      	break;
			case 'D':
				debugLevel2("Add compile option: " << option << "\n");
				if(find(d_compile.begin(), d_compile.end(), option) == d_compile.end())
					d_compile.push_back(option);
      	break;
			case 'i':
				//-include e.a.
				debugLevel2("Add compile option: " << option << "\n");
				if(find(d_compile.begin(), d_compile.end(), option) == d_compile.end())
					d_compile.push_back(option);
      	break;

      //Default to linker options!
			default:
				debugLevel2("Add link option: " << option << "\n");
				if(find(d_link.begin(), d_link.end(), option) == d_link.end())
					d_link.push_back(option);
				break;
		}
	}

	/* DEPRECATED include and libs parsing
  //Parse argument and addLibrary addInclude etc.
  if(argument.size() > 2)
  {
		//cout << "Adding argument: " << argument << "\n";
    if(argument[1] == 'I')
      d_includes[argument.substr(2)] = true;
    if(argument[1] == 'l')
      d_libs[argument.substr(2)] = true;
  }
  */


  delete[] text;
	delete[] argv;

  debugLevel4("leaving function");












}

