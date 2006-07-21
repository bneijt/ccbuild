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

#include "Source.ih"
void Source::scan(vector < string > *local, vector < string > *global, vector < string > *ignore)
{

	//Scan the file for all information

	//Scan sourcecode
  ifstream file(d_filename.c_str());
  if(!file)
  {
    cout << "\n\nSource::scan.cc:  THIS SHOULD NOT BE POSSIBLE!!!\n\n";
    return;
  }

  SourceScanner *scanner = new SourceScanner(&file);
  try
  {
    scanner->yylex();
    d_hasMainFunction = scanner->hasMainFunction();
    //d_hasDefine = scanner->hasDefine();
		if(ignore == 0)
			ignore = &d_ignored;

    scanner->includes(local, global, ignore);
    
		if(Options::verbose && ignore->size() > 0)
		{
			_foreach(ig, *ignore)
				cerr << "ccbuild: warning: ignoring \"" << *ig << "\" in \"" << filename() << "\"\n";
		}
  }
  catch(SourceScanner::Error err)
  {
  	//Errors are seen just after they are encountered, thus decrement lineno.
    cout << "Include scanning error on line " << scanner->lineno() - 1
    		 << " in file " << d_filename << "\n";
  }

  delete scanner;
}
