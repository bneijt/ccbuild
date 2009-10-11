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
std::string FileSystem::baseName(string const &filename)
{
  string::size_type i = filename.find_last_of('/') + 1;
  if(i == string::npos)
  	i = 0;

  return filename.substr(i, filename.find_last_of('.') - i);
}
