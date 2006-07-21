
##
#This script should give a list of options we might encounter in the Compiler/addArguments function

PKG=pkg-config
$PKG --list-all |awk -- "//{system(\"$PKG --cflags --libs \" \$1); }" |sed -e "s/ \-/\n-/g"| sort --unique
echo
echo ======
echo
$PKG --list-all |awk -- "//{system(\"$PKG --cflags --libs \" \$1); }"

