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






#include "Compiler.ih"

int Compiler::compile(std::string pwd, std::string target,
		       std::string outputFile) const
{
	cls();

  cerr << "[CC] " << target << "\n";

  string command = compileCommand(pwd, target, outputFile);

	//If possible fork this... if(Options::optino<unsigned>("numThreadsLeft") > 0) fork exit(system)

 	int retValue = System::system(command.c_str());

  if(retValue != 0)
  {
    cerr << "ccbuild: Non zero exit status (" << retValue << ")\n";

    if(!Options::execOnFail.empty())
    	System::system((Options::execOnFail + " \"" + target + "\"").c_str());

    if(!Options::brute)
    	throw Problem(Problem::Subfailure, "Compilation failed on " + target, retValue);

    //Remove the output file, to make sure linking fails
    FileSystem::rmIfExists(outputFile);
  }
  else if(!Options::execOnPass.empty())
   	System::system((Options::execOnPass + " \"" + target + "\"").c_str());

	//TODO retValue is always 0, thus meaningless because of exceptions.
  return retValue;
}
