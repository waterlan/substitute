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

#ifndef writeSet_INCLUDED
#define writeSet_INCLUDED


#include <stdio.h>

#include "std_macro.h"
#include "structures.h"

#include "text.h"


   template <class Tset>
   void writeSet(size_t tabs,
                 Tset set,
                 FILE* fp = stdout)
   {
      size_t index = 0;
      while(index < size(set))
      {
         write(tabs, elementAt(index, set), fp);
         index = index + 1;
      }
   }
   template <class Tset>
   void writeSet(text firstSeparator,
                 text nextSeparator,
                 size_t tabs,
                 Tset set,
                 FILE* fp = stdout)
   {
      if (isEmpty(set) eq false)
         write(firstSeparator, tabs, elementAt((size_t) 0, set), fp);

      size_t index = 1;
      while(index < size(set))
      {
         write(nextSeparator, tabs, elementAt(index, set), fp);
         index = index + 1;
      }
   }
   template <class Tset>
   void writeSetHandleSep(text firstSeparator,
                          text nextSeparator,
                          size_t tabs,
                          Tset set,
                          FILE* fp = stdout)
   {
      if (isEmpty(set) eq false)
      {
         fprintf(fp, "%s%s", firstSeparator, Tab(tabs));
         write("", tabs, elementAt((size_t) 0, set), fp);
      }

      size_t index = 1;
      while(index < size(set))
      {
         fprintf(fp, "%s%s", nextSeparator, Tab(tabs));
         write("", tabs, elementAt(index, set), fp);

         index = index + 1;
      }
   }
   template <class Tset,
             class Targ>
   void writeSet(size_t tabs,
                 Tset set,
                 Targ arg,
                 FILE* fp = stdout)
   {
      size_t index = 0;
      while(index < size(set))
      {
         write(tabs, elementAt(index, set), arg, fp);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ>
   void writeSet(text firstSeparator,
                 text nextSeparator,
                 size_t tabs,
                 Tset set,
                 Targ arg,
                 FILE* fp = stdout)
   {
      if (isEmpty(set) eq false)
         write(firstSeparator, tabs, elementAt((size_t) 0, set), arg, fp);

      size_t index = 1;
      while(index < size(set))
      {
         write(nextSeparator, tabs, elementAt(index, set), arg, fp);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ>
   void writeSetHandleSep(text firstSeparator,
                          text nextSeparator,
                          size_t tabs,
                          Tset set,
                          Targ arg,
                          FILE* fp = stdout)
   {
      if (isEmpty(set) eq false)
      {
         fprintf(fp, "%s%s", firstSeparator, Tab(tabs));
         write("", tabs, elementAt((size_t) 0, set), arg, fp);
      }

      size_t index = 1;
      while(index < size(set))
      {
         fprintf(fp, "%s%s", nextSeparator, Tab(tabs));
         write("", tabs, elementAt(index, set), arg, fp);

         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2>
   void writeSet(size_t tabs,
                 Tset set,
                 Targ1 arg1,
                 Targ2 arg2,
                 FILE* fp = stdout)
   {
      size_t index = 0;
      while(index < size(set))
      {
         write(tabs, elementAt(index, set), arg1, arg2, fp);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2>
   void writeSet(text firstSeparator,
                 text nextSeparator,
                 size_t tabs,
                 Tset set,
                 Targ1 arg1,
                 Targ2 arg2,
                 FILE* fp = stdout)
   {
      if (isEmpty(set) eq false)
         write(firstSeparator, tabs, elementAt((size_t) 0, set), arg1, arg2, fp);

      size_t index = 1;
      while(index < size(set))
      {
         write(nextSeparator, tabs, elementAt(index, set), arg1, arg2, fp);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2>
   void writeSetHandleSep(text firstSeparator,
                          text nextSeparator,
                          size_t tabs,
                          Tset set,
                          Targ1 arg1,
                          Targ2 arg2,
                          FILE* fp = stdout)
   {
      if (isEmpty(set) eq false)
      {
         fprintf(fp, "%s%s", firstSeparator, Tab(tabs));
         write("", tabs, elementAt((size_t) 0, set), arg1, arg2, fp);
      }

      size_t index = 1;
      while(index < size(set))
      {
         fprintf(fp, "%s%s", nextSeparator, Tab(tabs));
         write("", tabs, elementAt(index, set), arg1, arg2, fp);

         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2,
             class Targ3>
   void writeSet(size_t tabs,
                 Tset set,
                 Targ1 arg1,
                 Targ2 arg2,
                 Targ3 arg3,
                 FILE* fp = stdout)
   {
      size_t index = 0;
      while(index < size(set))
      {
         write(tabs, elementAt(index, set), arg1, arg2, arg3, fp);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2,
             class Targ3>
   void writeSet(text firstSeparator,
                 text nextSeparator,
                 size_t tabs,
                 Tset set,
                 Targ1 arg1,
                 Targ2 arg2,
                 Targ3 arg3,
                 FILE* fp = stdout)
   {
      if (isEmpty(set) eq false)
         write(firstSeparator, tabs, elementAt((size_t) 0, set), arg1, arg2, arg3, fp);

      size_t index = 1;
      while(index < size(set))
      {
         write(nextSeparator, tabs, elementAt(index, set), arg1, arg2, arg3, fp);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2,
             class Targ3>
   void writeSetHandleSep(text firstSeparator,
                          text nextSeparator,
                          size_t tabs,
                          Tset set,
                          Targ1 arg1,
                          Targ2 arg2,
                          Targ3 arg3,
                          FILE* fp = stdout)
   {
      if (isEmpty(set) eq false)
      {
         fprintf(fp, "%s%s", firstSeparator, Tab(tabs));
         write("", tabs, elementAt((size_t) 0, set), arg1, arg2, arg3, fp);
      }

      size_t index = 1;
      while(index < size(set))
      {
         fprintf(fp, "%s%s", nextSeparator, Tab(tabs));
         write("", tabs, elementAt(index, set), arg1, arg2, arg3, fp);

         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2,
             class Targ3,
             class Targ4>
   void writeSet(size_t tabs,
                 Tset set,
                 Targ1 arg1,
                 Targ2 arg2,
                 Targ3 arg3,
                 Targ4 arg4,
                 FILE* fp = stdout)
   {
      size_t index = 0;
      while(index < size(set))
      {
         write(tabs, elementAt(index, set), arg1, arg2, arg3, arg4, fp);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2,
             class Targ3,
             class Targ4>
   void writeSet(text firstSeparator,
                 text nextSeparator,
                 size_t tabs,
                 Tset set,
                 Targ1 arg1,
                 Targ2 arg2,
                 Targ3 arg3,
                 Targ4 arg4,
                 FILE* fp = stdout)
   {
      if (isEmpty(set) eq false)
         write(firstSeparator, tabs, elementAt((size_t) 0, set), arg1, arg2, arg3, arg4, fp);

      size_t index = 1;
      while(index < size(set))
      {
         write(nextSeparator, tabs, elementAt(index, set), arg1, arg2, arg3, arg4, fp);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2,
             class Targ3,
             class Targ4>
   void writeSetHandleSep(text firstSeparator,
                          text nextSeparator,
                          size_t tabs,
                          Tset set,
                          Targ1 arg1,
                          Targ2 arg2,
                          Targ3 arg3,
                          Targ4 arg4,
                          FILE* fp = stdout)
   {
      if (isEmpty(set) eq false)
      {
         fprintf(fp, "%s%s", firstSeparator, Tab(tabs));
         write("", tabs, elementAt((size_t) 0, set), arg1, arg2, arg3, arg4, fp);
      }

      size_t index = 1;
      while(index < size(set))
      {
         fprintf(fp, "%s%s", nextSeparator, Tab(tabs));
         write("", tabs, elementAt(index, set), arg1, arg2, arg3, arg4, fp);

         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2,
             class Targ3,
             class Targ4,
             class Targ5>
   void writeSet(size_t tabs,
                 Tset set,
                 Targ1 arg1,
                 Targ2 arg2,
                 Targ3 arg3,
                 Targ4 arg4,
                 Targ5 arg5,
                 FILE* fp = stdout)
   {
      size_t index = 0;
      while(index < size(set))
      {
         write(tabs, elementAt(index, set), arg1, arg2, arg3, arg4, arg5, fp);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2,
             class Targ3,
             class Targ4,
             class Targ5>
   void writeSet(text firstSeparator,
                 text nextSeparator,
                 size_t tabs,
                 Tset set,
                 Targ1 arg1,
                 Targ2 arg2,
                 Targ3 arg3,
                 Targ4 arg4,
                 Targ5 arg5,
                 FILE* fp = stdout)
   {
      if (isEmpty(set) eq false)
         write(firstSeparator, tabs, elementAt((size_t) 0, set), arg1, arg2, arg3, arg4, arg5, fp);

      size_t index = 1;
      while(index < size(set))
      {
         write(nextSeparator, tabs, elementAt(index, set), arg1, arg2, arg3, arg4, arg5, fp);
         index = index + 1;
      }
   }
   template <class Tset,
             class Targ1,
             class Targ2,
             class Targ3,
             class Targ4,
             class Targ5>
   void writeSetHandleSep(text firstSeparator,
                          text nextSeparator,
                          size_t tabs,
                          Tset set,
                          Targ1 arg1,
                          Targ2 arg2,
                          Targ3 arg3,
                          Targ4 arg4,
                          Targ5 arg5,
                          FILE* fp = stdout)
   {
      if (isEmpty(set) eq false)
      {
         fprintf(fp, "%s%s", firstSeparator, Tab(tabs));
         write("", tabs, elementAt((size_t) 0, set), arg1, arg2, arg3, arg4, arg5, fp);
      }

      size_t index = 1;
      while(index < size(set))
      {
         fprintf(fp, "%s%s", nextSeparator, Tab(tabs));
         write("", tabs, elementAt(index, set), arg1, arg2, arg3, arg4, arg5, fp);

         index = index + 1;
      }
   }
#endif
