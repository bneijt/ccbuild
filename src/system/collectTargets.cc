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






#include "system.ih"

void System::collectTargets(vector<Source *> &sources, bool skipBin)
{
	//Collect the targets for the current given sourcestack.
	set<Source *> roots(sources.begin(), sources.end());
	vector<Source *> srcStack(sources);
	sources.clear();
	vector<Source *> srcs;
	
	while(srcStack.size() > 0)
	{
		Source *src = srcStack.back();
		srcStack.pop_back();
		inspect(src);

		//We skip if: isbinary, and is not part of the roots
		if(skipBin
				&& src->isBinTarget()
				&& roots.count(src) == 0)
			continue;
			
		src->directDeps(srcs);
		
    if(find(sources.begin(), sources.end(),
					  src) != sources.end())
			continue;

		sources.push_back(src);

		copy(srcs.begin(), srcs.end(), back_inserter(srcStack));
		
		//Collect all source files surrounding local includes
		if(src->isHeader())
		{
			//Collect all surrounding object targets
			Sources &mainSrcList = Sources::getInstance();
			vector<string> files;
			FileSystem::globSourceFilesInto(&files, src->directory());
			__foreach(file, files)
			{
				//Load file using sources
				Source *loadedSrc = mainSrcList[*file];
				
				//Push sources to stack.
				if(loadedSrc)
					srcStack.push_back(loadedSrc);
			}
		}
	}
	
}
