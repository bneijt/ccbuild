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
	Testing include statements
Test: ccbuild deps include.cc
*/
#ifdef THIS_IS_NOT_MEANT_FOR_COMPILATION_JUST_SCANNER_TESTING
#include <iostream>
 # include <gnoredg>
 # include <ignwsoredg>    
 # include <ignwcoredg> 		//Hello, this should work tooo
 # include "ignoredl"
 # include "ignoredlws" 
 # include "ignoredlwt"	
 #  include <doublespace>		  //COMMENTNAKJDJE
 #	include <tab>		  //COMMENTNAKJDJE
 # include "ignoredlwstc"		  //COMMENTNAKJDJE
 # include "ignoredlwstc"		  //COMMENTNAKJDJE
 # include "ignoredlwstc"		  //COMMENTNAKJDJE
#include "empty.hh"
//#include "noextistinglocal.h"
#endif
int main(int argc, char *argv[])
{
	
}
