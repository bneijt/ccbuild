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






#include "arguments.ih"

void Arguments::clear()
{
	//Reduce memory usage
	std::set<bool *> pointerList;

	//std::map<std::string, bool * > d_flags;
	__foreach(flag, d_flags)
		pointerList.insert((*flag).second);

	//std::map<bool *, std::string> d_value;
	__foreach(flag, d_values)
		pointerList.insert((*flag).first);

	//Kill all boolean pointers
	__foreach(p, pointerList)
		delete *p;

	d_rest.clear();
	d_errors.clear();
}
