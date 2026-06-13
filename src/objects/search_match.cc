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

#define search_match_cc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"

#include "error.h"
#include "text.h"
#include "search_rangeset.h"
#include "search_match.h"


expfun search_match search_matchNew(text pattern = NULL,
                                    int flags = 0)
{
   search_match s = (search_match) malloc (sizeof(search_match_struct));
   if (s != NULL)
   {
      s->pattern = pattern;
      s->flags = flags;
      s->valid = false;
      s->ranges = search_rangesetNew();
   }
   else
      malloc_error("search_matchNew()");

   return s;
}
expfun bool eqSelfPattern(text pattern,
                          search_match s)
{
   if ((pattern == NULL) || (hasPattern(s) == false))
      return false;
   else if (eqSelf(pattern, getPattern(s)))
      return true;
   else
      return false;
}
expfun bool eqPattern(text pattern,
                      search_match s)
{
   if ((pattern == NULL) || (hasPattern(s) == false))
      return false;
   else if (Eq(pattern, getPattern(s)))
      return true;
   else
      return false;
}
expfun bool eqFlags(int flags,
                    search_match s)
{
   if (s == NULL)
      return false;
   else if (flags == getFlags(s))
      return true;
   else
      return false;
}
expfun bool eqValid(bool validIn,
                    search_match s)
{
   if (s == NULL)
      return false;
   else if (validIn == valid(s))
      return true;
   else
      return false;
}
expfun bool eqSelfRanges(search_rangeset ranges,
                         search_match s)
{
   if ((ranges == NULL) || (hasRanges(s) == false))
      return false;
   else if (eqSelf(ranges, getRanges(s)))
      return true;
   else
      return false;
}
expfun bool eqRanges(search_rangeset ranges,
                     search_match s)
{
   if ((ranges == NULL) || (hasRanges(s) == false))
      return false;
   else if (Eq(ranges, getRanges(s)))
      return true;
   else
      return false;
}
expfun bool eqSelf(search_match a,
                   search_match b)
{
   if ((a == NULL) || (b == NULL))
      return false;
   else if (a == b)
      return true;
   else
      return false;
}
expfun bool Eq(search_match a,
               search_match b)
{
   if (eqSelf(a, b))
      return true;
   else if (eqPattern(getPattern(a), b) == false)
      return false;
   else if (eqFlags(getFlags(a), b) == false)
      return false;
   else if (eqValid(valid(a), b) == false)
      return false;
   else if (eqRanges(getRanges(a), b) == false)
      return false;
   else
      return true;
}
expfun text getPattern(search_match s)
{
   if (s != NULL)
      return s->pattern;
   else
      return NULL;
}
expfun int getFlags(search_match s)
{
   if (s != NULL)
      return s->flags;
   else
      return 0;
}
expfun bool valid(search_match s)
{
   if (s != NULL)
      return s->valid;
   else
      return false;
}
expfun search_rangeset getRanges(search_match s)
{
   if (s != NULL)
      return s->ranges;
   else
      return NULL;
}
expfun search_match setPattern(text pattern,
                               search_match s)
{
   if (s != NULL)
      s->pattern = pattern;
   return s;
}
expfun search_match setFlags(int flags,
                             search_match s)
{
   if (s != NULL)
      s->flags = flags;
   return s;
}
expfun search_match setValid(bool valid,
                             search_match s)
{
   if (s != NULL)
      s->valid = valid;
   return s;
}
expfun search_match setRanges(search_rangeset ranges,
                              search_match s)
{
   if (s != NULL)
      s->ranges = ranges;
   return s;
}
expfun bool hasPattern(search_match s)
{
   if (getPattern(s) != NULL)
      return true;
   else
      return false;
}
expfun bool hasRanges(search_match s)
{
   if (isEmpty(getRanges(s)) == false)
      return true;
   else
      return false;
}
expfun search_match copy(search_match src,
                         size_t level = 0)
{
   search_match s;

   if (src == NULL)
      return NULL;
   else
   {
      s = (search_match) malloc (sizeof(search_match_struct));
      if (s != NULL)
      {
         if (level > 0)
         {
            s->pattern = textNew(src->pattern);
            s->flags = src->flags;
            s->valid = src->valid;
            s->ranges = copy(src->ranges, level - 1);
         }
         else
         {
            s->pattern = src->pattern;
            s->flags = src->flags;
            s->valid = src->valid;
            s->ranges = src->ranges;
         }
      }
      else
         malloc_error("copy()");

      return s;
   }
}
expfun search_match deepCopy(search_match src)
{
   search_match s;

   if (src == NULL)
      return NULL;
   else
   {
      s = (search_match) malloc (sizeof(search_match_struct));
      if (s != NULL)
      {
         s->pattern = textNew(src->pattern);
         s->flags = src->flags;
         s->valid = src->valid;
         s->ranges = deepCopy(src->ranges);
      }
      else
         malloc_error("deepCopy()");

      return s;
   }
}
expfun void dump(text Offset,
                 search_match s,
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

      if (hasPattern(s) || showEmpty)
      {
         if (s->pattern ne NULL)
            fprintf(fp, "%stext pattern : %s\n", new_Offset, s->pattern);
         else if (showEmpty)
            fprintf(fp, "%stext pattern : NULL\n", new_Offset);
      }

      fprintf(fp, "%sint flags : %d\n", new_Offset, getFlags(s));

      fprintf(fp, "%sbool valid : %d\n", new_Offset, valid(s));

      if (hasRanges(s) || showEmpty)
      {
         fprintf(fp, "%ssearch_rangeset ranges,\n", new_Offset);
         dump(new_Offset, s->ranges, fp, showEmpty);
         fprintf(fp, "%s\\end search_rangeset\n", new_Offset);
      }

      fprintf(fp, "%s}\n", Offset);
   }
}
expfun void Free(search_match s,
                 size_t level = 0)
{
   if (s ne NULL)
   {
      if (level > 0)
      {

         if (s->pattern ne NULL)
         {
            free((void *) s->pattern);
            s->pattern = NULL;
         }

         Free(s->ranges, level - 1);
         s->ranges = NULL;
      }


      free((void *) s);
   }
}
expfun void deepFree(search_match s)
{
   if (s ne NULL)
   {

      if (s->pattern ne NULL)
      {
         free((void *) s->pattern);
         s->pattern = NULL;
      }

      deepFree(s->ranges);
      s->ranges = NULL;

      free((void *) s);
   }
}
