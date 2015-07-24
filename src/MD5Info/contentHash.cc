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

#include "MD5Info.ih"

std::string const &MD5Info::contentHash(std::string const &filename) {
    OpenMP::ScopedLock lock(d_contentLock);
    if(d_content.count(filename) == 0) {

        //#define MD5_DIGEST_LENGTH 16

        unsigned char md[MD5_DIGEST_LENGTH];
        gnutls_hash_hd_t context;
        gnutls_hash_init (&context, GNUTLS_DIG_MD5);

        //Start updating with the file content
        size_t const bufferSize = 1024*512/8; //512-bit block multiple for update
        char *buffer = new char[bufferSize];
        ifstream ifile(filename.c_str());
        while(ifile) {
            ifile.read(buffer, bufferSize);
            gnutls_hash (context, buffer, ifile.gcount());
        }
        delete[] buffer;

        gnutls_hash_deinit (context, &md[0]);
        // gnutls_free (context);
        char hex_hash[(MD5_DIGEST_LENGTH * 2) + 1];
        for(size_t i = 0; i < MD5_DIGEST_LENGTH; ++i) {
            sprintf(&hex_hash[i*2], "%02x", md[i]);
        }
        hex_hash[(MD5_DIGEST_LENGTH * 2)] = '\0';
        d_content[filename] = string(&hex_hash[0]);
        _debugLevel2("Calculated content hash " << filename << " == " << d_content[filename]);
    }

    return d_content[filename];
}
