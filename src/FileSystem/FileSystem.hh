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


#ifndef _FileSystem_H_INCLUDED_
#define _FileSystem_H_INCLUDED_
#include <string>
#include <vector>
#include <sys/types.h>

#include "../problem/problem.hh"


#ifndef GLOB_ONLYDIR
#define GLOB_ONLYDIR 0
#endif


namespace bneijt
{
///\brief FileSystem
///
///A small collection of FileSystem functions.
class FileSystem
{
  public:

    /**\brief Get a vector of regular files matching the glob pattern.
    
    	\param list The vector to place the result into
    	\param pattern The glob pattern
    	\param sort	Wether or not to use a sorting glob call
    */
    static void globFilesInto(std::vector < std::string > *list,
    										std::string const &pattern,
    										bool sort = true
      			);

    ///\brief Get a vector of regular files matching the glob pattern.
    static void globSourceFilesInto(std::vector < std::string > *list,	///< The vector to place the result into
			      std::string const &directory	///< The directory
      );


    /**\brief Get a vector of regular directories matching the glob pattern.
    
    	\param list The vector to place the result into
    	\param pattern The glob pattern
    	\param sort	Wether or not to use a sorting glob call
    */
    static void globDirectoriesInto(std::vector < std::string > *list,
			      std::string const &pattern,
			      bool sort = false
      );
    
    ///\brief Glob all subdirectories of this directory
		static void recursiveGlobDirectoriesInto(std::vector< std::string> *list, std::string const &directory);
		
    /**\brief Get a vector of files matching the glob pattern.
    
    	\param list The vector to place the result into
    	\param pattern The glob pattern
    	\param sort	Wether or not to use a sorting glob call
    */
    static void globInto(std::vector < std::string > *list,	///< The vector to place the result into
			      std::string const &pattern,	///< The glob pattern
			      bool sort = true
      );

		///\brief Returns true if the file exists, in any form (it may be a directory)
    static bool fileExists(std::string const &filename,	///< The filename of the file to check
    	      bool noDir = false ///< The file is not a directory
    	);

		///\brief Remove the file it it exitst, return true on succes.
    static bool rmIfExists(std::string const &filename	///< The filename of the file to remove
    	);

		/**\brief Returns a cleaner version of the given path ("./a/../b" -> "./b")
			\param filename The filename of the file to check
		*/
    static std::string cleanPath(std::string const &filename);
		
		/**\brief Returns the directory part of a path
			\param filename The filename of the file to check
		*/
    static std::string directoryName(std::string const &filename);
    	
		/**\brief Returns base of the filename (filename, withouth path, without extension)
		
		\param filename The filename to do the conversion on
		\return The resulting stripped basename
		*/
    static std::string baseName(std::string const &filename);
    
		/**\brief Returns the filename (filename, withouth path)
		
		\param filename The filename to do the conversion on
		\result The resulting stripped filename
		*/
    static std::string fileName(std::string const &filename);

    ///\brief Touch the given file
    static bool touch(std::string const &filename	///< The filename of the file to touch
    	);

    ///\brief Return the current working directory
		static std::string cwd();

    /**\brief Check wether file1 is newer then file2
    	If either file doesn't exist, the function returns false.
    */
    static bool newer(std::string const &file1, std::string const &file2);
    
    ///\brief Return the modification time for the given file
		static time_t modTime(std::string const &file) throw (Problem);
		
    ///\brief Returns true when the given file is readable
    static bool isReadable(std::string const &file);
    
    ///\brief If the given directory doesn't exist, create it.
    static void ensureDirectory(std::string const &directoryName);
};
}				//namespace
#endif
