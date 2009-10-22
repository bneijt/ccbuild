
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

#include "source.ih"

void Source::directDeps(std::vector<Source*> &localDeps, std::vector<std::string *> &globalDeps, std::vector<string> &ignored) const
{
  if(!d_depsDone)
    throw Problem(Problem::Unable, "Unable to get directDeps without the file being scanned.");

	localDeps = d_deps;
	copy(d_globalDeps.begin(), d_globalDeps.end(), back_inserter(globalDeps));

	//String copying!	
	ignored = d_ignored;
}

void Source::directDeps(std::vector<Source*> &localDeps, std::vector<std::string *> &globalDeps) const
{
  if(!d_depsDone)
    throw Problem(Problem::Unable, "Unable to get directDeps without the file being scanned.");
	localDeps = d_deps;
	copy(d_globalDeps.begin(), d_globalDeps.end(), back_inserter(globalDeps));
}

void Source::directDeps(std::vector<Source*> &localDeps) const
{
  if(!d_depsDone)
    throw Problem(Problem::Unable, "Unable to get directDeps without the file being scanned.");
	localDeps = d_deps;
}
