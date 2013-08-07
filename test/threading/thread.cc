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

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

int main(int argc, char * argv[])
{
	using namespace std;
	int status;
	pid_t p = fork();
	if(p == -1)
		cout << "Failure to fork\n";
	else if(p == 0)
	{
		cout << "Child exiting with 10\n";
		sleep(2);
		exit(5);
	}
	else
	{
		//Mother waits...
		pid_t pp = wait(&status);
		if(pp == p)
			cout << "Got the pid back from wait\n";
		else
			cout << "Got another pid back from wait: " << pp << "\n";
		cout << "Status: " << WEXITSTATUS(status) << "\n";
	}
	return 0;
}
