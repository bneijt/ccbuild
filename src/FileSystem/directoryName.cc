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






#include "FileSystem.ih"
std::string FileSystem::directoryName(string const &filename)
{  
	//TODO allow for slash escaping of the character??
  string::size_type lastSlashPos = filename.find_last_of("/");
  if(lastSlashPos == string::npos)
    return ".";
  if(lastSlashPos == 0)
    return "/"; //Last slash is the root
 
	_debugLevel2("dir(" + filename + ") = " + filename.substr(0, lastSlashPos));

  return filename.substr(0, lastSlashPos);
}
