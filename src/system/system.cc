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

int System::system(std::string const &command, bool simulate) throw (Problem) {
    boost::circular_buffer_space_optimized<string> output(1024);
    if(Options::showCommands) {
        cout << command << "\n";
    }

    //Run command caching output
    int status = 0;
    _debugLevel3((simulate ? "Simulation on" : "Simulation off"));
    if(!simulate) {
        //TODO Replace popen with fork/exec/dup2 to redirect more cleanly?
        //     or find another way to handle the redirect of stderr
        FILE *processOutputDescriptor = popen(command.c_str(), "r");
        if(processOutputDescriptor == NULL) {
            //TODO read errno here
            throw Problem(Problem::Unable, "The fork(2) or pipe(2) calls failed, or we cannot allocate memory");
        }
        char buffer[1024];

        while (fgets(buffer, sizeof(buffer), processOutputDescriptor)) {
            output.push_back(string(buffer));
        }
        if(ferror(processOutputDescriptor) != 0) {
            output.push_back("PLEASE NOTE: the subprocess output stream ended with an error status.");
        }
        status = pclose(processOutputDescriptor);
        if(status == -1) {
            throw Problem(Problem::Unable, "Popen was unable to read the child exit status");
        }
    }

    if(output.size() > 0) {
        cerrLock.set();

        //Highlight ON
        if(Options::highlight) {
            cerr << "\x1b\x5b\x33\x31\x6d";    //\e[31m
        }

        copy(output.begin(), output.end(), ostream_iterator<string>(cerr));

        //Highlight OFF
        if(Options::highlight) {
            cerr << "\x1b\x5b\x30\x6d";    //\\e[0m
        }

        cerrLock.unset();
    }

    //On normal termination return the exit status, otherwise throw a problem
    if(!WIFEXITED(status)) {
        throw Problem(Problem::Suberror, "Abnormal sub process termination", WEXITSTATUS(status));
    }
    return WEXITSTATUS(status);
}
