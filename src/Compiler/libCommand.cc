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

string Compiler::libCommand(std::string pwd,
			std::string target) const
{

  ostringstream command(d_baseCommand, ios::ate);
  command << " -shared -Wl,-soname,\"" << target << "\"" << Options::extraArgs << " ";


  _foreach(obj, d_objects)
    command << " \"" << (*obj) << "\" ";

  copy(d_link.begin(), d_link.end(), ostream_iterator<string>(command, " "));

  command << "-o \"" << target << "\" ";
  

  command << Options::commandAppend;

	return command.str();
}
