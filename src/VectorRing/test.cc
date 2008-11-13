#include "VectorRing.hh"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <typeinfo>

using namespace std;
using namespace bneijt;
int main(int argc, char **argv)
try
{
  VectorRing<string> v(3);
  string a("a");
  for(char i = 'a'; i < 'z'; ++i)
  {
    cout << "=\n";
    v.push_back(a);
    copy(v.begin(), v.end(), ostream_iterator<string>(cout));
    a[0] = i;
  }
  cout << "\n";
  return 0;
}
catch(const std::exception &e)
{
	//All is LOST... nothing to do here but die
  cerr << "Caught std::exception (" << typeid(e).name() << "): " << e.what();
  cerr << "\nPlease report this as a bug.\n";
}
