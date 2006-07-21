#!/bin/sh

#
#  Generate a true man compiler output webpage...
#  Simple example script, not as usefull as it might become
#    with allot of additions....
#

TMPFILE=/tmp/ccbuild_trueman.$RANDOM.$$
CCBUILD=./bb
HTMLOF="./trueman.html"

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
	awk -- 'BEGIN{FS="\t";}//{if($1 == 0) print "<span class=\"passed\">" $2 "</span>"; else print "<span class=\"passed\">" $2 "</span>";}' < "$1" >> "$HTMLOF";
	echo "$HTMLFOOTER" >> "$HTMLOF";
}


while [[ 1 ]];
	do
	$CCBUILD --brute --real-man > $TMPFILE
	createWebpage $TMPFILE;
	exit;
done;
rm $TMPFILE;
