/*
	ccbuild - A strict developer's build utility
	Copyright (C) 2005  Jesse van den Kieboom <jesse@icecrew.nl>
	Copyright (C) 2005	A. Bram Neijt <bneijt@gmail.com>
	
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

	Initial version by Jesse van den Kieboom
	Modifications by A. Bram Neijt.
	
*/

#include "System.ih"

void System::tree(std::ostream &str)
{
	vector<string> files;

	Sources &s = Sources::getInstance();

	FileSystem::globSourceFilesInto(&files, ".");

	_foreach(file, files)
	{
		Source *target = s[*file];

		//Error loading source??
		if(target == 0)
		{
			cerr << "Error loading '" << *file << "'\n";
			continue;
		}

		System::inspect(target);

		//isBinTarget test can only be done after the inspect
		if(!target->isBinTarget())
			continue;

		System::tree(target, str);
	}
}

void System::tree(Source *source, std::ostream &str)
{
	vector<Source *> srcList;
	srcList.push_back(source);
	collectTargets(srcList);
	string prevClass;
	string currentClass;

	str << "[target";
	
	if (Options::verbose)
		cout << ":" << source->basename();
	
	str << "] " << source->filename() << "\n";

	_foreach(src, srcList)
	{
	  str << "\t";
		currentClass = (*src)->directory();
		
		if (currentClass != ".")
		{
			if (prevClass != currentClass)
			{
				str << "[dir] " << currentClass << "\n\t";
				prevClass = currentClass;
			}
			str << "\t";
		}
		
		str << "[file";
		
		if(Options::verbose)
		{
			if((*src)->isHeader())
			{
				if((*src)->isInternalHeader())
					str << ":ih";
				else
					str << ":hh";
			}
			else
				str << ":so";
		}
		
		str << "] " << (*src)->filename();
		str << "\n";
	}
}