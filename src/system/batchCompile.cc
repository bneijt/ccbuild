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

/*
void Source::buildObjectTarget(Compiler &cc)
{
  OpenMP::ScopedLock slock(d_apiLock);

  vector<Source *> srcList;
  vector<string const*> globalList;
	dependencies(srcList, globalList);

  Resolver &resolver = Resolver::getInstance();
  //Resolve all globals into the compiler
  __foreach(global, globalList)
  	resolver.resolveInto(*global, cc);

  if(!upToDate(srcList))
  {
  	//Need an update
	  string outputDirectory = FileSystem::directoryName(outputFilename());//OLD directory() + "/o";

	  //Check for object directory existence (exists("o"))
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
			__foreach(src, srcList)
				collectedHash += md5i.contentHash((*src)->filename());
			
			md5i.save(filename(), collectedHash);
		}
  }
  //Add my object to the list of objects in the compiler.
  cc.addObject(outputFilename());
}




*/


void System::batchCompile(std::vector<Source const*> &batchList, Compiler const &cc_const)
{
  //Make a copy of the compiler, we want this to be compiler read-only
  Compiler cc(cc_const);
  
  //Generate a list of dependencies and globals for all the files
  vector<Source *> srcList;
  vector<string const*> globalList;
  vector<string > srcNames;
  __foreach(src, batchList)
  {
  	(*src)->dependencies(srcList, globalList);
  	srcList.clear();
  	//Add this source to the batch names
  	srcNames.push_back(FileSystem::absolutePath((*src)->filename()));
  }

  //Resolve all globals into the compiler  
  Resolver &resolver = Resolver::getInstance();
  __foreach(global, globalList)
  	resolver.resolveInto(*global, cc);

  //Create a temporary directory
  std::string tmpDir = System::mkdtemp("/tmp/ccbuild_batchXXXXXX");
  
  //Create the command we need to run
  std::string command = cc.compileCommand(srcNames);
  
  //chdir, compile, chdir
  std::string const cwd(FileSystem::cwd());
  if(System::changeTo(tmpDir) == false)
    throw Problem(Problem::Unable, "Unable to change to \"" + string(tmpDir) + "\" for batch compilation");
    
  System::system(command);
  if(System::changeTo(cwd) == false)
    throw Problem(Problem::Unable, "Unable to change back to our starting working directory after batch compilation\n\tTried to go to: " + cwd);
  
  //Search through the created objects and make sure we update the MD5 of all the objects that worked out well
  vector<string > objectList;
  FileSystem::globInto(&objectList, string(tmpDir) + "/*.o");
  __foreach(oFile, objectList)
  {
    //Copy to the right location
    //Find the source that this object file is ment to be part of
    std::string oBaseName = FileSystem::baseName(*oFile);
    oBaseName = oBaseName.substr(0, oBaseName.size() -2);//Strip .o extension
    Source const *oSource(0);
    //Find the source with the correct output name
    __foreach(src, batchList)
      if((*src)->basenameWithoutExtension() == oBaseName)
      {
        oSource = *src;
        break;
      }
    if(oSource == 0)
      throw Problem(Problem::Unable, "Not able to find the batch source which resulted in: " + *oFile);
    
    //Move to the right location using the src->outputFilename ot find the right place
    FileSystem::rename(*oFile, oSource->outputFilename());
    //Update the source's MD5
    oSource->markAsDone();
  }

  //Collect the global headers of all the objects, and resolve them all
  //Make sure you collect
}
