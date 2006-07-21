/*
	ccbuild - A strict developer's build utility
	Copyright (C) 2005  A. Bram Neijt <bneijt@gmail.com>

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

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
