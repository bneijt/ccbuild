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

//See GNU manual for options: http://gcc.gnu.org/onlinedocs/gcc/Link-Options.html#Link-Options


#include "Compiler.ih"
void Compiler::addArgument(std::string argument)
{
	_debugLevel4("Starting (" << argument << ")");
	//String split the argument by spaces
	vector<string> arguments;
	_debugLevel4("Split");
	splitInto(argument, arguments);
	

	_debugLevel4("Parse");
	//Parse arguments
	while(true)
	{
		unsigned count = countFirstLinkerArguments(arguments);
		
		//Move those arguments to the linker options list
		while(count--)
		{
			//Never add multiple arguments of the same value
			if(find(d_link.begin(), d_link.end(), arguments.front()) == d_link.end())
				d_link.push_back(arguments.front());
			arguments.erase(arguments.begin());
			_debugLevel3("Linker opt: " << d_link.back());
		}

		//EOF
		if(arguments.size() == 0)
			break;
			
		//Move this argument to the normal compilation argument list.
		//Never add multiple arguments of the same value
		if(find(d_compile.begin(), d_compile.end(), arguments.front()) == d_compile.end())
			d_compile.push_back(arguments.front());

		arguments.erase(arguments.begin());		
	}
	_debugLevel4("End");
}

