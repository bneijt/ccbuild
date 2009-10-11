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


#include "string.ih"
std::string String::replace(char from, char to) const
{
				std::string copy(*this);
			__foreach(c, copy)
				if(*c == from)
					*c = to;
			return copy;

}
std::string String::replace(std::string const &from, std::string const &to) const
{
				std::string copy(*this);
			while(true)
			{
			  std::string::size_type pos = copy.find(from);
			  if(pos == std::string::npos)
			    break;
			  copy.replace(pos, from.size(), to);
			}
			return copy;

}
