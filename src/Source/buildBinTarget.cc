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

#include "Source.ih"
void Source::buildBinTarget(Compiler & cc)
{
  _debugLevel4("Output filename: " << outputFilename());

  vector<Source *> srcList;
  vector<string *> globalList;
	dependencies(srcList, globalList);
  Resolver &resolver = Resolver::getInstance();

  //Resolve all globals into the compiler
  _foreach(global, globalList)
  	resolver.resolveInto(*global, cc);


	if(!upToDate(srcList))
  {	//Need an update

	  string outputDirectory = directory() + "/o";

	  //Check for object directory existence (exists("o"))
	  _debugLevel2("Ensure " + outputDirectory);
	  FileSystem::ensureDirectory(outputDirectory);

    //Now, we have a compiler with all the objects in it.
    int ret = cc.compile(directory(), d_filename, outputFilename());
    //Compilation OK
		//Update hash
		if(Options::md5 && ret == 0)
		{
			MD5Info &md5i = MD5Info::getInstance();
			string collectedHash = md5i.contentHash(filename());
			
			vector<Source *> srcList;
			dependencies(srcList);
			_foreach(src, srcList)
				collectedHash += md5i.contentHash((*src)->filename());
			
			md5i.save(filename(), collectedHash);
		}
  }
	
  //Now all local children are build, so now we can build our own functions.
  //compile me
  //Add my object to the list of objects in the compiler.
  cc.addObject(outputFilename());
}
