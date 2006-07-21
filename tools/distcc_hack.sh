#!/bin/sh
#
#  This is an unsupported hack that might
#  enable the use of ccbuild and distcc with versions
#  of ccbuild that don't support threading.
#
while [[ 1 ]];
  ccbuild --compiler distcc makefile > Makefile;
  make -j8;
  sleep 10;
done;
