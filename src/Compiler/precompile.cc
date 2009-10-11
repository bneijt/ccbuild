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

int Compiler::precompile(std::string pwd, std::string target,
		       std::string outputFile) const
{
	cls();

  cerr << "[PREC] " << target << "\n";

  string command = precompileCommand(pwd, target, outputFile);

 	int retValue = System::system(command.c_str());


  if(retValue != 0)
  {
    cerr << "ccbuild: Non zero exit status (" << retValue << ")\n";

    if(!Options::execOnFail.empty())
    	System::system((Options::execOnFail + " \"" + target + "\"").c_str());

    if(!Options::brute)
    	throw Problem(Problem::Subfailure, "Precompilation failed on " + target, retValue);    
	    
	  //Remove output, to make sure the gch is not used by g++
	  FileSystem::rmIfExists(outputFile);
  }
  else if(!Options::execOnPass.empty())
   	System::system((Options::execOnPass + " \"" + target + "\"").c_str());

  return retValue;
}
