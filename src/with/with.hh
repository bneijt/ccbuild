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

#ifndef with_hh_included_
#define with_hh_included_

namespace bneijt {
/**\brief Scoped temporary assignment
  Assignment of a temporary value which on destruction of this class will be reset to the old value.
*/
template<typename T>
class With {
        T d_oldValue;
        T &target;
    public:

        With(T &a, T const &temporary)
            :
            d_oldValue(a),
            target(a) {
            a = temporary;
        }
        ~With() {
            target = d_oldValue;
        }
};
} //Namespace
#endif

