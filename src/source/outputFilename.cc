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






#include "source.ih"

std::string Source::outputFilename() const
{
	if(isObjectTarget() || isBinTarget())
	{
	  //Output into a seperate directory with path in filename
		// OLD per directory output directory directory() + "/o/" + basename() + ".o";
		String oname = String(directory()).replace('/', '_') + "_" + basename() + ".o";
		//Strip any ._ beginning
		if(oname.startsWith("._"))
		  oname = oname.substr(2);
		return "o/objects/" + oname;
  }
	if(isHeader())
		return filename() + ".gch";

	return "";
}
