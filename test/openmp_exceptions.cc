/*
  This file is part of ccbuild.
  Copyright (C) 2013  A. Bram Neijt <bneijt@gmail.com>

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
#include <iostream>
#include <omp.h>
int main(int, char const *[])
{
  float ts = 42.0f;
  std::cerr <<"ZERO, before parallel: " <<std::endl;
  std::cout <<"ts " <<ts <<" &ts " <<&ts
	<<std::endl <<std::endl;
  #pragma omp parallel num_threads (1)
  {
	#pragma omp critical (std_cerr_critical)
	{
	  std::cerr <<"ONE, before try-catch: " <<std::endl;
	  std::cerr <<"ts " <<ts <<" &ts " <<&ts
		<<std::endl <<std::endl;
	}
	try {
	  #pragma omp critical (std_cerr_critical)
	  {
		std::cerr <<"TWO, inside try: " <<std::endl;
		std::cerr <<"ts " <<ts <<" &ts " <<&ts
		  <<std::endl <<std::endl;
	  }
	} catch(...) {
	  #pragma omp critical (std_cerr_critical)
	  {
		std::cerr <<"THREE, inside catch: " <<std::endl;
		std::cerr <<"ts " <<ts <<" &ts " <<&ts
		  <<std::endl <<std::endl;
	  }
	}
	#pragma omp critical (std_cerr_critical)
	{
	  std::cerr <<"FOUR, after catch, inside parallel: "
		<<std::endl;
	  std::cerr <<"ts " <<ts <<" &ts " <<&ts
		<<std::endl <<std::endl;
	}
  } // end #pragma omp parallel
  std::cerr <<"FIVE, after parallel: " <<std::endl;
  std::cerr <<"ts " <<ts <<" &ts " <<&ts
	<<std::endl <<std::endl;
  return 0;
}
