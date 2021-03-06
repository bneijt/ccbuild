#!/bin/bash
#This script is used to clean up the directory
#
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
cd "`dirname "$0"`"
set -e

echo "]]] Clean cmake config"
./update_cmakelists.sh clean

echo "]]] Update cmake config"
. ./update_cmakelists.sh

if [ -z "$VERSION" ]; then
    # VERSION should come from the import of update_cmakelists
    echo EMPTY VERSION FOUND
    exit 1
fi

sed -r 's/PROJECT_NUMBER         = [0-9.]+/PROJECT_NUMBER         = '$VERSION'/' -i Doxyfile
sed 's/<version>.*/<version>'$VERSION'/' -i doc/ccbuild/ccbuild.sgml

echo "]]] Update documentation"
make -C doc/ccbuild clean
make -C doc/ccbuild

rm -rf build
mkdir -p build

awk '/^\s*$/{exit}//{print}' < ChangeLog > build/release.md

echo "Version is now $VERSION"
git archive --format=tar --prefix=ccbuild-$VERSION/ HEAD | tar -xC build
cp -rf doc build/ccbuild-$VERSION
cd build
tar -czf ccbuild-$VERSION.tar.gz ccbuild-$VERSION
