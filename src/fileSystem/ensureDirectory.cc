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

#include "fileSystem.ih"

void FileSystem::ensureDirectory(std::string const &directoryName)
{
	//Check for object directory existence
  if(directoryName.size() && directoryName != "." && !fileExists(directoryName))
	{
		//S_IRUSR    00400     owner has read permission
    //S_IWUSR    00200     owner has write permission
    //S_IXUSR    00100     owner has execute permission
    cerrLock.set();
    cerr << "[MKDIR] " << directoryName << "\n";
    cerrLock.unset();
    
    if(!Options::simulate)
    {
      //Check base directory existence and create them if needed
      ensureDirectory(FileSystem::directoryName(directoryName));
      fsLock.set();
      int mdstat = ::mkdir(directoryName.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
      fsLock.unset();
			if(mdstat != 0 && !isDirectory(directoryName))
			{
        cerrLock.set();
  		  cerr << "ccbuild: Warning: Unable to create directory \"" << directoryName << "\"\n";
  		  cerrLock.unset();
		  }
		}
	}
}
