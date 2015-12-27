// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#ifndef ISENSOR_HH
#define ISENSOR_HH

#include "meta.hh"

#include <cassert>
#include <map>




struct ISensor
{

  struct
  {
    std::function<void ()> enable;
    std::function<void ()> disable;
  } in;

  struct
  {
    std::function<void ()> triggered;
  } out;

  dezyne::port::meta meta;
  inline ISensor(dezyne::port::meta m) : meta(m) {}


  void check_bindings() const
  {
    if (! in.enable) throw dezyne::binding_error(meta, "in.enable");
    if (! in.disable) throw dezyne::binding_error(meta, "in.disable");

    if (! out.triggered) throw dezyne::binding_error(meta, "out.triggered");

  }
};

inline void connect (ISensor& provided, ISensor& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}





#endif // ISENSOR_HH
