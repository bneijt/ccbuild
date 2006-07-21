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

#include "Resolver.ih"
string Resolver::expand(std::string const &name) const
{
  ostringstream pathstr("", ios::app);

	wordexp_t p;
  char **w;

	int retv = wordexp(name.c_str(), &p, 0);

	if(retv != 0)
	{
		cerr << "ccbuild: Error shell expanding '" << name << "'.\n";

		switch(retv)
		{
			case WRDE_BADCHAR:
				cerr << "ccbuild: Illegal  occurrence of newline or one of |, &, ;, <, >, (, ), {,}.\n";
				break;

//			case WRDE_BADVAL:
//				cerr << "ccbuild: An undefined shell variable was referenced, and  the  WRDE_UNDEF flag told us to consider this an error.\n";
//				break;

			case WRDE_CMDSUB:
				cerr << "ccbuild: Command  substitution  occurred, and the WRDE_NOCMD flag told us\n";
				cerr << "ccbuild:   to consider this an error.\n";
				break;

			case WRDE_NOSPACE:
				cerr << "ccbuild: Out of memory.\n";
				break;

			case WRDE_SYNTAX:
				cerr << "ccbuild: Shell syntax error, such as unbalanced parentheses or unmatched quotes.\n";
				break;
    }
		//Flush error stream
		cerr << "ccbuild: You might want to check your ccResolutions file." << endl;
	}
	else
	{
  	w = p.we_wordv;
		pathstr  << "\"" << w[0] << "\"";
  	for (unsigned i = 1; i < p.we_wordc; ++i)
		 	pathstr << " \"" << w[i] << "\"";
	
		//wordfree segfaults if wordexp failed
  	wordfree(&p);
	}
  return pathstr.str();
}
