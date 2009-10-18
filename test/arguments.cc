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

#include "arguments/arguments.hh"
#include <iostream>

#include "misc/foreach.hh"
#include <vector>

int main(int argc, char *argv[])
{
	using namespace bneijt;
	using namespace std;

	Arguments::Option options[] = {
	  {"f force-update", "", "Force an update"},
		{"a add", "<file to add>", "Add something to a list"},
	  {"b", "[maybe]", "Not supported optional arguments yet"},
	  {0, 0, 0}
	};

	Arguments::initialize(options, argc, argv);
	Arguments &args = Arguments::getInstance();
	if(args.flagged("a"))
		cout << "Add: " << args.value("a") <<"\n";
	if(args.flagged("b"))
		cout << "B: " << args.value("b") <<"\n";

	if(args.errors().size() > 0)
	{
		vector<string> &err = args.errors();

		__foreach(e, err)
		{
			cout << "ERROR: " << (*e) << "\n";
		}
	}

	if(args.rest().size() > 0)
	{
		vector<string> &err = args.rest();

		__foreach(e, err)
		{
			cout << "REST: " << (*e) << "\n";
		}
	}

	args.destroy();	//Destroy the instance.

	return 0;
}

