/*
  This file is part of ccbuild.

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

#include "compiler.ih"

std::string const Compiler::s_highLightOff("\x1b\x5b\x30\x6d");		//\\e[0m
std::string const Compiler::s_highLightOn("\x1b\x5b\x33\x31\x6d");	//\e[31m
std::string const Compiler::s_clear("\33[H\33[2J");

//Messages
std::string const Compiler::s_msgCancelBruteMode("ccbuild: Canceling brute because of return value 2 from compiler\n");
