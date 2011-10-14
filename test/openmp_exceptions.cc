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
