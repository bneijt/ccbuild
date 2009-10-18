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
#
#  Generate a status page, showing which files are
#   up to date and which are not.
#

TMPFILE=/tmp/ccbuild_web.$RANDOM.$$
CCBUILD=ccbuild
HTMLOF="./ccbuildstatus.html"

##HTML CONTENT

HTMLHEADER='
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
    "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" >
<head>
  <link rel="stylesheet" type="text/css" href="ccbuild.css">
  <meta http-equiv="refresh" content="5">
</head>
<body>
'

HTMLFOOTER="
</body>
</html>
"

##WORK HORSES

function createWebpage()
{
	echo "$HTMLHEADER" > "$HTMLOF";
	awk -- 'BEGIN{FS="\t";}//{if($1 == "old") print "<span class=\"old\">" $2 "</span>"; else print "<span class=\"uptodate\">" $2 "</span>";}' < "$1" >> "$HTMLOF";
	echo "$HTMLFOOTER" >> "$HTMLOF";
}


$CCBUILD $@ check > $TMPFILE
createWebpage $TMPFILE
rm $TMPFILE
