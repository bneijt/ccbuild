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

#include "source.ih"

Source::Source(string const &sourceFilename)
    :
    d_filename(sourceFilename),
    d_inoDev(make_pair(0,0)),
    d_modTime(0),
    d_deps(),
    d_globalDeps(),
    d_ignored(),
    d_depsDone(false),
    d_update(0),
    d_hasMainFunction(false),
    d_srcType(Unknown) {
    d_filename = FileSystem::cleanPath(d_filename);
    _debugLevel2("Loaded \"" << filename << "\" as \"" << d_filename << "\"");

    struct stat a;

    if(stat(d_filename.c_str(), &a) == 0) {
        d_inoDev.first = a.st_dev;
        d_inoDev.second = a.st_ino;
        d_modTime = a.st_mtime;
    }
    setType();
}

//Empty source initializer
Source::Source()
    :
    d_filename(""),
    d_inoDev(make_pair(0,0)),
    d_modTime(0),
    d_deps(),
    d_globalDeps(),
    d_ignored(),
    d_depsDone(false),
    d_update(0),
    d_hasMainFunction(false),
    d_srcType(Unknown) {
    setType();
}
