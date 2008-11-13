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


#ifndef __VectorRing_HH_INCLUDED
#define	__VectorRing_HH_INCLUDED

#include <vector>
#include <algorithm>
#include <iterator>

namespace bneijt
{
///A Vector which will not grow bejond a special size, containing only the last "n" entries appended
template <typename T>
class VectorRing: public std::vector<T>
{
    size_t d_size;
    typename std::vector<T>::const_iterator d_endIndex;
	public:
	  VectorRing<T>(size_t const maximumSize)
	    :
	    d_size(maximumSize)
	  {}
	  void push_back(T const &value)
	  {
	    if(std::vector<T>::size() >= d_size)
	      std::vector<T>::erase(std::vector<T>::begin());
	    std::vector<T>::push_back(value);
	  }
	  
};
} //Namespace
#endif

