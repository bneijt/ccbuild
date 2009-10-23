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

///\file
///\brief Preprosessor macro to define a STL iterator for loop: _foreach(iterator, container)


#ifndef __ccsys_FOREACH_H_INCLUDED
#define __ccsys_FOREACH_H_INCLUDED
//
// The triple expansion may seem daring, but it is needed to fully expand the __LINE__
// Which is needed for code like: foreach(iter, arrayOfVectors[0])
//

///\brief Preprosessor macro to define a STL iterator for loop: __foreach(iterator, container)
///
///The preprosessor instruction foreach takes a variable name and an iterator name and translates
///into a default for loop using the != operator. It should work with any forward iterator.
///For const iterators, there is the cforeach preprocessor macro.
///\section examples Examples
///\code
///vector<usnigned> numbers;
///numbers.push_back(10);
///__foreach(number, numbers)
///  cout << *number << "\n";
///\endcode
///
///DON'T!!!
///Don't use temporary const objects returned by functions, like: foreach(i, file.lines()).
/*
__typeof__((cont).begin()) iter
#pragma omp parallel private (iter)
{
for (iter = (cont).begin(); iter != (cont).end(); ++iter)
{
   #pragma omp single nowait
   {
     CODE
   }
} // end for
} // end omp parallel



*/

#ifdef __foreach
#error __foreach already defined! This macro may have gone wild!
#endif

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#define __foreach( iter, cont) for(auto iter = (cont).begin(); iter != (cont).end(); ++iter)
#else
#define __foreach( iter, cont) for( __typeof__((cont).begin()) iter = (cont).begin(); iter != (cont).end(); ++iter)
#endif

//#define __foreachMP( iter, cont, block) #pragma omp parallell private (oter)

//_INCLUDED
#endif
