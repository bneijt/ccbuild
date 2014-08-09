% ccbuild(1) General Commands Manual
% A. Bram Neijt <bneijt@gmail.com>
% August 8, 2014

# NAME

ccbuild — Strict C++ developer's build utility

# SYNOPSIS

**ccbuild** [options]  [command]

# DESCRIPTION

**ccbuild** is a build utility that will read C++ source. It collects all
source surrounding your local includes and links  these  to  your  main
program. Global  include statements (#include <something>) are used to
make sure the compiler gets the` right arguments. The link between  com‐
piler  arguments  and these global includes is made using configuration
files. These files contain lines with a global header file name and the
extra  arguments the compiler needs to find and use this file. The file
name and arguments are  separated  by  tab  character(s)  or  a  space.
ccbuild  reads  these configuration files in order. Only the first men‐
tion of a global header file in  these  files  is  used.  Usually  only
**./ccResolutions** is used, but there are more possibilities. See the sec‐
tion FILES for more information.

**ccbuild** will follow any local include (#include "something.hh") to  try
to  find more source code to compile. To keep **ccbuild** from following up
on an include statement, separate the #-sign and the include  statement
by a single space ("# include").

# COMMANDS

build [filename.cc]
:   Build everything or the given source.

lib [filename.cc]
:   Collect  all  objects into an archive. If a version is given,
    using --pversion, then a shared library is  also  build  with
    symbolic  links.  This  currently  forces  the -fPIC argument
    addition. The name of your library is given the name  of  the
    current  directory  or it's parent when the current directory
    is called src.

    Example: create an empty .cc file which simply  includes  all
    the  local  libraries, run ccbuild --pversion 0.0.1 lib that‐
    file.cc

clean [filename.cc]
:   Clean everything or the given source.

distclean
:   Recursively remove all "o"  directories  after  removing  all
    .md5 and .o files therein. And removes all .gch files.

deps [filename.cc]
:   List  all  files this source depends on. It lists three lines
    separated by empty  lines.   The  first  contains  the  local
    dependencies,  the  second the ignored headers (for the file)
    and the last contains all global includes needed.

dot [filename.cc]
:   Generate dot graph files for sources on  the  stdout.  If  no
    source file name is given, then for all binary targets in the
    local directory a .dot file will be created. If the --verbose
    flag  is used the dot graph will also contain all object file
    names and their dependencies and lists  of  ignored  headers.
    Objects  will  be  coloured  light grey, binary targets light
    blue, ignored headers by a red line.

makefile [filename.cc]
:   Generate a Makefile on stdout. If no file name is  given,  an
    all  rule will be generated. Otherwise only the rules for the
    given file are generated.

aap [filename.cc]
:   Generate an A-A-P file on stdout. If the  file  name  is  not
    given,  an "all" rule will be added and all local binary tar‐
    gets will be listed.

check [filename.cc]
:   Display source status and file name on the stdout. Status  and
    source  path  are  separated  with a tab character. Status is
    either "old" or  "ok".  When  the  --verbose  flag  is  used,
    another  tab  separated  column will be inserted containing a
    two letter file type ccbuild identifies it as. This file type
    is "bt", "ot", "ih" or "hh" for binary target, object target,
    internal header and header respectively.

icmake [filename.cc]
:   icmake slave mode. This will output the used directories with
    one  directory per line. If a CLASSES file already exists, it
    will only output the class directories not mentioned  in  the
    CLASSES  file.  If  --verbose  is  given, all classes will be
    listed. The output will not  contain  directories  with  only
    header  files. Updating the CLASSES is typically done by run‐
    ning: ccbuild icmake >> CLASSES

resolve [filename.cc]
:   Print all unresolved globals onto the stdout  followed  by  a
    tab  character.  These  can  be appended to the ccResolutions
    file using: ccbuild resolve >> ccResolutions .

md5 [filename.cc]
:   MD5 sum all sources needed to compile all binary targets,  or
    the given source on stdout.

# OPTIONS
Options are used to change the behaviour of the commands. Some  options  are
useless for some commands.

-f --force-update
:   Update everything by labelling everything as old.

-h --help
:   Get a list of options and commands.

--gnutouch
:   Touch files part of the GNU software standard. They will be touched
    in ../ except when there is a directory called src in  the  current
    directory, then the current directory will be used. This will touch
    AUTHORS, NEWS, README, INSTALL, COPYING, TODO and ChangeLog.

-s --no-act
:   Simulate, don't really execute any writing commands.

--compiler cmd
:   Set the compiler command. The default is "g++".

-a --args argument
:   Set these default compiler arguments, removing the standard default
    arguments  ("-Wall  -g"). Multiple uses of this option are concate‐
    nated with spaces.

-C path
:   Change directory before anything else.

-p --precompile-ih
:   Pre-compile only internal headers. This requires  g++  version  3.4
    up.

--precompile-all
:   Pre-compile both internal headers and normal headers. This requires
    g++ version 3.4 up. When you use internal headers, this  will  only
    slow  you  down. However, when you don't use internal headers, this
    pre-compilation is all you've got.

--brute
:   Continue on compiler errors.

--md5
:   Use MD5 hashes to check for file changes. The hashes are  store  in
    "o/filename.md5" for every file. These sums are only stored after a
    clean exit from ccbuild (last line showing "[WR] MD5  data")  or  a
    successful compilation.

-I path
:   Add  this  path to the local include search path of ccbuild and the
    compiler (which will receive the same argument).

--recursive-include path
:   This is just like -I, but for the given path  and  every  non-empty
    directory  with a name other then "o". Make sure you do not come to
    depend on this behaviour, that would be bad practice.

-l --highlight
:   Highlight the output of the compiler using a red terminal colour.

--xof --exec-on-fail command
:   Execute this command when the command (pre)compilation returns any‐
    thing but 0.  The first argument given to the command will be rela‐
    tive path to the file the command was executed on (which is  either
    a  C++  source  or header). If you don't want to use the file name,
    you can append an echo command like "sleep 2; echo".

--xop --exec-on-pass cmd
:   This is the same as --exec-on-fail, except it only works  when  the
    command  returns 0. The first argument given to the command will be
    the relative path to the file the command was executed on.

--clearpc
:   Clear the screen just before executing the command (clear per  com‐
    mand).

--append cmd
:   Append  this  to every command. This can be used to redirect output
    or set up pipes for compiler output.

--loop
:   Loop the system with one second intervals. This only works for  the
    build  command  at the moment.  All sources who are touched will be
    reloaded. If a file is removed, the whole source tree is reloaded.

--nodefargs
:   Do not read the first line of ./ccResolutions for extra arguments.

--nodefres
:   Do not load any ccResolutions  files  outside  of  ./ccResolutions.
    This  can be used to create a monolithic ccResolutions file or dis‐
    cover your project's dependencies with the resolve command.

--addres filename
:   Load the given resolution file before any other.

--pversion version
:   Set the program version you are working on to version. This is cur‐
    rently only used for the library command. When defined, the library
    command can make a shared object (.so) and symbolic links by  using
    the  version  number. It should not contain any file system special
    characters like slashes.

--ar
:   Archive the objects before linking. This should reduce  the  binary
    size because it leaves out unused objects.

--verbose
:   Show commands and produce more output for dot and check commands.

-V --version
:   Output version number on stdout and copyright/license on stderr.

--xml
:   Output  in  XML  where  supported. Currently this is only the check
    command.

--nowarn
:   Leave out most warnings.

--batch
:   Compile a batch of files with one g++ call before any other  compi‐
    lation.  This  effectively  disables  any  multi-threading, but may
    speed things up for larger collections of small files. This process
    involves creating a temporary directory in /tmp/ccbuild_batch.XXXX.
    The exact behaviour of this option may change in the  future  based
    on performance results and user experience.

-j number_threads
:   Set the maximum number of threads used during build. Only available
    when OpenMP is enabled.

# RESOLUTION CONFIGURATION

The ccResolutions file links global headers to compiler arguments. Every line
should  be either empty, start with a comment character "#" or contain a con‐
figuration line.  A configuration  line  contains  the  name  of  the  global
header,  followed by one or more tab characters and then the additional argu‐
ments needed when a source depends on this global header.  The arguments  are
POSIX shell expanded.

If  the  first  line  of the ccResolutions file starts with "#&", the rest of
this line is shell expanded and used and appended to  the  argument  list  of
*ccbuild*.

# EXAMPLES

Examples of program use.

ccbuild resolve >> ccResolutions
:   Add  any  of  the unknown global headers to the ccResolutions file.
    You can also use --nowarn to keep ccbuild quiet, but you will  have
    to think twice if you get compilation errors.

ccbuild --brute
:   Get back to development after a distclean. This will update as much
    objects as will compile. Which will  allow  you  to  focus  on  the
    errors in the next ccbuild call.

ccbuild -p --compiler 'g++-3.4' --args -Wall --args '-Wextra -ansi'
:   Precompile  internal  headers  using g++-3.4 and highlight all com‐
    piler output (-l). Also give all compiler commands  the  parameters
    "-Wall -Wextra -ansi".

ccbuild -f --args -O3
:   Recompiling  your project for benchmarking tests. Forces the update
    of all code (-f) and sets the compiler argument to -O3.

ccbuild --verbose dot; dotty *.dot
:   Graph the dependencies for all programs  with  colours.  Then  view
    these  using  dotty. This can help you to discover irregular depen‐
    dencies and what test programs use.

ccbuild --xof 'gedit'
:   Try to compile the program and open the first file  that  does  not
    compile  correctly. Open all error producing sources in gedit. Very
    useful for when you change the interface of a class.

ccbuild --compiler distcc -j 20
:   Use 20 distcc compilers to compile the project.

# FILES
Configuration files used by ccbuild

./ccResolutions[.USERNAME,.HOSTNAME,.KERNEL_NAME,.MACHINE,]
:   Local configuration which is project specific.  It  will  load  the
    first   existing  file  of:  ./ccResolutions.USERNAME,  ./ccResolu‐
    tions.HOSTNAME,      ./ccResolutions.KERNEL_NAME,       ./ccResolu‐
    tions.MACHINE,  ./ccResolutions.  Hostname, kernel name and machine
    can be found with uname -nsm.

~/.ccbuild/ccResolutions
:   Global configuration file.

~/.ccbuild/ccResolutions.d
:   The resolution configuration directory. All files in this directory
    are considered configuration files.

# CAVEATS
Do not place any file into o directories, these will be removed when using the
distclean command. Also don't use files with the same basename, but different
C++ extensions, this will give problems with the objects created (for example
"add.cc" and "add.cpp" in the same directory).

Currently there is no way to allow one object file to effect the command-line
parameters  of  another. This means that if all objects need a flag, you must
use the --args argument and cannot use a global header resolution line. Exam‐
ples  of  these  flags  that  need  to  be  defined everywhere are -pthreads,
-mthreads and -threads. Please read the g++ manual for  more  information  on
usage of flags.

ccbuild seems to be incompatible with flex 2.5.4. That version of flex places
an int main function in the resulting scanner and there doesn't seem to be  a
way to stop it from mentioning it. The result is that ccbuild will think that
the generated scanner is a test program for your class and won't link it into
the  main program. A solution is to move to a newer version of flex or find a
way to remove the int main function from the resulting scanner file.

# REPORTING BUGS
Report any issue with ccbuild at: https://github.com/bneijt/ccbuild

# RESTRICTIONS
ccbuild will not follow or act on any include statements with a single  space
between  the  #-sign and the include. So all include statements starting with
"# include" will be ignored, all other combinations will be acted on. This is
a  feature,  not  a  bug.  In verbose mode (--verbose) these are mentioned as
warnings.

# SEE ALSO

`pkg-config`(1), `dotty`(1), `make`(1), `icmake`(1), `g++`(1), `aap`(1), `svn`(1)
