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

#define search_range_cc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"

#include "error.h"
#include "text.h"
#include "search_rangeset.h"
#include "search_range.h"


expfun search_range search_rangeNew(regoff_t begin = 0,
                                    regoff_t end = 0)
{
   search_range s = (search_range) malloc (sizeof(search_range_struct));
   if (s != NULL)
   {
      s->begin = begin;
      s->end = end;
      s->subranges = search_rangesetNew();
   }
   else
      malloc_error("search_rangeNew()");

   return s;
}
expfun bool eqBegin(regoff_t begin,
                    search_range s)
{
   if (s == NULL)
      return false;
   else if (begin == getBegin(s))
      return true;
   else
      return false;
}
expfun bool eqEnd(regoff_t end,
                  search_range s)
{
   if (s == NULL)
      return false;
   else if (end == getEnd(s))
      return true;
   else
      return false;
}
expfun bool eqSelfSubranges(search_rangeset subranges,
                            search_range s)
{
   if ((subranges == NULL) || (hasSubranges(s) == false))
      return false;
   else if (eqSelf(subranges, getSubranges(s)))
      return true;
   else
      return false;
}
expfun bool eqSubranges(search_rangeset subranges,
                        search_range s)
{
   if ((subranges == NULL) || (hasSubranges(s) == false))
      return false;
   else if (Eq(subranges, getSubranges(s)))
      return true;
   else
      return false;
}
expfun bool eqSelf(search_range a,
                   search_range b)
{
   if ((a == NULL) || (b == NULL))
      return false;
   else if (a == b)
      return true;
   else
      return false;
}
expfun bool Eq(search_range a,
               search_range b)
{
   if (eqSelf(a, b))
      return true;
   else if (eqBegin(getBegin(a), b) == false)
      return false;
   else if (eqEnd(getEnd(a), b) == false)
      return false;
   else if (eqSubranges(getSubranges(a), b) == false)
      return false;
   else
      return true;
}
expfun regoff_t getBegin(search_range s)
{
   if (s != NULL)
      return s->begin;
   else
      return 0;
}
expfun regoff_t getEnd(search_range s)
{
   if (s != NULL)
      return s->end;
   else
      return 0;
}
expfun search_rangeset getSubranges(search_range s)
{
   if (s != NULL)
      return s->subranges;
   else
      return NULL;
}
expfun search_range setBegin(regoff_t begin,
                             search_range s)
{
   if (s != NULL)
      s->begin = begin;
   return s;
}
expfun search_range setEnd(regoff_t end,
                           search_range s)
{
   if (s != NULL)
      s->end = end;
   return s;
}
expfun search_range setSubranges(search_rangeset subranges,
                                 search_range s)
{
   if (s != NULL)
      s->subranges = subranges;
   return s;
}
expfun bool hasSubranges(search_range s)
{
   if (isEmpty(getSubranges(s)) == false)
      return true;
   else
      return false;
}
expfun search_range copy(search_range src,
                         size_t level = 0)
{
   search_range s;

   if (src == NULL)
      return NULL;
   else
   {
      s = (search_range) malloc (sizeof(search_range_struct));
      if (s != NULL)
      {
         if (level > 0)
         {
            s->begin = src->begin;
            s->end = src->end;
            s->subranges = copy(src->subranges, level - 1);
         }
         else
         {
            s->begin = src->begin;
            s->end = src->end;
            s->subranges = src->subranges;
         }
      }
      else
         malloc_error("copy()");

      return s;
   }
}
expfun search_range deepCopy(search_range src)
{
   search_range s;

   if (src == NULL)
      return NULL;
   else
   {
      s = (search_range) malloc (sizeof(search_range_struct));
      if (s != NULL)
      {
         s->begin = src->begin;
         s->end = src->end;
         s->subranges = deepCopy(src->subranges);
      }
      else
         malloc_error("deepCopy()");

      return s;
   }
}
expfun void dump(text Offset,
                 search_range s,
                 FILE* fp = stdout,
                 bool showEmpty = false)
{
   text increment = " ";
   rwtext new_Offset = rwtextNew(strlen(Offset) + strlen(increment) + 1);
   sprintf(new_Offset, "%s%s", Offset, increment);

   if (s == NULL)
   {
      if (showEmpty)
      {
         fprintf(fp, "%s{\n", Offset);
         fprintf(fp, "%sNULL\n", new_Offset);
         fprintf(fp, "%s}\n", Offset);
      }
   }
   else
   {
      fprintf(fp, "%s{\n", Offset);

      fprintf(fp, "%sint begin : %ld\n", new_Offset, (long)getBegin(s));

      fprintf(fp, "%sint end : %ld\n", new_Offset, (long)getEnd(s));

      if (hasSubranges(s) || showEmpty)
      {
         fprintf(fp, "%ssearch_rangeset subranges,\n", new_Offset);
         dump(new_Offset, s->subranges, fp, showEmpty);
         fprintf(fp, "%s\\end search_rangeset\n", new_Offset);
      }

      fprintf(fp, "%s}\n", Offset);
   }
}
expfun void Free(search_range s,
                 size_t level = 0)
{
   if (s ne NULL)
   {
      if (level > 0)
      {

         Free(s->subranges, level - 1);
         s->subranges = NULL;
      }


      free((void *) s);
   }
}
expfun void deepFree(search_range s)
{
   if (s ne NULL)
   {

      deepFree(s->subranges);
      s->subranges = NULL;

      free((void *) s);
   }
}
