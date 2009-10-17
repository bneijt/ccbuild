/*
  ccbuild - A strict developer's build utility
  Copyright (C) 2008  A. Bram Neijt <bneijt@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef _MD5Info_H_INCLUDED_
#define _MD5Info_H_INCLUDED_
#include <sys/types.h>
#include <string>
#include <map>
#include <set>
#include "../openmp/lock/lock.hh"

namespace bneijt
{

/**\brief MD5Sum information singleton. Keeps an in memory list of current and last MD5Hashes

	MD5Info is an interface to the .md5 files in the o directory. The hash filenames are not
	to be used by other parts of the program.
	Instead, the filename of the source file (the hash is about) is used and internally translated
	to the right .md5 filename.

	The .md5 files contain a list of hashes which is a concatination of the hashes of the file and all it's
	dependencies. This means that if the file changes, the first 32 characters will change. Whenever 
	a dependecy changes, characters in the latter part of the line will change.
*/
class MD5Info
{
		static MD5Info *s_instance;	///<Static pointer to the instance
		static OpenMP::Lock s_instanceLock; ///<Lock for autmoatic instantiation and destruction
		
		std::map<std::string, std::string> d_old;	///< A map of filename-hashstring for containing cached information
    OpenMP::Lock d_oldLock;
		std::map<std::string, std::string> d_new;	///< A map of filename-hashstring for the new md5sum information
    OpenMP::Lock d_newLock;

		/**\brief The cached content hash of the file on disk.
		*/
		std::map<std::string, std::string> d_content;
    OpenMP::Lock d_contentLock;

	public:
		/**\brief Get the instance
		
		This get instance doesn't require an initialization, it creates a new default
		class when called uninitialized.
		\return An instance to the MD5Info singleton
		*/
		static MD5Info &getInstance();

		/**\brief Delete the instance
		
		Unlike most destroy functions, this one is protected against multiple destoys. So calling
		this function on a already destroyed instance is no problem.
		*/
		static void destroy();
		
		/**\brief Return the old, cached information for the given file.
			This will return the string placed in the configuration file with save.
		*/
		std::string const &old(std::string const &filename);

		///\brief Return the current hex hash string for the given file		
		std::string const &contentHash(std::string const &filename);
				
		/**\brief Save the hash information for the given file on disk now.
			\param filename The source filename the information is about.
			\param hash A string containing hash information.
		*/
		void save(std::string const &filename, std::string const &hash);
		
		/**\brief Returns the path to the hash file of a given filename
		This function should not be used very often. Currently it's only use is
		the cleaning part of the program.
		*/
		static std::string hashFilenameFor(std::string const &filename);
    
	private:
		
		///\brief Load the hash for the given file from the default place
		void load(std::string const &filename);
		

		MD5Info();

		///\brief Destory the cache, saving any memory data to disk
		~MD5Info();

		///\brief Not implemented
		MD5Info(MD5Info const &other);						//NI

		///\brief Not implemented
		MD5Info &operator=(MD5Info const &other);	//NI
};
}//namespace

#endif
