#!/bin/sh

echo "#"
echo "#"
echo "#        Small install script"
echo "# This program is distributed in the hope that it will be useful,"
echo "# but WITHOUT ANY WARRANTY; without even the implied warranty of"
echo "# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
echo "#"
echo "#"

make -j2 || exit 1;
strip -s ccbuild;

function binDir()
{
  #Determine BINDIR
  #Find another installation directory
  IFS=":"
  for path in $PATH;
    do
    if [ -d "$path" ];
    then if [ -w "$path" ];
    	then echo $path;
			return 0;
		fi;
  	fi
  done;
	return 1;
}

BINDIR=`binDir || echo /usr/local/bin`
PROGRAM="src/ccbuild"
DEFCONF="./tools/ccResolutions.d"
CONFDIR="$HOME/.ccbuild"



echo
echo Install directory: $BINDIR
echo Config directory:  $CONFDIR
echo
echo "Do you want to continue with installation? (yes/no)"
read REPLY
if [[ "x$REPLY" != "xyes" ]];
  then
  echo Reply "\"$REPLY\"" isn\'t \"yes\"
  echo EXIT
  exit 1;
fi;

mkdir -p $CONFDIR

echo cp -r $DEFCONF $CONFDIR
cp -r $DEFCONF $CONFDIR

echo cp $PROGRAM $BINDIR
cp $PROGRAM $BINDIR

