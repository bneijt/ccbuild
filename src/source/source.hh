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

//Source is a wrapper class for sources
//It should facilitate methods as: hasFunction()
//and includes()
//To investigate the source

#ifndef _Source_H_INCLUDED_
#define _Source_H_INCLUDED_
#include <sys/types.h>
#include <utility>
#include <string>
#include <vector>
#include <set>

#include "../compiler/compiler.hh"
#include "../openmp/lock/lock.hh"
namespace bneijt {

///\brief Sourcefile wrapper
///
///This class wraps a sourcefile. It holds all functionality needed to extract information
/// from the source. Information like: is it a headerfile (isHeader) or a sourcefile?
/// Wether it should be used to create a executable (isBinTarget), a
/// library (isLibTarget) or just an object (isObjectTarget).
///The source wrapper should be able to tell us everything we want to know about a source.
class Source {
        OpenMP::Lock d_apiLock;///<Lock for the complete api, every non-const function should lock this.
        ///\brief A pair containing ino_t and dev_t information
        typedef std::pair<ino_t, dev_t> InodeDevPair;

        std::string d_filename; ///<Filename
        InodeDevPair d_inoDev;  ///<File ino dev pair
        time_t d_modTime;               ///<File modtime

        //A source can never depend on the same sources twice
        std::vector< Source * > d_deps; ///<Local dependencies (direct)
        std::set< std::string const *> d_globalDeps;///<Global dependencies
        std::vector< std::string > d_ignored;///<Ignored dependencies

        bool d_depsDone;    ///< Have the dependencies been calculated?

        unsigned char d_update; ///<  Do we need an update? 0=unknown, 1=true, 2=false;
        bool d_hasMainFunction; ///< Does this source have a main function

        ///\brief Internallly used source type defenitions
        enum SourceType {
            Unknown,
            LocalHeader,
            InternalHeader
        };

        SourceType d_srcType;   ///< The type of this source

    public:

        ///\brief Load the source
        Source(std::string const &filename  ///<The path to the source
              );

        ///\brief Create an empty source
        ///
        ///This can be used to match with sources to see if they loaded ok
        ///as this source will have (0,0) as InodeDevPair
        Source();

        //No destructor needed yet, default will do.

        ///\brief The basename of the filename
        std::string basenameWithoutExtension() const;

        ///\brief Give a list of all the sources that this source depends on.
        void dependencies(std::vector<Source *> &localDeps, std::vector<std::string const*> &globalDeps) const;

        ///\brief Append this source's local dependency pointers to this list
        void dependencies(std::vector<Source *> &localDeps) const;

        ///\brief Give a list of all the sources that this source depends on.
        void directDeps(std::vector<Source *> &localDeps) const;

        ///\brief Give a list of all the sources that this source depends on.
        void directDeps(std::vector<Source *> &localDeps, std::vector<std::string const *> &globalDeps) const;

        ///\brief Give a list of all the sources that this source depends on.
        void directDeps(std::vector<Source *> &localDeps, std::vector<std::string const *> &globalDeps, std::vector<std::string> &ignored) const;

        ///\brief Give a list of all ignored dependencies
        void ignoredDeps(std::vector<std::string> &ignored) const {
            ignored = d_ignored;
        }


        ///\brief Create the list of all the sources that this source depends on directly.
        void genDeps();

        ///\brief The directory the file is in
        std::string directory() const;

        ///\brief The actual given filename
        std::string const &filename() const {
            return d_filename;
        }

        ///\brief The filename it will create
        std::string outputFilename() const;

        /**\brief Reload this source

            Should only be used for reloading of source, as the pointers
            in other sources will still point to this source.
        */
        bool reload();

        /**\brief Compile this source using the compiler cc (Currently NOT USED)

            If we are a header, search for a local child and build that first
            This is done by seaking a local include that shares our path
            This source is loaded en build
            Now all local children are build, so now we can build our own functions
        Find all .cc files and build them
            We are a header, so we quit (no compilation).

            If we are a source, search for a local child and build that first
        check for update or not
            This is done by seaking a local include that shares our path
            This source is loaded en build
        (this handy for when a local child in the .ih but not in the .h)
        Now all local children are build, so now we can build our own functions.
        compile me
        Add my object to the list of objects in the compiler.

        \param cc Use this Compiler to compile this source
        */
        void build(Compiler &cc);

        ///\brief Build this source using the given compiler
        void buildObjectTarget(Compiler &cc ///<Use this compiler ot compile the source
                              );

        ///\brief Build this source using the given compiler
        void buildBinTarget(Compiler &cc ///<Use this compiler ot compile the source
                           );

        ///\brief Build this source using the given compiler (Currently NOT USED)
        void buildHeader(Compiler &cc ///<Use this compiler ot compile the source
                        );


        /**\brief Return true if the file is a binary target.
            This can only be done after the source has been inspected using genDeps()
        */
        bool isBinTarget() const;

        /**\brief Return true if the file is a library target.
            This can only be done after the source has been inspected using genDeps()
        */
        bool isLibTarget() const;

        /**\brief Return true if the file is a header.
            This can only be done after the source has been inspected using genDeps()
        */
        bool isHeader() const;

        /**\brief Return true if the file is a header.
            This can only be done after the source has been inspected using genDeps()
        */
        bool isLocalHeader() const;

        /**\brief Return true if the file is a header.
            This can only be done after the source has been inspected using genDeps()
        */
        bool isInternalHeader() const;

        /**\brief Return true if the file is an object target.
            This can only be done after the source has been inspected using genDeps()
        */
        bool isObjectTarget() const;

        ///\brief Return true if the file has a C++ source extension (.cc etc.)
        bool hasSourceExtension() const;

        ///\brief Non-const helper function. Not const because of dependencies not being const.
        bool upToDate() const;

        ///\brief Mark the souce as done, using MD5 update if that is enabled
        void markAsDone() const;

        ///\brief Return wether this source produces output.
        bool producesOutput() const;

        /** \brief Return wether this source has changed since last seen

            This is a helper function, introduced with the MD5 sum checking.
            It returns wether this source changed since last run. If we don't use
            md5 hashing, we need a substitute output file to check the modtime
            against for when the source doesn't produce output.

            \param substituteOutput A filename to use the modtime from if this doesn't output anything.

            \return true when the source changed since last seen.

        */
        bool changed(std::string const &substituteOutput) const;

        ///\brief Check wether this source has changed since last seen
        bool changed() const;


        /**\brief Return wether the source is up to date given a collection of reference sources

            \param sources The sources this source's output file needs to be newer then.
            \return True if this source is up to date, false otherwise.
        */
        bool upToDate(std::vector<Source *> const &sources) const;

        /** \brief Return true if the source file is newer then the loaded class.

            This function checks to see if the on disk file is the same as the in memory file.
            If this is not the case, the dependency information might be old.
        */
        bool stale();

        ///\brief Compares two sources based on inode and device numbers.
        bool operator==(Source const &rvalue) const {
            //Two sources are equal when they have the same ino-dev pair
            return d_inoDev == rvalue.d_inoDev;
        }

    private:
        ///\brief Fills the two vectors up with the local and global includes and fills d_hasMainFunction
        void scan(std::vector< std::string > *local, std::vector< std::string > *global, std::vector< std::string > *ignore = 0);
        ///\brief Determine source type based on he filename
        void setType();


};
}//namespace

#endif

