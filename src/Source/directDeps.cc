
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




#include "Source.ih"

void Source::directDeps(std::vector<Source*> &localDeps, std::vector<std::string *> &globalDeps, std::vector<string> &ignored) const
{
	localDeps = d_deps;
	copy(d_globalDeps.begin(), d_globalDeps.end(), back_inserter(globalDeps));

	//String copying!	
	ignored = d_ignored;
}

void Source::directDeps(std::vector<Source*> &localDeps, std::vector<std::string *> &globalDeps) const
{
	localDeps = d_deps;
	copy(d_globalDeps.begin(), d_globalDeps.end(), back_inserter(globalDeps));
}

void Source::directDeps(std::vector<Source*> &localDeps) const
{
	localDeps = d_deps;
}
