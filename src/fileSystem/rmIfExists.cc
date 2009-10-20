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

#include "fileSystem.ih"

bool FileSystem::rmIfExists(std::string const &filename)
{
  if(! FileSystem::fileExists(filename))
  	return false;

  cerr << "[RM] " << filename << "\n";
  
  if(Options::simulate)
		return true;

	int retValue = unlink(filename.c_str());

	if(retValue != 0)
	{
	  cerrLock.set();
	  cerr << "Non zero exit status for unlink: status " << retValue << "\n";
	  cerr << "    could not remove: " << filename << "\n";
	  cerrLock.unset();
	  return false;
	}

	return true;
}

