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


ccbuild distclean

echo ]]] Documentation
rm -rf doc/html
make -C doc/ccbuild

YYLEX=src/SourceScanner/yylex.cc
ROOT=$PWD




echo ]]] Make and A-A-P scripts
if [ -f $YYLEX ];	then
	aap cleanALL;
	
	ln -s src/ccResolutions;
	ccbuild --nodefargs --args -O2 makefile src/ccbuild.cc > Makefile.ccbuild;
	ccbuild --nodefargs aap src/ccbuild.cc > ccbuild.aap;
	rm -f ccResolutions;
	
	cd $ROOT;
else
	echo NO YYLEX.cc FOR SCRIPT GENERATION;
	echo use "make -f Makefile.human src/SourceScanner/yylex.cc"
	exit 1;
fi;



echo ]]] MD5 sum list of source
rm -f MD5SUMS*
make clean
ccbuild md5 src/ccbuild.cc > MD5SUMS

ccbuild distclean

echo ]]] Configure scripts for distribution: create, distclean, create
sh bootstrap
./configure
sh bootstrap clean
sh bootstrap

rm $YYLEX
rm -rf autom4te.cache
