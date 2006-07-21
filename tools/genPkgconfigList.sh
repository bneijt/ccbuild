#!/bin/sh
#
# Small script to generate a pkg-config list for a given package
#
# Use this script like: genPkgconfigList.sh gtkmm-2.4
# PLEASE NOTE: This creates large list. Only use when you are really lazy :-)
PACKAGE=$1
PATHS=`pkg-config --cflags "$PACKAGE"|grep -o -e '-I[^ ]*'|sed -e 's/^-I//'`

echo '# Autolis generated for ccbuild resolutions of' $PACKAGE
echo '# this file was automatically generated using:'
echo "#  $0 $@"
echo '# For more information visit: http://ccbuild.sourceforge.net'
echo '#'

for path in $PATHS; do
	echo '###'
	echo '### Autolist for headers in ' $path
	echo '###'
	(
		cd $path;
		find "$path" -type f -printf '%P\n'  \
	  |sed -e "s/\$/\\t\`pkg-config --cflags --libs $PACKAGE\`/"
	)
done;
