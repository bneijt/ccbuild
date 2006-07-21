#!/bin/sh
#Example of creating media files from your dot files.
#
# You can add arguments for dot, to the commandline of this program.
#
# Usage: ./dot2media [dot arguments] <dot file.dot>
# Will generate png and svg file.

#All the types you want. Example: types="png svg"
# Supported types may include:
#   ps svg svgz fig mif hpgl
#   pcl png jpg gif imap cmap
#   ismap cmap
# (see man dot for full listing)
#
types="png svg"

for file in `ls *.dot`; do
  for type in $types; do
    OF=$file".$type"
    echo [$type] $file "-->" $OF
    nice dot "$file" -T$type -o "$OF" $@
  done;
done;
