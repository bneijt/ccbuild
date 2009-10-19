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


/**\file

 \brief ccbuild - A strict developer's build utility

  <pre>
   Copyright (C) 2005 A. Bram Neijt <bneijt@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
  </pre>
*/

#include "problem/problem.hh"
#include "system/system.hh"
#include "source/source.hh"
#include "FileSystem/FileSystem.hh"
#include "globallocks/globallocks.hh"
#include "misc/foreach.hh"
#include "Options/Options.hh"

//Singletons...
#include "arguments/arguments.hh"
#include "sources/sources.hh"
#include "MD5Info/MD5Info.hh"


#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <cassert>
#include <typeinfo>

//#define DEBUGLEVEL 20
#include "misc/debug.hh"

using namespace bneijt;
using namespace std;

namespace {
/**
	Temporary solution, this will probably go away and arguments will be handled as as
	vector<string> arg(argv[0], argv[argc -1]);
	Which will remove the need for this weird class.
	(Wanted to call this Apoptosis, but ArgsDestory seemed more readable ;-) )
//TODO Cleanup with auto_ptr if possible
//TODO Maybe move the whole program into a class, and use the destructor for this
*/
class ArgsDestroy
{
		char **d_argv;
		unsigned d_argc;
	public:
		ArgsDestroy()
			:
			d_argv(0),
			d_argc(0)
		{}
		
		ArgsDestroy(ArgsDestroy const & o);//NI
    ArgsDestroy operator=(const ArgsDestroy&);//NI
    
		void set(unsigned argc, char *argv[])
		{
			assert(argc > 0);
			d_argc = argc;
			d_argv = argv;
		}
		
		~ArgsDestroy()
		{
			
			for(unsigned i = 0; i < d_argc; ++i)
      	delete[] d_argv[i];

      if(d_argv)
	      delete[] d_argv;
		}
};

}//namespace
/**
  The main program function: call argument parser and go through the commands using a large if-then-else block.
*/
int main(int argc, char **argv)
try
{
  //TODO Clean up main
  //See Options/statics.cc Options::CC = "g++";
  //See Options/statics.cc Options::version = "...";
  Arguments::Option options[] = {
    {"f force-update", "", "Force an update of everything"},
    {"h help", "", "Get this help message"},
    {"gnutouch", "", "Do the GNU touch (NEWS, README, etc.)"},
    {"s no-act", "", "Simulate, don't execute any writing commands"},
    {"compiler", "<cmd>", "Set the compiler command (Default: g++)"},
    {"a args", "<arguments>", "Use these as base compiler arguments (Default: -Wall -g)"},
    {"C", "<path>", "Change directory before anything else"},
    {"p precompile-ih", "", "Precompile only internal headers (g++-3.4 up)"},
    {"precompile-all", "", "Precompile all headers (g++-3.4 up)"},
    {"brute", "", "Continue on compiler errors"},
    {"md5", "", "Use md5 hashes instead or timestamps to check for file changes"},
    {"I", "<path>", "Add path to local include search paths"},
    {"recursive-include", "<path>", "Like -I but recursive"},
    {"l highlight", "", "Colour command output"},
    {"xof exec-on-fail", "<cmd>", "Execute this command on source on failure"},
    {"xop exec-on-pass", "<cmd>", "Execute this command on source on success"},
    {"clearpc", "", "Clear the screen just before every command"},
    {"append", "<cmd>", "Append this to every command (for pipes etc.)"},
    {"loop", "", "Loop ccbuild execution (build only)."},
    {"nodefargs", "", "Don't load extra arguments from ./ccResolutions"},
    {"nodefres", "", "Don't load any ccResolutions files but ./ccResolutions"},
    {"addres", "<file>", "Also load this resolution file"},
    {"pversion", "<version>", "Set the program version you are working on (used by the lib command)"},
    {"ar", "", "Archive before link (can shrink size for release)"},
    {"verbose", "", "Show executed commands and produce more output for dot and check commands"},
    {"V version", "", "Output ccbuild version number to stdout"},
    {"xml", "", "Where supported, produce XML output"},
    {"nowarn", "", "Leave out most warnings"},
#ifdef _OPENMP
    {"j", "<integer>", "Set the maximum number of threads used during build"},
#endif
    {"", "", ""}	//End of list
  };

  int retValue = 0;
  
  //First find C option and change directory before anything else
  Arguments::initialize(options, argc, argv);
  Arguments &tempArg = Arguments::getInstance();
  
  bool defargs = !tempArg.flagged("nodefargs");
  if(tempArg.flagged("C"))
    if(!System::changeTo(tempArg.value("C")))
    	throw Problem(Problem::Unable, "Unable to change dir to '" + tempArg.value("C") + "'");
  
  tempArg.destroy();
  
  
  //Check for extra options on the start of our ccResolutions files  
  ArgsDestroy a;
  if(defargs)
    if(System::addArguments(argc, argv))
	    a.set(argc, argv);	//set self destuctor

  Arguments::initialize(options, argc, argv);
  Arguments &arg = Arguments::getInstance();

  bool destroy = System::parseArguments(arg);

  if(Options::showCommands)
  {
    cerrLock.set();
    cerr << "Command:";
    for(int i = 0; i < argc; i++)
    {
      if(index(argv[i], ' ') || strlen(argv[i]) == 0)
        cerr << " \"" << argv[i] << "\"";
      else
        cerr << " " << argv[i];
    }
    cerr << "\n";
    cerrLock.unset();
  }

  if(destroy)
  {
    System::destroy();
    return 1;
  }

  if(arg.flagged("gnutouch"))
  {
    cerr << "[gnutouch]\n";
    string offset;
    string cwd = FileSystem::cwd();

    //Are we in the src directory?
    if(cwd.size() > 3 && cwd.substr(cwd.size() - 3) == "src")
      offset = "../";

    //Are we being fooled??
    if(FileSystem::fileExists("./src"))
      offset = "";

    string gnufiles[] = {"AUTHORS", "NEWS", "README", "INSTALL", "COPYING", "TODO", "ChangeLog"};
    for(unsigned i = 0; i < 7; ++i)
    {
      cerr << "[TOUCH] " << offset << gnufiles[i];

      if(!Options::simulate)
      if(! FileSystem::touch(offset + gnufiles[i]))
        cerr << " Failed !";
      cerr << "\n";
    }
  }

    
  vector<string> &rest = arg.rest();


  if(rest.size() == 0)
  {
    cerr << "Implicit build\n";
    rest.push_back("build");
  }  
  else if(rest.size() == 1 && FileSystem::fileExists(*rest.begin(), /*noDir=*/true))
  {
    cerr << "Implicit build because first an only command is a file\n";
    rest.insert(rest.begin(), "build");    	
  }



  Sources &sources = Sources::getInstance();
  
  bool skipArgument(false);
  __foreach(argument, rest)
  {
    vector<string>::iterator next = argument;
    ++next;
    
    if(skipArgument)
    {
      skipArgument = false;
      continue;
    }
        
    if(*argument == "icmake")
    {
      cerr << "[" << *argument << "]\n";
      
      if(next == rest.end())
        System::icmake();
      else
      {
        Source *s = sources[*next];
        if(s)
        {
          skipArgument = true;
          System::icmake(s);
        }
        else
        {
          cerr << "Error loading '" <<  *next << "' for status checking.\n";
          retValue = 2;
          break;
        }
      }
      retValue = 0;
      break;
    }
    else if(*argument == "check")
    {
      cerr << "[" << *argument << "]\n";

      if(next == rest.end())
        System::check();
      else
      {
        Source *s = sources[*next];
        if(s)
        {
          skipArgument = true;
          System::check(s);
        }
        else
        {
          cerr << "Error loading '" <<  *next << "' for status checking.\n";
          retValue = 2;
          break;
        }
      }
      retValue = 0;
      break;
    }
    else if(*argument == "resolve")
    {
      cerr << "[" << *argument << "]\n";

      if(next == rest.end())
        System::resolveTest(cout);
      else
      {
        Source *s = sources[*next];
        if(s)
        {
          skipArgument = true;
          System::resolveTest(s, cout);
        }
        else
        {
          cerr << "Error loading '" <<  *next << "' for status checking.\n";
          retValue = 2;
          break;
        }
      }
    }
    else if(*argument == "build")
    {
      bool loop = arg.flagged("loop");
      do
      {
        //Because we might destroy the instance, we need a new version
        cerr << "[" << *argument << "]\n";
        
        if(next == rest.end())
          System::buildAll();
        else
        {
          Source *s = sources[*next];
          if(s)
          {
            skipArgument = true;
            System::build(s);
          }
          else
          {
            cerr << "Error loading '" <<  *next << "' for building.\n";
            retValue = 2;
            break;
          }
          
        }

        //Remove stale sources
        if(loop)
        {
          sources.reloadStaleSources();
          //Restart all hash knowledge
          MD5Info::destroy();
          
	        cerr << "ccbuild: Loop mode: Press return to continue or q to exit..." << endl;
	        string tmp;
	        getline(cin, tmp);
	        if(tmp == "q")
	        {
	        	cerr << "ccbuild: breaking loop on 'q'\n";
	        	break;
	        }
        }
        
        /*Full reload, 
        if(loop)
        {
          Sources::destroy();
          MD5Cache::destroy();
          cerr << "Loop sleep 1 second";
          System::sleep(1);
          cerr << ".\n";
        }*/
      }while(loop);
    }
    else if(*argument == "clean")
    {
      cerr << "[" << *argument << "]\n";

      if(next == rest.end())
        System::clean();
      else
      {
        Source *s = sources[*next];
        if(s)
        {
          skipArgument = true;
          System::clean(s);

        }
        else
        {
          cerr << "Error loading '" <<  *next << "' for cleaning.\n";
          retValue = 2;
          break;
        }
      }
      retValue = 0;
      break;
    }
    else if(*argument == "deps")
    {
      cerr << "[" << *argument << "]\n";

      if(next == rest.end())
        System::depsFor(cout);
      else
      {
        Source *s = sources[*next];
        if(s)
        {
          skipArgument = true;
          System::depsFor(s, cout);

        }
        else
        {
          cerr << "Error loading '" <<  *next << "' for dependencie listing.\n";
          retValue = 2;
          break;
        }
      }
      retValue = 0;
      break;
    }
    else if(*argument == "makefile")
    {
      cerr << "[" << *argument << "]\n";

      if(next == rest.end())
        System::makefileForAll(cout);
      else
      {
        Source *s = sources[*next];
        if(s)
        {
          skipArgument = true;
          System::makefileFor(s, cout);
        }
        else
        {
          cerr << "Error loading '" <<  *next << "' for Makefile generation.\n";
          retValue = 2;
          break;
        }
      }
      retValue = 0;
      break;
    }
    else if(*argument == "aap")
    {
      cerr << "[" << *argument << "]\n";

      if(next == rest.end())
        System::aapForAll(cout);
      else
      {
        Source *s = sources[*next];
        if(s)
        {
          skipArgument = true;
          System::aapFor(s, cout);
        }
        else
        {
          cerr << "Error loading '" <<  *next << "' for A-A-P generation.\n";
          retValue = 2;
          break;
        }
      }
      retValue = 0;
      break;
    }
    else if(*argument == "md5")
    {
      cerr << "[" << *argument << "]\n";

      if(next == rest.end())
        System::md5();
      else
      {
        Source *s = sources[*next];
        if(s)
        {
          skipArgument = true;
          System::md5(s);
        }
        else
        {
          cerr << "Error loading '" <<  *next << "' for MD5 list generation.\n";
          retValue = 2;
          break;
        }
      }
      retValue = 0;
      break;
    }
    else if(*argument == "tree")
    {
      cerr << "[" << *argument << "]\n";

      if(next == rest.end())
        System::tree(cout);
      else
      {
        Source *s = sources[*next];
        if(s)
        {
          skipArgument = true;
          System::tree(s, cout);
        }
        else
        {
          cerr << "Error loading '" <<  *next << "' as tree source.\n";
          retValue = 2;
          break;
        }
      }
      retValue = 0;
      break;
    }
    else if(*argument == "dot")
    {
      cerr << "[" << *argument << "]\n";

      if(next == rest.end())
        System::dotgraphForAll();
      else
      {
        Source *s = sources[*next];
        if(s)
        {
          skipArgument = true;
          System::dotgraphFor(s, cout);
        }
        else
        {
          cerr << "Error loading '" <<  *next << "' for graphing.\n";
          retValue = 2;
          break;
        }
      }
      retValue = 0;
      break;
    }
    else if(*argument == "lib")
    {
      if(Options::progVersion.empty())
        cerr << "[" << *argument << " (archive only)]\n";
      else
        cerr << "[" << *argument << " " << Options::progVersion << "]\n";

      if(next == rest.end())
        retValue = System::lib(Options::progVersion);
      else
      {
        Source *s = sources[*next];
        if(s)
        {
          skipArgument = true;
          retValue = System::lib(Options::progVersion, s);
        }
        else
        {
          cerr << "Error loading '" <<  *next << "' for library building.\n";
          retValue = 2;
          break;
        }
      }
      
      break;
    }
    else if(*argument == "distclean")
    {
      cerr << "[" << *argument << "]\n";
      System::distclean();
    }
    else
    	throw Problem(Problem::Unknown, "Unknown command: " + *argument +"\n Try '" + argv[0] + " -h' for more information.\n");
  }
  
  //Cleanup and exit

  //Destroy singletons...
  System::destroy();
  
  return retValue;
}
catch(const Problem &p)
{
	cerr << "ccbuild: Problem " << p.id() << ": " << p.what() << "\n";
  System::destroy();
	return p.id();
}
catch(const std::exception &e)
{
	//All is LOST... nothing to do here but die
  cerr << "Caught std::exception (" << typeid(e).name() << "): " << e.what();
  cerr << "\nPlease report this as a bug.\n";
  return 1;
}
