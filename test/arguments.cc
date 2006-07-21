

#include "Arguments/Arguments.hh"
#include <iostream>

#include "Misc/Misc.hh"
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

		_foreach(e, err)
		{
			cout << "ERROR: " << (*e) << "\n";
		}
	}

	if(args.rest().size() > 0)
	{
		vector<string> &err = args.rest();

		_foreach(e, err)
		{
			cout << "REST: " << (*e) << "\n";
		}
	}

	args.destroy();	//Destroy the instance.

	return 0;
}

