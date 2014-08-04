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

#ifndef System_H_INCLUDED_
#define System_H_INCLUDED_

#include "../source/source.hh"
#include "../compiler/compiler.hh"
#include "../arguments/arguments.hh"
#include "../problem/problem.hh"

#include <string>
#include <iosfwd>
#include <set>
#include <vector>

namespace bneijt {

///\brief The main workinghorse
///The actual system, wich loads sources and starts building. This is a static class containing all needed functions for the commands
class System {
        //Force linking for builds
        static bool forceLink;

    public:

        //Inspection FASE
        ///\brief Inspect all sources in the current directory
        static void inspect();

        ///\brief Inspect the given filename source
        static void inspect(std::string filename);

        ///\brief Inspect the given source pointer
        static void inspect(Source *root    ///<The source to inspect
                           );

        //Update/Build FASE
        ///\brief Build all binTargets in the current directory
        static void buildAll(); ///Build the given source

        ///\brief Build the given source using the default compiler
        static void build(Source *source    ///<The Source to build
                         );

        ///\brief Build the given source using the given compiler
        static void build(Source *source,   ///<The Source to build
                          Compiler &cc
                         );

        //Clean/Remove FASE
        ///\brief Clean all local sources
        static void clean();

        ///\brief Clean the given source
        static void clean(Source *source    ///<The Source to clean
                         );

        /**\brief Expand all sources on the given list to include all targets associated with them.

            \param sources The list of sources you want to expand.
            \param skipBinaryTargets Wether to skip any found binary targets. Otherwise inspect and folow their includes.
        */
        static void collectTargets(std::vector<Source *> &sources, bool skipBinaryTargets = true);

        ///\brief Clean all local binary target sources
        static void icmake();

        ///\brief Clean the given source
        static void icmake(Source *source   ///<The Source to clean
                          );

        ///\brief Check all local binary target sources
        static void check();

        /** \brief Check the given source status
            \param source The Source to clean
        */
        static void check(Source *source);

        ///\brief MD5 sum the all bintargets in current directory
        static void md5();

        /**\brief MD5 sum the sources in a source tree
            \param source The Source to follow
        */
        static void md5(Source *source);


        ///\brief Remove all 'o' directories recursively
        static void distclean();

        ///\brief Load extra agruments from the ccResolutions file
        ///
        ///If the ccResolutions files contains a "#&" first line the
        /// remainder of this line is word expanded and added as arguments
        /// to argv. On succes the function returns true, on error false.
        /// On succes a memory leak is created becaus the argv will point to
        /// a newly allocated array. This array should be deallocated somewhere lateron.
        static bool addArguments(int &argc, char ** &argv); //NotImplementedYet

        ///\brief Resolve test command for all sources
        static void resolveTest(Source * s, std::ostream &str);

        ///\brief Resolve test command
        static void resolveTest(std::ostream &str);

        ///\brief Resolve the source and insert non-resolving into globals
        static void resolveTest(Source * s, std::set<std::string> *globals);

        ///\brief Write a header include graph in DOT language for all binary targets
        ///
        ///This will create a .dot file for every binary target in the current directory.
        static void dotgraphForAll();

        ///\brief Change to the given path
        static bool changeTo(std::string const &path);


        ///\brief Write a header include graph in DOT language for root to str
        static void dotgraphFor(Source *root,   ///<The source to inspect
                                std::ostream &str ///<The stream to place the output
                               );

        ///\brief Write dependencies to str in human readable form
        static void depsFor(std::ostream &str);

        ///\brief Write dependencies for root to str in human readable form
        static void depsFor(Source *root, std::ostream &str);

        ///\brief Produce a Makefile on str
        static void makefileForAll(std::ostream &str    ///< ostream to put the Makefile on
                                  );

        /**\brief Produce an a-a-p file on str

        \param str to put the Makefile on
        */
        static void aapForAll(std::ostream &str);

        /**\brief Produce an a-a-p for root on str

        \param root Target source
        \param str Stream to put the makefile on
        */
        static void aapFor(Source *root, std::ostream &str);

        ///\brief System sleep call
        static unsigned sleep(unsigned const seconds);

        ///\brief Produce a Makefile for root on str
        static void makefileFor(Source *root, ///< Target source
                                std::ostream &str ///< Stream to put the makefile on
                               );

        ///\brief Load the Options functions using the arguments given. Returns true on error.
        static bool parseArguments(Arguments &arg   ///<The Arguments class to load the options from
                                  );

        ///\brief Call destroy, then exit with retValue
        static void exit(int retValue);

        ///\brief Delete the singletons
        static void destroy()  throw();

        ///\brief Return a trimmed version of the given string.
        static std::string trimmed(std::string const &argument);

        ///\brief Trim the given string.
        static void trim(std::string *argument);

        ///\brief Glob all sources of the current directory and place their Source pointers in list.
        static void localSourcesInto(std::vector<Source *> &list);

        /**\brief Build a library of all local sources or a given source

            \param s A Sources pointer to the source
            \param version A (possibly empty) string containing the version number
        */
        static int lib(std::string const &version, Source *s = 0);

        /** \brief Execute command and return the exit status

            \param command The command to execute
            \param simulate When true, the actual command is not run.
            \return On normal exit it, the exit status, otherwise 255.
        */
        static int system(std::string const &command, bool simulate = Options::simulate) throw(Problem);

        /** \brief Batch compile a list of objects
          If we compile multiple objects with the same G++ we get a performance boost
          To keep the objects from coming out, we need a nasty hack: use -save-temps, and pick
          the object files out of the results and tell the linker to do nothing but tell us
          it's version (-Wl,--version) to keep linking errors from becoming a problem.

        */
        static void batchCompile(std::vector<Source const*> const &batchList, Compiler const &cc);

        /**\brief Deduct the project name from the directory structure

            This function tries to deduct the project name using the directory path
            of the current process. The project name will be either the current directory or, if
            the current directory is named "src", the directory above it.
        */
        static std::string projectName();

        /** \brief Return uname output for the given uname field name
        */
        static std::string uname(char const field);
        /** \brief Create a temporary directory from the template name and return it
        */
        static std::string mkdtemp(std::string const& nameTemplate) throw(Problem);

        /**\brief Return the current username of the running process
        */
        static std::string username() throw(Problem);

};

}   //namespace

#endif
