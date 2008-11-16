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



#include "Options.ih"

std::string Options::version("1.5.8SVN");
std::string Options::CC("g++");
std::string Options::execOnPass("");
std::string Options::extraArgs("");
std::string Options::commandAppend("");
std::string Options::execOnFail("");
std::string Options::homepage("http://ccbuild.sourceforge.net");
std::string Options::progVersion("");
//std::string Options::("");
//std::string Options::("");

bool Options::md5(false);
bool Options::simulate(false);
bool Options::precompile(false);
bool Options::precompileAll(false);
bool Options::verbose(false);
bool Options::defaultUpdate(false);
bool Options::highlight(false);
bool Options::showCommands(false);
bool Options::brute(false);
bool Options::clearPerCommand(false);
bool Options::loadGlobalRes(false);
bool Options::makefileHeaderDone(false);
bool Options::aapHeaderDone(false);
bool Options::xml(false);
bool Options::interAr(false);
bool Options::noWarn(false);
//bool Options::(false);
//bool Options::(false);

std::vector<std::string> Options::includePaths;
std::vector<std::string> Options::extraResolutions;
