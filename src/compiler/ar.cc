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

int Compiler::ar(std::string target) const {
    //Construct ar command
    //  ar [--plugin name] [-X32_64] [-]p[mod [relpos] [count]] archive [member...]
    ostringstream command("ar qcs ", ios::ate);
    command << " " << target;

    __foreach(obj, d_objects)
    command << " \"" << (*obj) << "\"";

    cls();

    //Remove the output file
    FileSystem::rmIfExists(target);
    cerrLock.set();
    cerr << "[AR] " << target << "\n";
    cerrLock.unset();

    //Run ar command
    int retValue = System::system(command.str().c_str());


    if(retValue != 0) {
        cerrLock.set();
        cerr << "ccbuild: Non zero exit status (" << retValue << ")\n";
        cerrLock.unset();

        if(!Options::brute) {
            throw Problem(Problem::Subfailure, "Ar failed to create " + target, retValue);
        }
    }

    return retValue;
}
