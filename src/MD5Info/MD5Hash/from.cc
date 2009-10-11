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






#include "MD5Hash.ih"



void MD5Hash::from(std::string const &filename)
{
	d_loaded = true;
//	if(Options::option<bool>("verbose"))
//		cerr << "[MD5] " << filename << "\n";
	ifstream file(filename.c_str());
	GCrypt algo(GCRY_MD_MD5);
	
	//Feed it the file
	static unsigned const blockSize(1024);
	char data[blockSize];
	unsigned int read(0);
	while(true)
	{
		read = file.readsome(&data[0], blockSize);
		if(!read)
			break;
		algo.update(&data[0], read);
	}
	algo.finalize();
	algo.rawInto(d_hash);
}
