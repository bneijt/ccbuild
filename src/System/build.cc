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

#include "System.ih"

void System::build(Source *source)
{
	Compiler cc;
	build(source, cc);
}

void System::build(Source *source, Compiler &cc)
{
  bool needLink = Options::defaultUpdate || forceLink;

  vector<Source *> srcList, objectTargets, localHeaders, internalHeaders;
  
	srcList.push_back(source);
	collectTargets(srcList);

	//Seperate sources into lists
	__foreach(src, srcList)
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
	  __foreach(src, localHeaders)
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
		__foreach(src, localHeaders)
			FileSystem::rmIfExists((*src)->outputFilename());
			
		__foreach(src, internalHeaders)
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


	//Build the binTarget object if needed
  needLink = (source->upToDate()) ? needLink : true;



	//Relink if any object is newer then the link target
	string outputFilename = source->directory() + "/" + source->basename();
	if(! FileSystem::fileExists(outputFilename))
		needLink = true;

  if(needLink)
  {
  	forceLink = true;	//Force linking of other builds
		if(! cc.objects().empty() && Options::interAr)
		{
	  	//Archive, clear object, add archive, links
  		FileSystem::ensureDirectory(source->directory() + "/o");
			cc.ar(source->directory() + "/o", source->basename() + ".ar.o");
			cc.rmObjects();
			
			//Add archive as object to compiler
  		cc.addObject(source->directory() + "/o/" + source->basename() + ".ar.o");
		}
		
		//Build the main source
  	source->buildBinTarget(cc);
  	
    cc.link(source->directory(), outputFilename);
  }
  else
  {
  	if(Options::clearPerCommand)
  	  cerr << "\33[H\33[2J";
    cerr << "[DONE]\t" << source->filename() << "\n";
  }
}
