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
#include "fileSystem.hh"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <typeinfo>

using namespace std;
using namespace bneijt;
int main(int argc, char **argv)
try {
#define FS(FNAME, a) std::cout << "FileSystem::" << #FNAME << "(\"" << a << "\")= " << FileSystem::FNAME(a) << "\n"
    FS(directoryName, "/home/bram/program/cc/ccbuild/src");
    FS(directoryName, ".");
    FS(directoryName, "/");
    FS(directoryName, "hello.txt");
    FS(directoryName, "hello.");
    FS(directoryName, ".hello/");
    std::string dname("/home/bram/program/cc/ccbuild/src");
    for(size_t i = 0; i < 8; ++i) {
        std::cout << i << ": " << dname << "\n";
        dname = FileSystem::directoryName(dname);
    }
    dname = "home/bram/program/cc/ccbuild/src";
    for(size_t i = 0; i < 8; ++i) {
        std::cout << i << ": " << dname << "\n";
        dname = FileSystem::directoryName(dname);
    }

    FS(cleanPath, "/home/bram/program/cc/ccbuild/src");
    FS(cleanPath, ".");
    FS(cleanPath, "/");
    FS(cleanPath, "././");
    FS(cleanPath, "././/");
    FS(cleanPath, "hello.txt");
    FS(cleanPath, "hello.");
    FS(cleanPath, ".hello/");
    FS(cleanPath, "../libbats/SocketComm/../../../Socket/socket.hh");
    FS(cleanPath, "..//../../../Socket/socket.hh");

    FS(absolutePath, "/home/bram/program/cc/ccbuild/src");
    FS(absolutePath, ".");
    FS(absolutePath, "/");
    FS(absolutePath, "././");
    FS(absolutePath, "././/");
    FS(absolutePath, "hello.txt");
    FS(absolutePath, "hello.");
    FS(absolutePath, ".hello/");

    cout << "\n";
    return 0;
} catch(const std::exception &e) {
    //All is LOST... nothing to do here but die
    cerr << "Caught std::exception (" << typeid(e).name() << "): " << e.what();
    cerr << "\nPlease report this as a bug.\n";
}
