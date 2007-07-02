#!/bin/bash

#
#  Generate a status page, showing which files are
#   up to date and which are not.
#

TMPFILE=/tmp/ccbuild_trueman.$RANDOM.$$
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
