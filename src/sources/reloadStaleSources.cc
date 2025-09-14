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

#include "sources.ih"

void Sources::reloadStaleSources() {
    OpenMP::ScopedLock dslock(d_sourcesLock);

    __foreach(src, d_sources) {
        if((*src)->stale()) {
            if((*src)->reload()) {
                continue;
            }

            //Reloading failed!
            _debugLevel1("Reload failed on " << (*src)->filename() << ". Cleaning up all sources.");

            cerr << "ccbuild: Source tree change. Forcing refresh.\n";

            //Forget all memory resident hashes
            MD5Info::destroy();
            MD5Info::getInstance();

            //Remove the object of any binary target to ensure relinking
            __foreach(i, d_sources) {
                if((*i)->isBinTarget()) {
                    FileSystem::rmIfExists((*i)->outputFilename());
                }
            }

            //Cleanup
            //Remove all dependency knowledge because of stale pointers...
            __foreach(i, d_sources)
            delete *i;
            d_sources.clear();
            break;
        }
    }
}
