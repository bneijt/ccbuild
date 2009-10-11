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







#include "source.ih"
void Source::dependencies(std::vector<Source *> &srcList)
{
  //Collect all Source pointers needed
  stack<Source *> srcStack;
  srcStack.push(this);

  //Gather all the global includes and sources
  while(srcStack.size() > 0)
  {
    Source *current = srcStack.top();
    srcStack.pop();

    //Have we seen this source?
    if(find(srcList.begin(), srcList.end(), current) != srcList.end())
      continue;
		
    //Copy dependencies to stack.
    vector<Source *> deps;
    current->directDeps(deps);

    //Push all sources to the stack
    __foreach(dep, deps)
				srcStack.push(*dep);

		//Never collect this in the list
		if(current != this)
	   	srcList.push_back(current);
  }
}

void Source::dependencies(std::vector<Source *> &srcList, std::vector<std::string *> &globalList)
{
	//TODO: use std::set as srcList to check for contents?
  //Collect all Source pointers needed
  stack<Source *> srcStack;
  srcStack.push(this);
	
	set<string *> globalSet(d_globalDeps);

  //Gather all the global includes and sources
  while(srcStack.size() > 0)
  {
    Source *current = srcStack.top();
    srcStack.pop();

    //Have we seen this source?
    if(find(srcList.begin(), srcList.end(), current) != srcList.end())
      continue;
		
    //Copy dependencies to stack.
    vector<Source *> deps;
    vector<string *> globals;
    current->directDeps(deps, globals);


    //Push all sources to the stack
    __foreach(dep, deps)
				srcStack.push(*dep);

    //Copy new global includes to the list.
    copy(globals.begin(), globals.end(), inserter(globalSet, globalSet.begin()));

   	srcList.push_back(current);
  }

  srcList.erase(srcList.begin());	//Remove "this" from the srcList;
  copy(globalSet.begin(), globalSet.end(), back_inserter(globalList));
  
}
