/*
	ccbuild - A strict developer's build utility
	Copyright (C) 2005  A. Bram Neijt <bneijt@gmail.com>
	Copyright (C) 2005  Jesse van den Kieboom <jesse@icecrew.nl>

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

	Initial version by Jesse van den Kieboom
	Modified by A. Bram Neijt
*/

#include "System.ih"

int System::system(std::string const &command, bool simulate) throw (Problem)
{
	VectorRing<string> output(1024);
  if(Options::showCommands)
  	cout << command << "\n";
  
  //Run command caching output
	int status = 0;
	if(!simulate)
	{  
		//status = ::system(command.c_str());
    FBB::Process process(command, FBB::Process::CIN |
                                  FBB::Process::COUT |
                                  FBB::Process::MERGE_COUT_CERR);
    process.start(FBB::Process::USE_PATH);
    //TODO Rewrite to copy call with back_inserter
		string line;
		while(getline(process, line))
		  output.push_back(line);
		status = process.stop();	
	}

	//Highlight ON
  if(Options::highlight)
	  cerr << "\x1b\x5b\x33\x31\x6d" << flush; //\e[31m

  copy(output.begin(), output.end(), ostream_iterator<string>(cerr, "\n"));

	//Highlight OFF
  if(Options::highlight)
	  cerr << "\x1b\x5b\x30\x6d" << flush; //\\e[0m

	//On normal termination return the exit status, otherwise throw a problem
	if(!WIFEXITED(status))
		throw Problem(Problem::Suberror, "Abnormal sub process termination", WEXITSTATUS(status));
	return WEXITSTATUS(status);
}
