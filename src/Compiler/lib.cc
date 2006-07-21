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

#include "Compiler.ih"
int Compiler::lib(std::string pwd,
			std::string outputFile, std::string const &version) const
{
	cls();

  cerr << "[LIB] " << outputFile << "." << version << "\n";

  string command = libCommand(pwd, outputFile + "." + version);

	int retValue = System::system(command.c_str());


	if(retValue != 0)
	{
	  cerr << "ccbuild: Non zero exit status (" << retValue << ")\n";
	  throw Problem(Problem::Subfailure, "Library linking failed.", retValue);
	}

	std::string majorVersion = version.substr(0, version.find_first_of("."));
	if(version.find_first_of(".") == string::npos)
	{
		majorVersion = "0";
		cerr << "ccbuild: Warning: Version without a point, setting Major to " << majorVersion << ".\n";
	}

	// Major version -> full version
	std::string lnc = "ln -sf \"" + outputFile + "." + version + "\" \"" + outputFile + "." + majorVersion + "\"";
	
	retValue = System::system(lnc.c_str());
	
	if(retValue != 0)
   	throw Problem(Problem::Subfailure, "Symlinking failed (major version to full version).", retValue);

  	

	// library.so -> Major version
	lnc = "ln -sf \"" + outputFile + "." + majorVersion + "\" \"" + outputFile + "\"";

	retValue = System::system(lnc.c_str());
	
	if(retValue != 0)
   	throw Problem(Problem::Subfailure, "Symlinking failed (library to major version).", retValue);

	//TODO Return value is now meaningless, throw on !=0
	return retValue;
}

