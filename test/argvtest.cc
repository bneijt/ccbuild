/*
	Check to see if argv is \0 terminated
*/

#include <iostream>


int main(int argc, char *argv[])
{
	using namespace std;
	cout << "argc " << argc << endl;
	for(unsigned i=0; i < 100; ++i)
		cout << "argv[" << i << "] (" << &argv[i] << ") " << argv[i] << endl;
}

