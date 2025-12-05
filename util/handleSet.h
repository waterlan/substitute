// Copyright (C) 1994-2006 Ondrej Popp
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#ifndef handleSet_INCLUDED
#define handleSet_INCLUDED



#include "std_macro.h"
#include "structures.h"



   template <class Tset>
   void handleSet(Tset set)
   {
      size_t index = 0;
      while(index < size(set))
      {
         handle(elementAt(index, set));
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ>
   void handleSet(Tset set,
                  Targ arg)
   {
      size_t index = 0;
      while(index < size(set))
      {
         handle(elementAt(index, set), arg);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2>
   void handleSet(Tset set,
                  Targ1 arg1,
                  Targ2 arg2)
   {
      size_t index = 0;
      while(index < size(set))
      {
         handle(elementAt(index, set), arg1, arg2);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2,
             class Targ3>
   void handleSet(Tset set,
                  Targ1 arg1,
                  Targ2 arg2,
                  Targ3 arg3)
   {
      size_t index = 0;
      while(index < size(set))
      {
         handle(elementAt(index, set), arg1, arg2, arg3);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2,
             class Targ3,
             class Targ4>
   void handleSet(Tset set,
                  Targ1 arg1,
                  Targ2 arg2,
                  Targ3 arg3,
                  Targ4 arg4)
   {
      size_t index = 0;
      while(index < size(set))
      {
         handle(elementAt(index, set), arg1, arg2, arg3, arg4);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2,
             class Targ3,
             class Targ4,
             class Targ5>
   void handleSet(Tset set,
                  Targ1 arg1,
                  Targ2 arg2,
                  Targ3 arg3,
                  Targ4 arg4,
                  Targ5 arg5)
   {
      size_t index = 0;
      while(index < size(set))
      {
         handle(elementAt(index, set), arg1, arg2, arg3, arg4, arg5);
         index = index + 1;
      }
   }
#endif
