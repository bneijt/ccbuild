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

#ifndef __Lock_HH_INCLUDED
#define	__Lock_HH_INCLUDED
#include <omp.h>

namespace bneijt
{
namespace OpenMP
{
class Lock
{
    omp_lock_t d_lock;
	public:
	  Lock()
	  {
	    omp_init_lock(&d_lock);
	  }
    ~Lock()
    {
	    omp_destroy_lock(&d_lock);    
    }
    void set()
    {
      omp_set_lock(&d_lock);
    }
    void unset()
    {
      omp_unset_lock(&d_lock);
    }
};
}} //Namespace
#endif

