/*
	ccbuild - A strict developer's build utility
	Copyright (C) 2005  A. Bram Neijt <bneijt@gmail.com>

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

//Arguments list singleton. There to make sure we only load Arguments once

#ifndef _Arguments_H_INCLUDED_
#define _Arguments_H_INCLUDED_

#include <string>
#include <map>
#include <vector>
#include <iosfwd>


namespace bneijt
{

/**
\brief Arguments singleton. Gives simple access to the give program arguments

First initialize the singleton with options and the commandline arguments.

Arguments can be tested using the functions flagged, value and rest.
Options should be a 3xN array of character pointers, ending in {0,0,0}. Options are defined with:
{"flagges and long names, space seperated", "valuename, if any", "Help text explaning what the option is."}

  WARNING: Arguments only supports up to 39 long options currently! See the TODO in Arguments.cc

\section example Example of use
\code
#include "Arguments/Arguments.hh"
#include <iostream>

#include <vector>

int main(int argc, char *argv[])
{
	using namespace bneijt;
	using namespace std;

	Arguments::Option options[] = {
	  {"f force-update", "", "Force an update"},
		{"a add", "<file to add>", "Add something to a list"},
	  {"b", "[maybe]", "Force an update"},
	  {0, 0, 0}
	};

	Arguments::initialize(options, argc, argv);
	Arguments &args = Arguments::getInstance();
	if(args.flagged("a"))
		cout << "Add: " << args.value("a") <<"\n";

	if(args.errors().size() > 0)
	{
		vector<string> &err = args.errors();

		foreach(e, err)
		{
			cout << "ERROR: " << (*e) << "\n";
		}
	}

	if(args.rest().size() > 0)
	{
		vector<string> &err = args.rest();

		foreach(e, err)
		{
			cout << "REST: " << (*e) << "\n";
		}
	}

	args.destroy();	//Destroy the instance.

	return 0;
}
\endcode



*/
class Arguments
{
		std::map<std::string, bool * > d_flags;	///<The flags and their link to the values
//std::map<bool *, std::string> d_value;	///<Map between the argument value and the flag option
		std::map<bool *, std::vector<std::string> > d_values;	///<Map between the argument value and the flag option
		std::vector<std::string> d_rest;				///<All remaining arguments
		std::vector<std::string> d_errors;			///<All options which caused errors
		std::vector<std::string> d_emptyList;		///<A non const empty stringList
		std::string d_empty;										///<A non const empty string

		static Arguments *s_instance;	///<Pointer to the singleton instance


	public:
		///\brief A structure containing the defenition of a commandline option
		struct Option
		{
			std::string flags;	///<All flags it can be called with, space seperated ("f force" will allow "-f" and "--force")
			std::string value;	///<The value, if any, the argument of the option is called. "<value>" for required, "[value]" for optional.
			std::string helpText;	///< The help text, describing this option. This is used when generating the help output.
		};


		///\brief Initialize the singleton with options and argv, argc
		///
		///
		static void initialize(Option const *options, int argc, char *argv[]);

		///\brief Get the instance of the Arguments class. Use this only after initializing it.
		static Arguments &getInstance();

		///\brief Return true when an option if flagged, false otherwise.
		bool flagged(std::string const &optionName) const;

		///\brief Returns the argument of an option or an empty string.
		std::string value(std::string const &optionName) const;

		///\brief Returns the argument of an option or an empty string.
		std::vector<std::string> const &values(std::string const &optionName) const;

		///\brief Returns a vector containing all the remaining commandline options.
		std::vector<std::string> &rest()
		{
			return d_rest;
		}

		///\brief Returns a vector containing all the commanline options generating errors.
		std::vector<std::string> &errors()
		{
			return d_errors;
		}

		///\brief Delete the instance. Use this only if you aren't going to use the Arguments class instance.
		static void destroy();

		///\brief Output a list of the flags and help information onto the given stream.
		void outputOptions(std::ostream &stream) const;

	private:
		Option const *d_options;	///< A pointer to the options used to initialize the Arguments class


		///\brief Clear the class, clearing all vectors and freeing pointers.
		void clear();

		///\brief Parse the argc and argv using the given options
		Arguments(Option const *options, int argc, char *argv[]);

		~Arguments();

		///\brief Not implemented
		Arguments(Arguments const &other);						//NI
		///\brief Not implemented
		Arguments &operator=(Arguments const &other);	//NI

};


}//namespace

#endif
