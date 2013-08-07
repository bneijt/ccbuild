#!/bin/sh
##
#  This file is part of ccbuild.
#  Copyright (C) 2013  A. Bram Neijt <bneijt@gmail.com>

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
#This script should give a list of options we might encounter in the Compiler/addArguments function
#This script is for debugging purposes only

PKG=pkg-config
$PKG --list-all |awk -- "//{system(\"$PKG --cflags --libs \" \$1); }" |sed -e "s/ \-/\n-/g"| sort --unique
echo
echo ======
echo
$PKG --list-all |awk -- "//{system(\"$PKG --cflags --libs \" \$1); }"

