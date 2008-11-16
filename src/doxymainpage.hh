/*
  ccbuild - A strict developer's build utility
  Copyright (C) 2008  A. Bram Neijt <bneijt@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

//		THIS FILE IS ONLY HERE FOR DOCUMENTATION PURPOSES
/**
   \mainpage ccbuild
   See the ccbuild homepage at: <a href="http://ccbuild.sourceforge.net">http://ccbuild.sourceforge.net</a>
   \section intro_sec Introduction
  
   ccbuild is a simple build utility. It is site specific (not multiplatform) and probably Linux specific. This however, adds some additional simplicity to the compilation of your source.
  It's this simplicity which allows the automization.
  
   \section probs_sec Problems it should solve
  One of the main things this program should solve is removing scripts. Scripts for building are
  nice and editable, but adding filenames to them is a bore. My source should be enough for the
  system to be able to resolve the compiler arguments that it needs to pull it of.
  
  Currently most systems doing the same as ccbuild generate scripts. Mostly using script languages.
  These are mostly slow (scripts running generating and then running scripts takes time), and
  sometimes made you define magic variables somewhere to keep them running.
  
  ccbuild is very demanding on your source, but fast and simple to use. Also, source tree cluttering
  should be avoided at all times.
  
   \section progflow_sec Program flow
  The program should be called from a place where the source directory resides: "src".
  
  ccbuild identifies 5 file types:
  	- Binary targets (source files with an "int main(" function)
  	- Object targets (source files wich are not binary targets)
  	- Internal headers (files with an ".ih" extension)
  	- Headers (None of the above)
  	- Global headers (Anything included using "#include &lt;...&gt;")
  
  When run, ccbuild will look at the current directory:
  	- For all binary targets
  		- Read the source, follow local includes
  			- Scan and use local includes
  			- Scan and use all object targets next these local
  		- Use global includes to determine extra commanline arguments
  		- Precompile (internal headers or all)
	  	- Compile
  		- Link
 
  
  \subsection dependencies	ccbuild dependencies
  Compile time:
   - flex 2.5.31	(newer might work, this is the version that I use)
   - As of >= 1.5.7 this is going to change.. please read the README

  \section hacking Hacking the ccbuild source
  \subsection link_ident Linker argument detection
  Currently linker argument detection is done in the Compiler class with the bneijt::Compiler::countFirstLinkerArguments function.
  \subsection hack_add_res Adding resolver functionality
  	To add or change the way the global header resolutions are done, or the arguments are parsed, see the resolve function in the Resolver class.
  	
  \subsection hack_add_cmd Adding commands
   	To add a command, add it to the large if statement in ccbuild.cc and then add a static function to the System class.
     To see an example of how to use the dependencies generated, read the makefileFor function ( System/makefileFor.cc ).
*/
