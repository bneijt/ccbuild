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


#include "Sources.ih"

namespace{
class DerivedEqual
{
	Source const * a;

	public:
	DerivedEqual(Source const *target)
		:
			a(target)
	{}

	bool operator()(Source * const &b) const
	{
		return *a == *b;
	}
};
}	//Anon namespace

Source *Sources::operator[](std::string const &filename)
{

	_debugLevel3("Request for " << filename);
	Source *s = new Source(filename);
	if(!s)
	{
		cerr << "ccbuild: Unable allocate a source class?? :-S\n";
		return 0;
	}
	_debugLevel4("Loaded " << s->filename());

	if(!FileSystem::isReadable(s->filename()))
	{
		_debugLevel2("Requested file '" << filename << "' not readable.");
		delete s;
		return 0;
	}

	std::set<Source *>::iterator pos = find_if(d_sources.begin(), d_sources.end(), DerivedEqual(s));

	if(pos == d_sources.end())
	{
		//Not found
		_debugLevel4("Not found: " << filename);
		d_sources.insert(s);
		return s;
	}
	
	//Found
	_debugLevel4("Found: " << filename);
	delete s;
	return *pos;
}
