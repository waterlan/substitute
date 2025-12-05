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

#define text_cc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"

#include "error.h"
#include "arithmetic.h"
#include "nameset.h"


expfun rwtext rwtextNew(size_t size)
{
   rwtext buffer = NULL;

   if (size > 0)
   {
      buffer = (rwtext) malloc (sizeof(char) * size);
      if (buffer eq NULL)
         malloc_error("rwtextNew(size)");
   }

   return buffer;
}
expfun text textNew(size_t size)
{
   return rwtextNew(size);
}
expfun rwtext rwtextNew(text string)
{
   rwtext buffer = NULL;

   if (string ne NULL)
   {
      buffer = rwtextNew(strlen(string) + 1);
      if (buffer ne NULL)
         strcpy(buffer, string);
      else
         malloc_error("rwtextNew(text)");
   }

   return buffer;
}
expfun text textNew(text string)
{
   return rwtextNew(string);
}
expfun bool Eq(text a,
               text b)
{
   if ((a == NULL) || (b == NULL))
      return false;
   else if (strcmp(a, b) == 0)
      return true;
   else
      return false;
}
expfun bool eqSelf(text a,
                   text b)
{
   if ((a == NULL) || (b == NULL))
      return false;
   else if (a == b)
      return true;
   else
      return false;
}
expfun text concat(text a,
                   text b)
{
   rwtext res = (rwtext) malloc(sizeof(char) * (strlen(a) + strlen(b) + 1));
   if (res ne NULL)
   {
      strcpy(res, a);
      strcpy(res + strlen(res), b);
   }
   else
      malloc_error("concat()");


   return res;
}
expfun text concat(text a,
                   text b,
                   text c)
{
   rwtext res = (rwtext) malloc(sizeof(char) * (strlen(a) + strlen(b) + strlen(c) + 1));
   if (res ne NULL)
   {
      strcpy(res, a);
      strcpy(res + strlen(res), b);
      strcpy(res + strlen(res), c);
   }
   else
      malloc_error("concat()");


   return res;
}
expfun text concat(text a,
                   text b,
                   text c,
                   text d)
{
   rwtext res = (rwtext) malloc(sizeof(char) * (strlen(a) + strlen(b) + strlen(c) + strlen(d) + 1));
   if (res ne NULL)
   {
      strcpy(res, a);
      strcpy(res + strlen(res), b);
      strcpy(res + strlen(res), c);
      strcpy(res + strlen(res), d);
   }
   else
      malloc_error("concat()");


   return res;
}
expfun text repeat(text pattern,
                   size_t amount,
                   int bufferNr = -1)
{
   size_t count = 0;
   static nameset buffers = NULL;
   rwtext buffer = NULL;

   if (buffers eq NULL)
      buffers = namesetNew();

   amount = limitNeg(amount, 0);

   if (bufferNr >= 0)
      buffer = (rwtext) elementAt((size_t) bufferNr, buffers);

   if (buffer eq NULL)
      buffer = rwtextNew(strlen(pattern) * amount + 1);
   else
      buffer = (rwtext) realloc((void *) buffer, sizeof(char) * (strlen(pattern) * amount + 1));

   if (buffer != NULL)
   {
      if (bufferNr >= 0)
         put(buffer, (size_t) bufferNr, buffers);

      buffer[0] = '\0';
      while(count < amount)
      {
         strcpy(buffer + strlen(buffer), pattern);
         count = count + 1;
      }
   }
   else
      malloc_error("repeat(pattern, amount, bufferNr)");

   return buffer;
}
expfun text Spaces(size_t amount,
                   int bufferNr = 0)
{
   return repeat(" ", amount, bufferNr);
}
expfun text Tab(size_t amount,
                int bufferNr = 0)
{
   size_t tabSize = 3;
   return Spaces(tabSize*amount, bufferNr);
}
expfun text toString(int i)
{
   char buffer[100];
   sprintf(buffer, "%d", i);
   return rwtextNew((rwtext) buffer);
}
expfun text toString(double d)
{
   char buffer[100];
   sprintf(buffer, "%g", d);
   return rwtextNew((rwtext) buffer);
}
expfun text toString(size_t s)
{
   char buffer[100];
   sprintf(buffer, "%zu", s);
   return rwtextNew((rwtext) buffer);
}
expfun text toString(ssize_t s)
{
   char buffer[100];
   sprintf(buffer, "%zd", s);
   return rwtextNew((rwtext) buffer);
}
