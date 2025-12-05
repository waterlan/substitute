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

#define action_cc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"

#include "error.h"
#include "text.h"
#include "action.h"


expfun action actionNew(text matchPat = NULL,
                        text replacePat = NULL)
{
   action a = (action) malloc (sizeof(action_struct));
   if (a != NULL)
   {
      a->matchPat = matchPat;
      a->replacePat = replacePat;
   }
   else
      malloc_error("actionNew()");

   return a;
}
expfun bool eqSelfMatchPat(text matchPat,
                           action a)
{
   if ((matchPat == NULL) || (hasMatchPat(a) == false))
      return false;
   else if (eqSelf(matchPat, getMatchPat(a)))
      return true;
   else
      return false;
}
expfun bool eqMatchPat(text matchPat,
                       action a)
{
   if ((matchPat == NULL) || (hasMatchPat(a) == false))
      return false;
   else if (Eq(matchPat, getMatchPat(a)))
      return true;
   else
      return false;
}
expfun bool eqSelfReplacePat(text replacePat,
                             action a)
{
   if ((replacePat == NULL) || (hasReplacePat(a) == false))
      return false;
   else if (eqSelf(replacePat, getReplacePat(a)))
      return true;
   else
      return false;
}
expfun bool eqReplacePat(text replacePat,
                         action a)
{
   if ((replacePat == NULL) || (hasReplacePat(a) == false))
      return false;
   else if (Eq(replacePat, getReplacePat(a)))
      return true;
   else
      return false;
}
expfun bool eqSelf(action a,
                   action b)
{
   if ((a == NULL) || (b == NULL))
      return false;
   else if (a == b)
      return true;
   else
      return false;
}
expfun bool Eq(action a,
               action b)
{
   if (eqSelf(a, b))
      return true;
   else if (eqMatchPat(getMatchPat(a), b) == false)
      return false;
   else if (eqReplacePat(getReplacePat(a), b) == false)
      return false;
   else
      return true;
}
expfun text getMatchPat(action a)
{
   if (a != NULL)
      return a->matchPat;
   else
      return NULL;
}
expfun text getReplacePat(action a)
{
   if (a != NULL)
      return a->replacePat;
   else
      return NULL;
}
expfun action setMatchPat(text matchPat,
                          action a)
{
   if (a != NULL)
      a->matchPat = matchPat;
   return a;
}
expfun action setReplacePat(text replacePat,
                            action a)
{
   if (a != NULL)
      a->replacePat = replacePat;
   return a;
}
expfun bool hasMatchPat(action a)
{
   if (getMatchPat(a) != NULL)
      return true;
   else
      return false;
}
expfun bool hasReplacePat(action a)
{
   if (getReplacePat(a) != NULL)
      return true;
   else
      return false;
}
expfun action copy(action src,
                   size_t level = 0)
{
   action a;

   if (src == NULL)
      return NULL;
   else
   {
      a = (action) malloc (sizeof(action_struct));
      if (a != NULL)
      {
         if (level > 0)
         {
            a->matchPat = textNew(src->matchPat);
            a->replacePat = textNew(src->replacePat);
         }
         else
         {
            a->matchPat = src->matchPat;
            a->replacePat = src->replacePat;
         }
      }
      else
         malloc_error("copy()");

      return a;
   }
}
expfun action deepCopy(action src)
{
   action a;

   if (src == NULL)
      return NULL;
   else
   {
      a = (action) malloc (sizeof(action_struct));
      if (a != NULL)
      {
         a->matchPat = textNew(src->matchPat);
         a->replacePat = textNew(src->replacePat);
      }
      else
         malloc_error("deepCopy()");

      return a;
   }
}
expfun void dump(text Offset,
                 action a,
                 FILE* fp = stdout,
                 bool showEmpty = false)
{
   text increment = " ";
   rwtext new_Offset = rwtextNew(strlen(Offset) + strlen(increment) + 1);
   sprintf(new_Offset, "%s%s", Offset, increment);

   if (a == NULL)
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

      if (hasMatchPat(a) || showEmpty)
      {
         if (a->matchPat ne NULL)
            fprintf(fp, "%stext matchPat : %s\n", new_Offset, a->matchPat);
         else if (showEmpty)
            fprintf(fp, "%stext matchPat : NULL\n", new_Offset);
      }

      if (hasReplacePat(a) || showEmpty)
      {
         if (a->replacePat ne NULL)
            fprintf(fp, "%stext replacePat : %s\n", new_Offset, a->replacePat);
         else if (showEmpty)
            fprintf(fp, "%stext replacePat : NULL\n", new_Offset);
      }

      fprintf(fp, "%s}\n", Offset);
   }
}
expfun void Free(action a,
                 size_t level = 0)
{
   if (a ne NULL)
   {
      if (level > 0)
      {

         if (a->matchPat ne NULL)
         {
            free((void *) a->matchPat);
            a->matchPat = NULL;
         }

         if (a->replacePat ne NULL)
         {
            free((void *) a->replacePat);
            a->replacePat = NULL;
         }
      }


      free((void *) a);
   }
}
expfun void deepFree(action a)
{
   if (a ne NULL)
   {

      if (a->matchPat ne NULL)
      {
         free((void *) a->matchPat);
         a->matchPat = NULL;
      }

      if (a->replacePat ne NULL)
      {
         free((void *) a->replacePat);
         a->replacePat = NULL;
      }

      free((void *) a);
   }
}
