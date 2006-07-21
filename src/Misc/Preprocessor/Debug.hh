/*
   Debug.hh - C++ debugging preprocessor macro's

   Copyright (C) 2004 A. Bram Neijt <b.neijt@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/
///\file
///\brief Preprosessor macro's for easy debug info printing
///
///These preprosessor instructions place info as debugging information on the screen.
///You should use DEBUGLEVEL to set the level of debugging info you want. When DEBUGLEVEL is not defined
/// these macro's evaluate to nothing.
///
///If DEBUGLEVEL is set to 1, Level1 debug info is printed. If DEBUGLEVEL is set to 2, all Level2 and lower are printed. etc.
///
///To set the debuglevel of a class, place \#define DEBUGLEVEL in the internal header file (in contrast to the header). This will keep multiple defenitions from occuring when compiling.
///
///The output generated is: "[Filename]:[Line number]: [information]\n"
///
///The extraction operator is used for creating the debug line, so info can contain more then multiple elements devided
/// by extraction operators.
///\section examples Examples
///\code
/// _debugLevel2("Starting algorithm with:" << "something.");
/// _debugLevel3("And thinking about running it" << i << " times.");
///\endcode

//No include guards, to keep the defenitions as much up to date as possible, due to the dependencie on DEBUGLEVEL.

#if DEBUGLEVEL > 0
#include <iostream>
	#define _debugLevel1(info) std::cerr << "D1:" << __FILE__ << ":" << __LINE__ << ": " << info << std::endl
#else
	///\brief Output info when DEBUGLEVEL is 1 or more
	#define _debugLevel1(info)
#endif

#if DEBUGLEVEL > 1
	#define _debugLevel2(info) std::cerr << "D2:" << __FILE__ << ":" << __LINE__ << ": " << info << std::endl
#else
	///\brief Output info when DEBUGLEVEL is 2 or more
	#define _debugLevel2(info)
#endif

#if DEBUGLEVEL > 2
	#define _debugLevel3(info) std::cerr << "D3:" << __FILE__ << ":" << __LINE__ << ": " << info << std::endl
#else
	///\brief Output info when DEBUGLEVEL is 3 or more
	#define _debugLevel3(info)
#endif

#if DEBUGLEVEL > 3
	#define _debugLevel4(info) std::cerr << "D4:" << __FILE__ << ":" << __LINE__ << ": " << info << std::endl
#else
	///\brief Output info when DEBUGLEVEL is 4 or more
	#define _debugLevel4(info)
#endif
