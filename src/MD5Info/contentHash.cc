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

#include "MD5Info.ih"

std::string const &MD5Info::contentHash(std::string const &filename)
{
  OpenMP::ScopedLock lock(d_contentLock);
	if(d_content.count(filename) == 0)
	{
	  //Create the hex hash of the file
	  unsigned char md[EVP_md5()->md_size];
	  EVP_MD_CTX context;
	  
	  //Done by the INIT below. EVP_MD_CTX_init(&context, EVP_md5(void));
	  EVP_DigestInit(&context, EVP_md5());

    //Start updating with the file content
    size_t const bufferSize = EVP_md5()->block_size;
    char *buffer = new char[bufferSize];
    ifstream ifile(filename.c_str());
    while(ifile)
    {
      ifile.read(buffer, bufferSize);
  	  EVP_DigestUpdate(&context, buffer, ifile.gcount());
    }
    delete[] buffer;
    
    unsigned int size;
	  EVP_DigestFinal(&context, &md[0], &size); //context is automatically cleaned-up
	  char hex_hash[(EVP_md5()->md_size * 2) + 1];
	  for(size_t i = 0; i < size; ++i)
	    sprintf(&hex_hash[i*2], "%02x", md[i]);
    hex_hash[(EVP_md5()->md_size * 2)] = '\0';
    d_content[filename] = string(&hex_hash[0]);
    _debugLevel2("Calculated content hash " << filename << " == " << d_content[filename]);
	}

	return d_content[filename];
}
