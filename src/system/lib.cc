/*
  This file is part of ccbuild.

  ccbuild is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  ccbuild is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with ccbuild.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "system.ih"

namespace {
bool byMTime(Source const *a, Source const *b)
{
  return FileSystem::modTime(a->filename()) < FileSystem::modTime(b->filename());
}
bool sourceIsBinaryTarget(Source const *src)
{
  return src->isBinTarget();
}
}// Anon namespace


//Read: http://www-128.ibm.com/developerworks/linux/library/l-shobj/
//Make more ready for: http://www.openismus.com/documents/linux/building_libraries/building_libraries.shtml
int System::lib(std::string const &version, Source *source)
{
	Compiler cc;
	Options::extraArgs = "-fPIC " + Options::extraArgs;
	bool needLink = Options::defaultUpdate;

  vector<Source *> srcList, objectTargets, localHeaders, internalHeaders;
  
  if(source)
		srcList.push_back(source);
	else
		localSourcesInto(srcList);
  
  if(srcList.empty())
	  throw Problem(Problem::Missing, "Can't find any source files for library building");
  
	collectTargets(srcList);	//Collect sub objects

  //Remove any of the sources that are binTargets because they would introduce a second main at link time
  std::vector<Source *>::iterator last = remove_if(srcList.begin(), srcList.end(), sourceIsBinaryTarget); //I want lambda functions... I want lambda functions..
  srcList.erase(last, srcList.end());//TODO do a real check for memory leaks on this, but I think Sources will track this.


	//Seperate sources into lists
	__foreach(src, srcList)
	{
		if((*src)->isObjectTarget())
			objectTargets.push_back(*src);
		else if((*src)->isInternalHeader())
			internalHeaders.push_back(*src);
		else if((*src)->isHeader())
			localHeaders.push_back(*src);
	  //TODO: Maybe use a target identifier bitset (can be both object and main) and a switch
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
    vector<Compiler> compilers(internalHeaders.size(), cc);
    #ifdef _OPENMP
    #pragma omp parallel for
    #endif
    for(vector<Source *>::size_type i = 0; i < internalHeaders.size(); ++i)
      internalHeaders[i]->build(compilers[i]);
    //The compiler does not need to be influenced here, so we can just destroy the compilers list
	}
	else
	{
		//If we don't precompile, make sure we remove any precompiled headers in our tree
		//This will slow down the total build process... so maybe we shouldn't???
		//However, having a broken build is even worse then anything else, YES??
		//Whahaha... I say it IS.
		__foreach(src, localHeaders)
			FileSystem::rmIfExists((*src)->outputFilename());
			
		__foreach(src, internalHeaders)
			FileSystem::rmIfExists((*src)->outputFilename());
	}

  //Sort objects by mtime
  sort(objectTargets.rbegin(), objectTargets.rend(), byMTime);


  //Build the objects and add them as links to the compiler
  {//Encaps iterator
    //GOD I WANT OpenMP 3 to be here already! F the single-nowait trick, back to index...
    vector<Compiler> compilers(objectTargets.size(), cc);
    size_t numNeedLink = 0;
    #ifdef _OPENMP
    #pragma omp parallel for
    #endif
    for(vector<Source *>::size_type i = 0; i < objectTargets.size(); ++i)
    {
      //_debugLevel4("Building: " << (*src)->filename());
      if(!objectTargets[i]->upToDate())
        ++numNeedLink;
      objectTargets[i]->build(compilers[i]);
      compilers[i].rmCompileOptions();
    }

    //Test whether linking is needed
    needLink = (numNeedLink > 0 ? true : needLink);
    
    //Acuumulate the compilers
    cc = accumulate(compilers.begin(), compilers.end(), cc);
    
  }//encaps iter
  
	std::string pn = projectName(); //Project name
	
	string outputAr = "lib" + pn + ".a";
	if(! FileSystem::fileExists(outputAr))
		needLink = true;
	if(version.size() and ! FileSystem::fileExists("lib" + pn + ".so." + version))
		needLink = true;
	

  if(needLink)
  {
  		cc.ar(outputAr);
  		if(!version.empty())
  			cc.lib(".", "lib" + pn + ".so", version);
  }
  else
  {
    cerrLock.set();
  	if(Options::clearPerCommand)
  	  cerr << "\33[H\33[2J";
    cerr << "[DONE LIB]\n";
    cerrLock.unset();
  }
  return 0;
}
