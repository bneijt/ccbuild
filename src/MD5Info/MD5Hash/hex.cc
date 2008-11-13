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



#include "MD5Hash.ih"

unsigned char MD5Hash::hex(char c)
{

	if (c >= '0' && c <= '9' ) //if 0 to 9
		return c - '0';
	
	if (c >= 'a' && c <= 'f') //if a to f
		return 10 + c -'a';
	
	if (c >= 'A' && c <= 'F') //if A to F
		return 10 + c - 'A';

	return 0;
}
