/*
   ccbuild - A strict developer's build utility

   Copyright (C) 2005 A. Bram Neijt <bneijt@gmail.com>

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
///\brief Test utility for the MD5Hash class


#include "MD5Cache/MD5Cache.hh"

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//#define DEBUGLEVEL 20
#include "Misc/Preprocessor/Debug.hh"

using namespace bneijt;
using namespace std;

int main(int argc, char *argv[])
{
	MD5Cache &c = MD5Cache::getInstance();
	cout << "Last:    " << c.last(argv[0]) << endl;
	cout << "Current: " << c.current(argv[0]) << endl;
	
	MD5Hash h;
	h.from(argv[0]);
	cout << h << "\t" << argv[0] << endl;
	
	c.destroy();
	return 0;
}
