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

void System::batchCompile(std::vector<Source const*> &batchList, Compiler const &cc_const)
{
  cerrLock.set();
  cerr << "[BATCH " << batchList.size() << "]\n";
  cerrLock.unset();

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


  //Clean up any -Isomething to make sure it is a complete absolute path
  //   (we are chdirring later)
  std::vector<std::string> newArgs = cc.compileArguments();

  //Append the extra args and make them temporarily empty
  istringstream extraOpts(Options::extraArgs);
  copy(std::istream_iterator<std::string>(extraOpts), std::istream_iterator<std::string>(), back_inserter(newArgs));
  
  for(size_t i = 0; i < newArgs.size(); ++i) //in place translate
  {
    String const arg(newArgs[i]);
    _debugLevel3("Testing for -I argument in: " << arg);
    if(!arg.startsWith("-I"))
      continue;
    if(arg.startsWith("-I/"))
      continue;
    _debugLevel1("Translating -I argument: " << arg);
    
    //Do the right thing and translate -I path into -I absolute path
    newArgs[i] = "-I" + FileSystem::absolutePath(arg.substr(2));
    _debugLevel1("Translated argument into: " << newArgs[i]);
  }
  cc.rmCompileOptions();
  __foreach(arg, newArgs)
    cc.addArgument(*arg);

  

  //Create a temporary directory
  std::string tmpDir = System::mkdtemp("/tmp/ccbuild_batch.XXXXXX");
  
  //Create the command we need to run
  std::string command;
  {
    _debugLevel2("Options::extraArgs=" << Options::extraArgs);
    With<std::string> temporarily(Options::extraArgs, ""); //Scoped change of extraArgs to ""
    _debugLevel2("Options::extraArgs=" << Options::extraArgs);
    command = cc.compileCommand(srcNames);
  } 
  _debugLevel2("Options::extraArgs=" << Options::extraArgs);
  //chdir, compile, chdir
  std::string const cwd(FileSystem::cwd());
  if(System::changeTo(tmpDir) == false)
    throw Problem(Problem::Unable, "Unable to change to \"" + string(tmpDir) + "\" for batch compilation");
  try
  {
    System::system(command);
  }
  catch(Problem const &p)
  {
    if(p.id() != Problem::Suberror)
      throw;
  }
  
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
  FileSystem::rmDirectoryIfExists(tmpDir);
  return; //Destroy all knowledge of ever doing this
}
