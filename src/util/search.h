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

#ifndef search_INCLUDED
#define search_INCLUDED


#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"

#include "intset.h"


   template <class TmatchId,
             class Tset,
             class Tel>
   ssize_t Index(TmatchId matchId,
                 Tset set,
                 bool (*match_f) (TmatchId, Tel),
                 bool state = true,
                 Tel (*elementAt_f) (size_t, Tset) = elementAt,
                 size_t (*size_f) (Tset) = size)
   {
      size_t index = 0;
      while(index < size_f(set))
      {
         if (match_f(matchId, elementAt_f(index, set)) == state)
            return (ssize_t) index;

         index = index + 1;
      }

      return -1;
   }
   template <class TmatchId,
             class Tset,
             class Tel>
   intset Indexes(TmatchId matchId,
                  Tset set,
                  bool (*match_f) (TmatchId, Tel),
                  bool state = true,
                  Tel (*elementAt_f) (size_t, Tset) = elementAt,
                  size_t (*size_f) (Tset) = size)
   {
      intset indexes = NULL;

      size_t index = 0;
      while(index < size_f(set))
      {
         if (match_f(matchId, elementAt_f(index, set)) == state)
         {
            if (indexes == NULL)
               indexes = intsetNew();

            add((int) index, indexes);
         }
         index = index + 1;
      }

      return indexes;
   }
   template <class TmatchId,
             class Tset,
             class Tel>
   size_t matchCount(TmatchId matchId,
                     Tset set,
                     bool (*match_f) (TmatchId, Tel),
                     bool state = true,
                     Tel (*elementAt_f) (size_t, Tset) = elementAt,
                     size_t (*size_f) (Tset) = size)
   {
      size_t count = 0;

      size_t index = 0;
      while(index < size_f(set))
      {
         if (match_f(matchId, elementAt_f(index, set)) == state)
            count = count + 1;

         index = index + 1;
      }

      return count;
   }
   template <class TmatchId,
             class Tset,
             class Tel>
   bool exists(TmatchId matchId,
               Tset set,
               bool (*match_f) (TmatchId, Tel),
               bool state = true,
               Tel (*elementAt_f) (size_t, Tset) = elementAt,
               size_t (*size_f) (Tset) = size)
   {
      size_t index = 0;
      while(index < size_f(set))
      {
         if (match_f(matchId, elementAt_f(index, set)) == state)
            return true;

         index = index + 1;
      }

      return false;
   }
   template <class TmatchId,
             class Tset,
             class Tel>
   bool existsUnique(TmatchId matchId,
                     Tset set,
                     bool (*match_f) (TmatchId, Tel),
                     bool state = true,
                     Tel (*elementAt_f) (size_t, Tset) = elementAt,
                     size_t (*size_f) (Tset) = size)
   {
      bool seenOne = false;

      size_t index = 0;
      while(index < size_f(set))
      {
         if (match_f(matchId, elementAt_f(index, set)) == state)
         {
            if (seenOne)
               return false;
            else
               seenOne = true;
         }
         index = index + 1;
      }

      return seenOne;
   }
   template <class Tsrc,
             class TmatchId,
             class Tdest,
             class Tel>
   void filterAppend(Tsrc src,
                     TmatchId matchId,
                     Tdest dest,
                     bool (*match_f) (TmatchId, Tel),
                     bool state = true,
                     Tel (*elementAt_f) (size_t, Tsrc) = elementAt,
                     void (*add_f) (Tel, Tdest) = add,
                     size_t (*size_f) (Tsrc) = size)
   {
      Tel element;
      size_t index = 0;
      while(index < size_f(src))
      {
         element = elementAt_f(index, src);
         if (match_f(matchId, element) == state)
            add_f(element, dest);

         index = index + 1;
      }
   }
#endif
