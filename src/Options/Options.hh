/*
	ccbuild - A strict developer's build utility
	Copyright (C) 2005  A. Bram Neijt <bneijt@gmail.com>

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef _Options_HH_INCLUDED_
#define	_Options_HH_INCLUDED_

#include <string>
#include <vector>
namespace bneijt
{
/**\brief A collection of static variables containing options

	
*/
struct Options
{
	static std::string version;				///<The version
	static std::string CC;				///<The compiler command
	static std::string execOnPass;				///<XOP option
	static std::string execOnFail;				///<XOF option
	static std::string extraArgs;				///<Arguments given with --args
	static std::string commandAppend;				///<To append to every compiled command (--append)
	static std::string homepage;				///<The homepage to mention in scripts
	static std::string progVersion;				///<The version (of the library) as given by --version.


	static bool md5;				///<Wether to use MD5 checks
	static bool simulate;				///<Wether we are running a simulation
	static bool precompile;				///<Use precomiplation
	static bool precompileAll;				///<Precompile all
	static bool verbose;				///<Wether to be verbose
	static bool defaultUpdate;				///<Wether the force option is given
	static bool highlight;				///<Wether to highlight g++ output
	static bool showCommands;				///<Wether to show commands (part of verbose)
	static bool brute;				///<Brute flag
	static bool clearPerCommand;				///<Clear per command flag
	static bool loadGlobalRes;				///<Global resolution loading flag
	static bool xml;				///<Wether to produce xml where possible
	static bool interAr;				///<Wether to archive inbetween compile and link

	static bool makefileHeaderDone;				///<Wether the Makefile header has been outputted
	static bool aapHeaderDone;				///<Wether the A-A-P header has been outputted
	
	static std::vector<std::string> includePaths;				///<A list of include paths (-I)
	static std::vector<std::string> extraResolutions;		///<Extra resolution files given with --addres
};
}//Namespace
#endif

