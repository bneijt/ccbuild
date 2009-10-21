/*
  ccbuild - A strict developer's build utility
  Copyright (C) 2008  A. Bram Neijt <bneijt@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef _Compiler_H_INCLUDED_
#define _Compiler_H_INCLUDED_
#include <string>
#include <vector>

#include "../options/options.hh"

namespace bneijt
{

///\brief A compiler wrapping class
///
///This class is a wrapper for the compiler. All functionality of the compiler is
///is, as needed, reflected by functions in this class.
///It also keeps track of any additional compiler arguments "currently" needed.
///
///When cleaning a system, this Compiler's interface is overloaded with the Cleaner class, which issues the unlink command on the output files for all the objects.
class Compiler
{
	  std::string d_baseCommand;							///<The basic command used for both link and compile (g++)
	  std::vector<std::string> d_objects;	///<List of known objects (.o files for link fase)

	  std::vector<std::string> d_compile;		///<List of compile options
	  std::vector<std::string> d_link;			///<List of link options
		static std::string const s_highLightOn;	///< String to begin a highlight
		static std::string const s_highLightOff;///< String to end a highlight
		static std::string const s_clear;       ///< String to clear the screen
		static std::string const s_msgCancelBruteMode;///< Message to print when canceling brute mode

	public:

		///\brief Initialize the compiler
  	Compiler(std::string basecommand = Options::CC ///<Basic command to use
							)
			:
			d_baseCommand(basecommand),
			d_objects(),
			d_compile(),
			d_link()
	  {}

	  ///\brief Copy constructor
	  Compiler(Compiler const &other)
	  	:
	  	d_baseCommand(other.d_baseCommand),
			d_objects(other.d_objects),
			d_compile(other.d_compile),
			d_link(other.d_link)
	  {}


		///\brief Return the sum of two compilers
	  Compiler const operator+(Compiler const &rvalue);

		///\brief Add the folowing object as a link option to the commandline
	  void addObject(std::string objFilename);

		///\brief Add the library lib to the compiler options
	  void addArgument(std::string argument	///< The argument. This is parsed to addLibrary and addObjects etc. terms.
	    );

		///\brief Run the compiler to precopmile a (header) file
  	int precompile(std::string pwd,	///<Working directory to use
	       std::string target,		///<Target filename to compile
	       std::string outputFile	///<The file to use for output
	    ) const;

		///\brief Return the compiler command to precopmile a (header) file
  	std::string precompileCommand(std::string pwd,	///<Working directory to use
	       std::string target,		///<Target filename to compile
	       std::string outputFile	///<The file to use for output
	    ) const;

		///\brief Run the compiler to create an object
  	int compile(std::string pwd,	///<Working directory to use
	       std::string target,		///<Target filename to compile
	       std::string outputFile	///<The file to use for output
	    ) const;

	  ///\brief Link all the objects to a file
	  int link(std::string pwd,///<Working directory to use
			std::string outputFile  ///<The file to use for output
	    ) const;

		/**\brief Create a library from all the objects

	  	\param pwd Working directory to use
	  	\param outputFile The name of the output file (libsomething.so)
	  	\param version The version of the library (0.6.7)		
		*/
	  int lib(std::string pwd, std::string outputFile, std::string const &version) const;

	  /**\brief Create an archive from all the objects
	  
	  	\param outputFile The file to use for output
	  */
	  int ar(std::string outputFile) const;

		/**\brief Return the library creation command to create a library

	  	\param pwd Working directory to use
	  	\param outputFile The name of the output file (libsomething.so)
		*/
  	std::string libCommand(std::string pwd,
	       std::string outputFile
	    ) const;

		/**\brief Return the compile command to create an object
			\param pwd Working directory to use
			\param target Target filename to compile
			\param outputFile The file to use for output
		*/
  	std::string compileCommand(std::string pwd,
	       std::string target,
	       std::string outputFile
	    ) const;

	  ///\brief Return the command used to link all the objects to a file
	  std::string linkCommand(std::string pwd,///<Working directory to use
			std::string outputFile  ///<The file to use for output
	    ) const;

	  ///\brief Return the arguments used for linking only
		std::vector<std::string> const & linkArguments() const
		{
			return d_link;
		}
		
	  ///\brief Return the arguments used for compilation (also used while linking)
		std::vector<std::string> const & compileArguments() const
		{
			return d_compile;
		}
		
    ///\brief Remove all compile-time arguments of the compiler
 	  void rmCompileOptions()
	  {
	    d_compile.clear();
	  }

		///\brief Return the map containing all the objects.
		std::vector<std::string> const &objects() const
		{
			return d_objects;
		}

    ///\brief Clear the list of objects used at link-time
	  void rmObjects()
	  {
	    d_objects.clear();
	  }



	private:
		/**\brief Return the number of linker arguments at the beginning of the given list
		
		\return The number of arguments which are linker arguments.
		*/
		unsigned countFirstLinkerArguments(std::vector<std::string> &arguments) const;
		
		/**\brief Split an arguments list into it's arguments
		
		This will split the arguments given in argument into the vector. It tries to combine all
		arguments with quoated values.
		*/
		void splitInto(std::string argument, std::vector<std::string> &arguments) const;
		
		/** \brief Clear the screen if needed according to options
		*/
		void cls() const;
};
}		//namespace
#endif
