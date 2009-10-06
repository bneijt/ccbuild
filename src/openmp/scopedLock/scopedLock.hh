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

#ifndef __ScopedLock_HH_INCLUDED
#define	__ScopedLock_HH_INCLUDED

#include "../lock/lock.hh"

namespace bneijt
{
namespace OpenMP
{
class ScopedLock
{
    Lock &d_lock;
    
	public:
	  ScopedLock(Lock &l)
	    :
	    d_lock(l)
	  {
	    d_lock.set();
	  }
	  ~ScopedLock()
	  {
	    d_lock.unset();
	  }
};
}} //Namespaces
#endif

