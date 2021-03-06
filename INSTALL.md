As far as I know, ccbuild will not correctly function on anything else apart
from plain, vanilla, Linux. However, please consider giving it a try on any
system you can find and report any problems online at
 https://github.com/bneijt/ccbuild/issues

Shortcut: `cmake . && make install`

Shortcut for other prefix: `cmake . && make DESTDIR=/tmp/prefix install`

There is only one binary, so installation should be easy...
1)
    Install the dependences:
    libbobcat 2.0 or higher (correct API of Process class)
    libgomp 1.0+ (OpenMP)
    libgnutls (for MD5 algorithm)
    libboost 1.37 or higher.
    Boost circular buffer is available since 1.35, but 1.35 seems to give build problems.
    flex 2.5.31 or newer (for the source scanner)

2)
    If you have absolutly no rights on the system, add a writable (for example ${HOME}/bin) to your path and run "sh localinstall.sh".

    This will use the first writeable PATH path as binary directory
    and install the configuration files to your home directory.

    Don't forget to awnser "yes" to the final do-you-really-want-this
    question.

    If you have some rights on the system and have cmake installed:

        cmake .
        make
        sudo make install

3)
    For the user of ccbuild, it might be nice to add the standard Unix
    headers as empty resolutions by copying the tools/ccResolutions.d
    directory to ~/.ccbuild (this is not automatically done by any
    of the install scripts).
