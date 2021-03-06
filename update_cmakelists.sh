#!/bin/bash
#This script is used to re-create the CMakeLists.txt using ccbuild
#
#  This file is part of ccbuild.

#  ccbuild is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.

#  ccbuild is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with ccbuild.  If not, see <http://www.gnu.org/licenses/>.
set -e

if [ "x$1" = "xclean" ]; then
    echo cleaning
    ccbuild distclean
    rm -rf CMakeFiles
    rm -f CMakeCache.txt
    rm -f src/sourceScanner/yylex.cc
    exit
fi

## Generate Makefile.am from ccbuild
PSOURCE=src/ccbuild.cc
PNAME=`basename "${PSOURCE}" .cc`
echo "Updating MD5SUMS file"

if [ -f "src/sourceScanner/yylex.cc" ]; then
    rm src/sourceScanner/yylex.cc
fi

ccbuild md5 --recursive-include . "${PSOURCE}" > MD5SUMS
SOURCES=`egrep .cc$ MD5SUMS | sed  -r 's/^[a-z0-9]+  //; s/ /\\ /' | tr '\n' ' '`
VERSION=`egrep -o 'VERSION=.+"[0-9.]+' src/ccResolutions |cut -d '"' -f 2`

#Write CMakeLists.txt
cat > CMakeLists.txt <<EOF
cmake_minimum_required (VERSION 3.0)
project (ccbuild)

set(CMAKE_CXX_STANDARD 20)

find_package(FLEX)
FLEX_TARGET(SourceScanner "src/sourceScanner/lexer"  "src/sourceScanner/yylex.cc" )
string(SUBSTRING \${FLEX_VERSION} 0 1 FLEX_VERSION_MAJOR)
string(SUBSTRING \${FLEX_VERSION} 2 1 FLEX_VERSION_MINOR)

add_definitions(-DVERSION="${VERSION}" -DFLEX_VERSION_MAJOR=\${FLEX_VERSION_MAJOR} -DFLEX_VERSION_MINOR=\${FLEX_VERSION_MINOR})
link_libraries(gomp bobcat gnutls)
add_definitions(-fopenmp)
add_executable(ccbuild ${SOURCES} \${FLEX_SourceScanner_OUTPUTS})
install(TARGETS ccbuild DESTINATION bin)
install(FILES doc/ccbuild/ccbuild.1 DESTINATION share/man/man1)
EOF
