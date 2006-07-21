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
//Read: http://www-128.ibm.com/developerworks/linux/library/l-shobj/
#include "System.ih"

int System::lib(std::string const &version, Source *src)
{
	Compiler cc;
	Options::extraArgs = "-fPIC " + Options::extraArgs;
	bool needLink = Options::defaultUpdate;

  vector<Source *> srcList, objectTargets, localHeaders, internalHeaders;
  
  if(src)
		srcList.push_back(src);
	else
		localSourcesInto(srcList);
  
  if(srcList.empty())
	  throw Problem(Problem::Missing, "Can't find any source files for library building");
  
	collectTargets(srcList);	//Collect sub objects

	//Seperate sources into lists
	_foreach(src, srcList)
	{
		if((*src)->isObjectTarget())
			objectTargets.push_back(*src);
		else if((*src)->isInternalHeader())
			internalHeaders.push_back(*src);
		else if((*src)->isHeader())
			localHeaders.push_back(*src);
		//Rest are main targets, leave these out.
	}
	srcList.clear();


	if(Options::precompile)
	{
		//Also do local headers
		//This will slow the build down it the source tree uses internal headers already
		if(Options::precompileAll)
		  _foreach(src, localHeaders)
		  {
 		    _debugLevel4("Precompiling: " << (*src)->filename());
 	      (*src)->build(cc);
 	      cc.rmCompileOptions();
		  }

	  //Precompile all internal headers
	  _foreach(src, internalHeaders)
	  {
    	_debugLevel4("Precompiling: " << (*src)->filename());
      (*src)->build(cc);
      cc.rmCompileOptions();
	  }
	}
	else
	{
		//If we don't precompile, make sure we remove any precompiled headers in our tree
		//This will slow down the total build process... so maybe we shouldn't???
		//However, having a broken build is even worse then anything else, YES??
		//Whahaha... I say it IS.
		//Are you having as much fun reading this, as I'm having writing it?
		_foreach(src, localHeaders)
			FileSystem::rmIfExists((*src)->outputFilename());
			
		_foreach(src, internalHeaders)
			FileSystem::rmIfExists((*src)->outputFilename());
	}

  //Build the objects and add them as links to the compiler
  _foreach(src, objectTargets)
  {
   	_debugLevel4("Building: " << (*src)->filename());
   	needLink = ((*src)->upToDate()) ? needLink : true;
    (*src)->build(cc);
    cc.rmCompileOptions();
  }


	//Relink if any object is newer then the link target
	std::string pn = projectName(); //Project name
	
	string outputAr = "lib" + pn + ".a";
	if(! FileSystem::fileExists(outputAr))
		needLink = true;
	if(! FileSystem::fileExists("lib" + pn + ".so." + version))
		needLink = true;
	

  if(needLink)
  {
  		cc.ar(".", outputAr);
  		if(!version.empty())
  			cc.lib(".", "lib" + pn + ".so", version);
  }
  else
  {
  	if(Options::clearPerCommand)
  	  cerr << "\33[H\33[2J";
    cerr << "[DONE LIB]\n";
  }
  return 0;
}
