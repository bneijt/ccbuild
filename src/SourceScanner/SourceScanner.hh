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

#ifndef _SourceScanner_H_
#define _SourceScanner_H_
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#ifndef _SKIP_YYFLEXLEXER_
#include <FlexLexer.h>
#endif

namespace bneijt{

///\brief Parse the given source
///
///The SourceScanner parses the source and stores a few features of it in memory:
/// - The local includes it uses
/// - The global includes it uses
/// - Wether it contains a "int main" function
class SourceScanner: public yyFlexLexer
{
  std::vector < std::string > d_globals;	///< Global dependencies
  std::vector < std::string > d_locals;		///< Local dependencies
  std::vector < std::string > d_ignore;		///< Ignored dependencies
  
  std::string d_ginclude;	///< global include collecting string
  std::string d_linclude;	///< local include collecting string
  std::string d_iinclude;	///< local include collecting string
  
  bool d_hasMainFunction;	///< Has main function state bit
  bool d_hasDefine;				///< Has \#define state bit

	public:
		///\brief An enumeration of possible error codes
		enum Error
  	{
  		invalidInclude
  	};

  	///\brief Initialize the SourceScanner on the given stream
    SourceScanner(std::istream * yyin ///< Stream to scan
    		);

    /**\brief Put the known local and global includes into these vectors

			\param local	Vector for local includes
    	\param global Vector for global includes
    	\param ignore Vector for ignored includes
    */
  	void includes(std::vector<std::string> *local,
									std::vector<std::string> *global,
									std::vector<std::string> *ignore = 0	
									);

		///\brief Returns true when the scanned source contained a main function
		bool const &hasMainFunction() const;

		///\brief Returns true when the scanned source contained a \#define directive
		bool const &hasDefine() const;


		///\brief The yylex function, to run the parser
  	virtual int yylex();
	private:
	
		///\brief Not implemented
		SourceScanner(SourceScanner const &other);	// NI
		
		///\brief Not implemented
  	SourceScanner &operator=(SourceScanner const &other);	// NI

		///\brief Push d_ginclude to the d_gobals vector
  	void storeGlobal();
	
		///\brief Push d_ginclude to the d_gobals vector
  	void storeIgnore();
  	
		///\brief Push d_linclude to the d_locals vector
  	void storeLocal();
};

}//Namespace
#endif
