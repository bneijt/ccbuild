/*
  This file is part of ccbuild.
  Copyright (C) 2013  A. Bram Neijt <bneijt@gmail.com>

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
    std::string contentCopy(*this);
    __foreach(c, contentCopy)
        if(*c == from)
            *c = to;
    return contentCopy;
}
std::string String::replace(std::string const &from, std::string const &to) const
{
    std::string contentCopy(*this);
    while(true)
    {
        std::string::size_type pos = contentCopy.find(from);
        if(pos == std::string::npos)
           break;
        contentCopy.replace(pos, from.size(), to);
    }
    return contentCopy;
}
