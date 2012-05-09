#!/bin/sh
#This script is used to clean up the directory
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

VERSION=`egrep -o 'VERSION=.+"[0-9.]+' src/ccResolutions |cut -d '"' -f 2`
if [ -z "$VERSION" ]; then
    echo EMPTY VERSION FOUND
    exit 1
fi


ccbuild distclean
rm -rf src/ccbuild

echo "]]] Documentation"
make -C doc/ccbuild clean
make -C doc/ccbuild

YYLEX=src/sourceScanner/yylex.cc


echo "]]] Makefile"
if [ ! -f $YYLEX ];	then
	make -f Makefile.human src/sourceScanner/yylex.cc
fi;

ccbuild --addres src/ccResolutions --nodefargs --args '-std=c++0x -O2 -DVERSION=\"2.0.0\"' makefile src/ccbuild.cc > Makefile.ccbuild;

#echo "]]] A-A-P"
#aap cleanALL;
#ccbuild --addres src/ccResolutions --nodefargs --args '-std=c++0x -O2 -DVERSION=\"2.0.0\"' aap src/ccbuild.cc > ccbuild.aap;



echo "]]] MD5 sum list of source"
rm MD5SUMS
if [ -f Makefile ]; then
    make clean
fi
ccbuild md5 src/ccbuild.cc > MD5SUMS

ccbuild -C src distclean

echo "]]] Configure scripts for distribution: create, distclean, create"
sh bootstrap
./configure
sh bootstrap clean
sh bootstrap

rm -f "$YYLEX"
rm -rf autom4te.cache

echo 'You can create a test archive using: git archive --format=tar --prefix=ccbuild-test/ HEAD | gzip > /tmp/ccbuild-test.tar.gz'
echo "Version is now $VERSION"
sed -r 's/AC_INIT\(ccbuild, [0-9.]+\)/AC_INIT(ccbuild, '$VERSION')/' -i configure.in
sed -r 's/PROJECT_NUMBER         = [0-9.]+/PROJECT_NUMBER         = '$VERSION'/' -i Doxyfile
sed 's/<version>.*/<version>'$VERSION'/' -i doc/ccbuild/ccbuild.sgml
echo "Update the version by changing src/ccResolutions"
