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
#include <vector>
#include <iterator>
#include <algorithm>

void showStrings(std::vector< std::string const *> &a)
{
  copy(a.begin(), a.end(), std::ostream_iterator<std::string const *>(std::cout));
}

/*
  Without this function below, you get Possible solution
./container_const.cc: In function ‘int main(int, char**)’:
./container_const.cc:48: error: invalid initialization of reference of type ‘std::vector<const std::string*, std::allocator<const std::string*> >&’ from expression of type ‘std::vector<std::string*, std::allocator<std::string*> >’
./container_const.cc:23: error: in passing argument 1 of ‘void showStrings(std::vector<const std::string*, std::allocator<const std::string*> >&)’
*/
void showStrings(std::vector< std::string *> &a)
{
  std::vector<std::string const *> b(a.begin(), a.end());
  showStrings(b);
  //copy(a.begin(), a.end(), std::ostream_iterator<std::string *>(std::cout));

  //Does not work: std::vector<std::string const> b(a.begin(), a.end());
  /* Also does not seem to work
  std::vector<std::string const> b(a.size());
  copy(a.begin(), a.end(), b.begin());
  showStrings(b);
  */
}
int main(int argc, char *argv[])
{
	using namespace std;
	vector<std::string *> the_container;
	std::string a("a"), b("b"), c("c");
	the_container.push_back(&a);
	the_container.push_back(&b);
	the_container.push_back(&c);
	showStrings(the_container);
}
