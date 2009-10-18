#!/bin/bash
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
types="png svg"
HELP="
Example of creating media files from your dot files.

 You can add arguments for dot, to the commandline of this program.

 Usage: $0 all
 Will generate files of the types: $types
 The first argument must be \"all\" to
 actually run this program.

Change the types variable for more types.
 Supported types may include:
   ps svg svgz fig mif hpgl
   pcl png jpg gif imap cmap
   ismap cmap
 (see man dot for full listing)
"
if [ "$1" != "all" ];then
	echo "$HELP"
	exit
fi

for file in `ls *.dot`; do
  for type in $types; do
    OF=$file".$type"
    echo [$type] $file "-->" $OF
    nice dot "$file" -T$type -o "$OF" $@
  done;
done;
