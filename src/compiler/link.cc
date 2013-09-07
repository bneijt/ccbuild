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
#include "compiler.ih"
int Compiler::link(std::string pwd,
                   std::string outputFile) const {
    cls();

    //TODO If arguments/object come above 32000, the we should collapse object files in the same directory
    // to *.o where possible.
    cerr << "[LINK] " << outputFile << "\n";

    string command = linkCommand(pwd, outputFile);

    int retValue = System::system(command.c_str());


    if(retValue != 0) {
        cerr << "ccbuild: Non zero exit status (" << retValue << ")\n";

        if(!Options::brute) {
            throw Problem(Problem::Subfailure, "Linking failed.", retValue);
        }

        FileSystem::rmIfExists(outputFile);
    } else if(!Options::execOnPass.empty()) {
        System::system((Options::execOnPass + " \"" + outputFile + "\"").c_str());
    }

    return retValue;
}
