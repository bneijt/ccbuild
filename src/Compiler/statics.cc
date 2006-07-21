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

std::string const Compiler::s_highLightOff("\x1b\x5b\x30\x6d");		//\\e[0m
std::string const Compiler::s_highLightOn("\x1b\x5b\x33\x31\x6d");	//\e[31m
std::string const Compiler::s_clear("\33[H\33[2J");

//Messages
std::string const Compiler::s_msgCancelBruteMode("ccbuild: Canceling brute because of return value 2 from compiler\n");
