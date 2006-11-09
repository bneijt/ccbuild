#!/bin/sh
ccbuild distclean

echo ]]] Documentation
rm -rf doc/html
make -C doc/debiandoc

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
	exit 1;
fi;



echo ]]] MD5 sum list of source
rm -f MD5SUMS*
make clean
ccbuild md5 src/ccbuild.cc > MD5SUMS

ccbuild distclean

