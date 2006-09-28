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

int Compiler::ar(std::string pwd, std::string target) const
{

	//Construct ar command
  ostringstream command("ar rcs ", ios::ate);
  command << " " << pwd << "/" << target;

  _foreach(obj, d_objects)
    command << " \"" << (*obj) << "\"";

	cls();
	
  //Remove the output file
  FileSystem::rmIfExists(target);

  cerr << "[AR] " << target << "\n";

	//Run ar command
	int retValue = System::system(command.str().c_str());


  if(retValue != 0)
  {
    cerr << "ccbuild: Non zero exit status (" << retValue << ")\n";

    if(!Options::brute)
    	throw Problem(Problem::Subfailure, "Archiving failed on " + target, retValue);
  }

  return retValue;
}