ccbuild: A strict developer's build utility
===========================================

    by A. Bram Neijt <bneijt@gmail.com>

See [INSTALL](INSTALL) for installation instructions.

Thank you for downloading `ccbuild`!

![Travis CI build status](https://api.travis-ci.org/bneijt/ccbuild.svg)


Documentation
-------------
All documentation can be found in the doc directory. If you want to hack ccbuild, don't forget to run `doxygen` first.
You can also use the online versions of these documents via the homepage, most easily found using [http://www.logfish.net/pr/ccbuild/](http://www.logfish.net/pr/ccbuild/)


Program usage
-------------
The program is meant to be run in the same directory as your main program resides.
For ccbuild self, this is the src directory.
The default behaviour of ccbuild is to find any sourcefile containing an `int main` function and start compiling it.

If the manual is not installed, use: `man ./doc/debiandoc/ccbuild.1`

see `ccbuild -h` for an overview of the possible options.


Directories
-----------

    ./src     The main source tree of ccbuild
    ./doc     Documentation
    ./tools   Currently contains only a one-liner to run dot on .dot files.
    ./test    A collection of class testing programs, not really usefull.

Examples of use
---------------
* Compile for debugging and development: `ccbuild`
* When recompiling for benchmark (force recompile, use `-O3`):
       `ccbuild -f --args -O3`
* Generate a `Makefile` for a friend developer, who hasn't got `ccbuild`: `ccbuild makefile > Makefile`
* Look at the dependencies for you program(s): `ccbuild deps`
* Graph the dependencies: `ccbuild dot; dotty *.dot`
* Clean up the generated `.o` files for all local programs: `ccbuild clean`
* Remove all `.o` files and `.gch` files, before making a backup or release: `ccbuild distclean`

DON'T DO THIS WHEN USING CCBUILD
--------------------------------
These are very obvious, but just to overcome any problems that might occur.

The following is a list of things you shouldn't do when using ccbuild:

* Place important documents or sources in the directory called `o`.
  This directory will be removed without warning when calling `ccbuild distclean`.
* Don't mix extensions for files with the same basename. So don't place
  a file called "main.cc" in the same directory as "main.cpp" because the
  object files in the `o` directory won't be seperated.
* Don't expect any warrenty of any kind (read the license).

Hacking the code, possible start-up problems
--------------------------------------------

`ccbuild` development requires `ccbuild` to generate basic
build files for `autotools`. For source releases this has
been done using `bootstrap`. If you do not have a `ccbuild`
release working yet, you can use

    make -f Makefile.ccbuild src/ccbuild

to build ccbuild using a generated Makefile.

Another option is using `cmake` which is used in the [Travis-CI build](https://travis-ci.org/bneijt/ccbuild).

* Flex scanner may need to be generated, use:

        rm src/sourceScanner/yylex.cc; make -f Makefile.human src/sourceScanner/yylex.cc

  Use this if the compiler complains about something with `SourceScanner`
* If the compiler complains about `FFB::Process` constructor called incorrectly,
  make sure you have `libbobcat 2.02.03` or higher.
