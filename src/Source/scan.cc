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



#include "Source.ih"
void Source::scan(vector < string > *local, vector < string > *global, vector < string > *ignore)
{

	//Scan the file for all information

	//Scan sourcecode
  ifstream file(d_filename.c_str());
  if(!file)
  {
    cerr << "\n\nSource::scan.cc:  THIS SHOULD NOT BE POSSIBLE!!!\n\n";
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
			__foreach(ig, *ignore)
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
