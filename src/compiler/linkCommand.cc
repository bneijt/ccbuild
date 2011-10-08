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

/*
//PART OF > 30000 objects code
namespace {
bool sameDirectory(string const &rvalue, string const &lvalue)
{
	return FileSystem::directoryName(rvalue) == FileSystem::directoryName(lvalue);
}
}//Anon namespace
*/

string Compiler::linkCommand(std::string pwd,
			std::string outputFile) const
{

  ostringstream command(d_baseCommand, ios::ate);
  command << " " << Options::extraArgs << " ";


  __foreach(obj, d_objects)
    command << "\"" << (*obj) << "\" ";

  copy(d_link.begin(), d_link.end(), ostream_iterator<string>(command, " "));

  command << "-o \"" << pwd << "/" << outputFile << "\" ";

/*	//checking the maximum length of command line arguments... 32768
	//THIS BLOCK MUST BE BEFORE _foreach(obj, d_objects) line
	//TODO If arguments/object come above 30000, the we should collapse object files in the same directory
	// to *.o where possible.
	static const unsigned maxObjectCount(30000);
	if(d_objects.size() > maxObjectCount)
		sort(d_objects.begin(), d_objects.end());

	while(d_objects.size() > maxObjectCount)
	{
		cerr << "OBJECTS REACH MAXIMUM!!";
		pair< vector<string>::forward_iterator, vector<string>::forward_iterator > ip;
		ip = adjacent_find(d_objects.begin(), d_objects.end(), sameDirectory);
		if(ip.first != d_objects.end())
		{
		  vector<string>::size_type oldSize = d_objects.size();
			//Archive the objects
			ostringstream cmd("ar -c -r ", ios::append);
			string archiveName = FileSystem::directoryName(objects.first()) << "/arch.a";
			cmd << archiveName << " ";
			copy(ip.first, ip.second, ostream_iterator<string>(cmd, " "));
			d_objects.erase(ip.first, ip.second);
			d_objects.push_back(archiveName);
			cerr << "[AR] " << oldSize << " to " << d_objects.size(); 
			system(cmd.str().c_str());
		}
	}	
*/
  command << Options::commandAppend;

  return command.str();
}
