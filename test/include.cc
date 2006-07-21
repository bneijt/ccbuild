/*
	Testing include statements
Test: ccbuild deps include.cc
*/
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

int main(int argc, char *argv[])
{
	
}
