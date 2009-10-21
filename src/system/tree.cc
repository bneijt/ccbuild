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
/*
  XML output found at http://cpansearch.perl.org/src/PCIMPRICH/XML-Directory-1.00/docs/Directory.html
 <?xml version="1.0" encoding="utf-8"?>
 <dirtree>
   <head version="0.70">
     <path>/home/petr/test</path>
     <details>2</details>
     <depth>5</depth>
   </head>
   <directory name="test" depth="0">
     <path></path>
     <modify-time epoch="998300843">Mon Aug 20 11:47:23 2001</modify-time>
     <file name="dir2xml.pl">
       <mode code="33261">rwx</mode>
       <size unit="bytes">225</size>
       <modify-time epoch="998300843">Mon Aug 20 11:47:23 2001</modify-time>
     </file>
   </directory>
 </dirtree>
*/

#include "system.ih"

void System::tree(std::ostream &str)
{
	vector<string> files;

	Sources &s = Sources::getInstance();

	FileSystem::globSourceFilesInto(&files, ".");

	__foreach(file, files)
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
		str << ":" << source->basenameWithoutExtension();
	
	str << "] " << source->filename() << "\n";

	__foreach(src, srcList)
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
