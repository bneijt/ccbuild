#!/bin/sh
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
#
# Small script to generate a pkg-config list for a given package
#
# Use this script like: genPkgconfigList.sh gtkmm-2.4
# PLEASE NOTE: This creates large list. Only use when you are really lazy ;-)
HELP="Usage: $0 <pkg-config package name>"
if [ -z "$1" ];then
	echo "$HELP"
	exit
fi

PACKAGE=$1
PATHS=`pkg-config --cflags "$PACKAGE"|grep -o -e '-I[^ ]*'|sed -e 's/^-I//'`

echo '# Autolis generated for ccbuild resolutions of' $PACKAGE
echo '# this file was automatically generated using:'
echo "#  $0 $@"
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
