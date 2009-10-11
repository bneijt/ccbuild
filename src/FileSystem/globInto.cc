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







#include "FileSystem.ih"

void FileSystem::globInto(vector<string> *list, string const &pattern, bool sort)
{

	glob_t globbuf;	//Needs to be globfreed at the end

	//Use glob to get canditates
	if(sort)
		::glob(pattern.c_str(), GLOB_TILDE, NULL, &globbuf);
	else
		::glob(pattern.c_str(), GLOB_TILDE | GLOB_NOSORT, NULL, &globbuf);
	

	//Copy all the matches
	copy(&globbuf.gl_pathv[0],
			 &globbuf.gl_pathv[globbuf.gl_pathc],
			 back_inserter(*list)
			 );

	//Cleanup
	globfree(&globbuf);
}
