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

#include "FileSystem.hh"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <typeinfo>

using namespace std;
using namespace bneijt;
int main(int argc, char **argv)
try
{
  #define FS(FNAME, a) std::cout << "FileSystem::" << #FNAME << "(\"" << a << "\")= " << FileSystem::FNAME(a) << "\n"
  FS(directoryName, "/home/bram/program/cc/ccbuild/src");
  FS(directoryName, ".");
  FS(directoryName, "/");
  FS(directoryName, "hello.txt");
  FS(directoryName, "hello.");
  FS(directoryName, ".hello/");
  std::string dname("/home/bram/program/cc/ccbuild/src");
  for(size_t i = 0; i < 8; ++i)
  {
    std::cout << i << ": " << dname << "\n";
    dname = FileSystem::directoryName(dname);
  }
  dname = "home/bram/program/cc/ccbuild/src";
  for(size_t i = 0; i < 8; ++i)
  {
    std::cout << i << ": " << dname << "\n";
    dname = FileSystem::directoryName(dname);
  }


  cout << "\n";
  return 0;
}
catch(const std::exception &e)
{
	//All is LOST... nothing to do here but die
  cerr << "Caught std::exception (" << typeid(e).name() << "): " << e.what();
  cerr << "\nPlease report this as a bug.\n";
}
