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

#include "Compiler.ih"
namespace {
bool startsWith(std::string const &a, std::string const &b)
{
	//Return wether a starts with b
	if(a.size() < b.size())
		return false;
	return a.compare(0, b.length(), b) == 0;
}

}//namespace


unsigned Compiler::countFirstLinkerArguments(std::vector<std::string> &arguments) const
{
	//Add argument taking linker options here, flags below
	//The following options take an argument:
	char const* takeArg[] = {
		"-Wl," //-Wl,option
		,"-Xlinker"
		,"-u"
		,"-L"
		,"-l"
//		,""
		,0
		};

	//The following options are simple flags
	char const *flag[] = {
		"-nostartfiles"
		,"-nodefaultlibs"
		,"-nostdlib"
		,"-pie"
		,"-s"
		,"-static"
		,"-static-libgcc"
		,"-shared"
		,"-shared-libgcc"
		,"-symbolic"
		,"-rdynamic"
//		,"-threads"
//		,"-pthreads"
//		,""
//		,""
		,0
	};




	//TODO optimize: arguments.size() test is possibly not necessary in nested for loop
	unsigned count(0);
	for(; count < arguments.size(); ++count)
	{
		bool found = false;
		
		//If one of the takeArg is found, count++
		for(unsigned i = 0; count < arguments.size() && takeArg[i]; ++i)
			if(startsWith(arguments[count], takeArg[i]))
			{
				_debugLevel2("Found: '" << takeArg[i] << "'");

				//If the argument is not attached to the flag				
				if(arguments[count].size() == strlen(takeArg[i]))
					++count;
				found = true;
				break;
			}
		
		//Go for the next one
		if(found)
			continue;
		
		//The flags
		for(unsigned i = 0; count < arguments.size() && flag[i]; ++i)
			if(arguments[count] == flag[i])
			{
				found = true;
				break;
			}		
		
		if(!found)
			break;
	}
	
	//If not any argument, break
	_debugLevel2("Stopped at: '" << (count < arguments.size() ? arguments[count] : "THE END" ) << "' counting " << count);

	return count;
}
/*

DOCUMENTATION VALUES
All added options are surrounded by parentheses


From commandline:
       Linker Options
           (-llibrary) (-nostartfiles)  (-nodefaultlibs)  (-nostdlib) (-pie) (-s)  (-static)
           (-static-libgcc)  (-shared)  (-shared-libgcc)  (-symbolic) (-Wl,option)  (-Xlinker option) (-u symbol)

       Directory Options
           -Bprefix  -Idir  -iquotedir  (-Ldir)  -specs=file  -I-

From: GNU manual for options: http://gcc.gnu.org/onlinedocs/gcc/Link-Options.html#Link-Options
3.13 Options for Linking

These options come into play when the compiler links object files into an executable output file. They are meaningless if the compiler is not doing a link step.

object-file-name
    A file name that does not end in a special recognized suffix is considered to name an object file or library. (Object files are distinguished from libraries by the linker according to the file contents.) If linking is done, these object files are used as input to the linker.
-c
-S
-E
    If any of these options is used, then the linker is not run, and object file names should not be used as arguments. See Overall Options.


(-llibrary)
(-l library)
    Search the library named library when linking. (The second alternative with the library as a separate argument is only for POSIX compliance and is not recommended.)

    It makes a difference where in the command you write this option; the linker searches and processes libraries and object files in the order they are specified. Thus, `foo.o -lz bar.o' searches library `z' after file foo.o but before bar.o. If bar.o refers to functions in `z', those functions may not be loaded.

    The linker searches a standard list of directories for the library, which is actually a file named liblibrary.a. The linker then uses this file as if it had been specified precisely by name.

    The directories searched include several standard system directories plus any that you specify with (-L).

    Normally the files found this way are library files—archive files whose members are object files. The linker handles an archive file by scanning through it for members which define symbols that have so far been referenced but not defined. But if the file that is found is an ordinary object file, it is linked in the usual fashion. The only difference between using an (-l) option and specifying a file name is that (-l) surrounds library with `lib' and `.a' and searches several directories.
-lobjc
    You need this special case of the (-l) option in order to link an Objective-C or Objective-C++ program.
-nostartfiles
    Do not use the standard system startup files when linking. The standard system libraries are used normally, unless -nostdlib or (-nodefaultlibs) is used.
-nodefaultlibs
    Do not use the standard system libraries when linking. Only the libraries you specify will be passed to the linker. The standard startup files are used normally, unless -nostartfiles is used. The compiler may generate calls to memcmp, memset, memcpy and memmove. These entries are usually resolved by entries in libc. These entry points should be supplied through some other mechanism when this option is specified.
(-nostdlib)
    Do not use the standard system startup files or libraries when linking. No startup files and only the libraries you specify will be passed to the linker. The compiler may generate calls to memcmp, memset, memcpy and memmove. These entries are usually resolved by entries in libc. These entry points should be supplied through some other mechanism when this option is specified.

    One of the standard libraries bypassed by -nostdlib and -nodefaultlibs is libgcc.a, a library of internal subroutines that GCC uses to overcome shortcomings of particular machines, or special needs for some languages. (See Interfacing to GCC Output, for more discussion of libgcc.a.) In most cases, you need libgcc.a even when you want to avoid other standard libraries. In other words, when you specify -nostdlib or -nodefaultlibs you should usually specify -lgcc as well. This ensures that you have no unresolved references to internal GCC library subroutines. (For example, `__main', used to ensure C++ constructors will be called; see collect2.)
(-pie)
    Produce a position independent executable on targets which support it. For predictable results, you must also specify the same set of options that were used to generate code (-fpie, -fPIE, or model suboptions) when you specify this option.
(-rdynamic)
    Pass the flag -export-dynamic to the ELF linker, on targets that support it. This instructs the linker to add all symbols, not only used ones, to the dynamic symbol table. This option is needed for some uses of dlopen or to allow obtaining backtraces from within a program.
(-s)
    Remove all symbol table and relocation information from the executable.
(-static)
    On systems that support dynamic linking, this prevents linking with the shared libraries. On other systems, this option has no effect.
(-shared)
    Produce a shared object which can then be linked with other objects to form an executable. Not all systems support this option. For predictable results, you must also specify the same set of options that were used to generate code (-fpic, -fPIC, or model suboptions) when you specify this option.1
(-shared-libgcc)
(-static-libgcc)
    On systems that provide libgcc as a shared library, these options force the use of either the shared or static version respectively. If no shared version of libgcc was built when the compiler was configured, these options have no effect.

    There are several situations in which an application should use the shared libgcc instead of the static version. The most common of these is when the application wishes to throw and catch exceptions across different shared libraries. In that case, each of the libraries as well as the application itself should use the shared libgcc.

    Therefore, the G++ and GCJ drivers automatically add -shared-libgcc whenever you build a shared library or a main executable, because C++ and Java programs typically use exceptions, so this is the right thing to do.

    If, instead, you use the GCC driver to create shared libraries, you may find that they will not always be linked with the shared libgcc. If GCC finds, at its configuration time, that you have a non-GNU linker or a GNU linker that does not support option --eh-frame-hdr, it will link the shared version of libgcc into shared libraries by default. Otherwise, it will take advantage of the linker and optimize away the linking with the shared version of libgcc, linking with the static version of libgcc by default. This allows exceptions to propagate through such shared libraries, without incurring relocation costs at library load time.

    However, if a library or main executable is supposed to throw or catch exceptions, you must link it using the G++ or GCJ driver, as appropriate for the languages used in the program, or using the option -shared-libgcc, such that it is linked with the shared libgcc.
(-symbolic)
    Bind references to global symbols when building a shared object. Warn about any unresolved references (unless overridden by the link editor option `-Xlinker -z -Xlinker defs'). Only a few systems support this option.
(-Xlinker option)
    Pass option as an option to the linker. You can use this to supply system-specific linker options which GCC does not know how to recognize.

    If you want to pass an option that takes an argument, you must use -Xlinker twice, once for the option and once for the argument. For example, to pass -assert definitions, you must write `-Xlinker -assert -Xlinker definitions'. It does not work to write -Xlinker "-assert definitions", because this passes the entire string as a single argument, which is not what the linker expects.
(-Wl,option)
    Pass option as an option to the linker. If option contains commas, it is split into multiple options at the commas.
(-u symbol)
    Pretend the symbol symbol is undefined, to force linking of library modules to define it. You can use -u multiple times with different symbols to force loading of additional library modules.
    
*/ 
