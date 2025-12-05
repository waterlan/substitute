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

#define search_rangeset_cc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"

#include "error.h"
#include "text.h"
#include "search_range.h"
#include "search_rangeset.h"


expfun search_rangeset search_rangesetNew(void)
{
   search_rangeset s = (search_rangeset) malloc (sizeof(search_rangeset_struct));
   if (s != NULL)
   {
      s->array = NULL;
      s->size = 0;
   }
   else
      malloc_error("search_rangesetNew()");

   return s;
}
expfun search_rangeset search_rangesetNew(search_range element)
{
   search_rangeset s = search_rangesetNew();

   if (element != NULL)
      add(element, s);

   return s;
}
expfun bool eqSelfArray(search_rangeset a,
                        search_rangeset b)
{
   size_t index;

   if ((a == NULL) || (b == NULL))
      return false;
   else if (a == b)
      return true;
   else if (a->size != b->size)
      return false;
   else
   {
      index = 0;
      while(index < a->size)
      {
         if (eqSelf(elementAt(index, a), elementAt(index, b)) == false)
            return false;

         index = index + 1;
      }
      return true;
   }
}
expfun bool eqArray(search_rangeset a,
                    search_rangeset b)
{
   size_t index;

   if ((a == NULL) || (b == NULL))
      return false;
   else if (a == b)
      return true;
   else if (a->size != b->size)
      return false;
   else
   {
      index = 0;
      while(index < a->size)
      {
         if (Eq(elementAt(index, a), elementAt(index, b)) == false)
            return false;

         index = index + 1;
      }
      return true;
   }
}
expfun bool eqSelf(search_rangeset a,
                   search_rangeset b)
{
   if ((a == NULL) || (b == NULL))
      return false;
   else if (a == b)
      return true;
   else
      return false;
}
expfun bool Eq(search_rangeset a,
               search_rangeset b)
{
   if (eqSelf(a, b))
      return true;
   else if (eqArray(a, b) == false)
      return false;
   else
      return true;
}
expfun search_range* getArray(search_rangeset s)
{
   if (s != NULL)
      return s->array;
   else
      return NULL;
}
expfun bool hasArray(search_rangeset s)
{
   if (isEmpty(s) == false)
      return true;
   else
      return false;
}
expfun size_t size(search_rangeset s)
{
   if (s != NULL)
      return s->size;
   else
      return 0;
}
expfun void setSize(size_t size,
                    search_rangeset set,
                    search_range initVal = NULL)
{
   size_t index;
   if (set != NULL)
   {
      if (size <= 0)
      {
         if (isEmpty(set) eq false)
         {
            free((void *) set->array);
            set->array = NULL;
            set->size = 0;
         }
      }
      else if (size ne set->size)
      {
         if (isEmpty(set))
            set->array = (search_range *) malloc(sizeof(search_range) * size);
         else
            set->array = (search_range *) realloc((void *) set->array, sizeof(search_range) * size);

         if (set->array ne NULL)
         {
            index = set->size;
            while(index < size)
            {
               set->array[index] = initVal;
               index = index + 1;
            }
            set->size = size;
         }
         else
         {
            set->size = 0;
            malloc_error("setSize(size, set, initVal)");
         }
      }
   }
}
expfun bool isEmpty(search_rangeset s)
{
   if (size(s) > 0)
      return false;
   else
      return true;
}
expfun void addFirst(search_range s,
                     search_rangeset set)
{
   insert(s, 0, set);
}
expfun void add(search_range s,
                search_rangeset set)
{
   if (set != NULL)
   {
      setSize(set->size + 1, set);
      if (set->array != NULL)
         set->array[set->size - 1] = s;
      else
         malloc_error("add()");
   }
}
expfun void put(search_range s,
                size_t position,
                search_rangeset set,
                search_range initVal = NULL)
{
   if (set != NULL)
   {
      if (position >= set->size)
         setSize(position + 1, set, initVal);
      if (set->array != NULL)
         set->array[position] = s;
      else
         malloc_error("put(s, position, set, initVal)");
   }
}
expfun void insert(search_range s,
                   size_t position,
                   search_rangeset set)
{
   size_t index;
   if (set != NULL)
   {
      index = set->size;
      while(index > position)
      {
         put(elementAt(index - 1, set), index, set);
         index = index - 1;
      }
      put(s, position, set);
   }
}
expfun search_range firstElement(search_rangeset s)
{
   if (isEmpty(s) == false)
      return s->array[0];
   else
      return NULL;
}
expfun search_range elementAt(size_t position,
                              search_rangeset set)
{
   if (set != NULL)
   {
      if (position < set->size)
         return set->array[position];
   }

   return NULL;
}
expfun search_range elementAt(ssize_t position,
                              search_rangeset set)
{
   if (set != NULL)
   {
      if (0 <= position)
         return elementAt((size_t) position, set);
   }

   return NULL;
}
expfun search_range lastElement(search_rangeset s)
{
   if (isEmpty(s) == false)
      return s->array[s->size - 1];
   else
      return NULL;
}
expfun void remove(size_t position,
                   search_rangeset set,
                   size_t level = 0)
{
   size_t index;
   if (set != NULL)
   {
      if (position < set->size)
      {
         if (level > 0)
            Free(set->array[position], level - 1);

         index = position + 1;
         while(index < set->size)
         {
            put(elementAt(index, set), index - 1, set);
            index = index + 1;
         }
         setSize(set->size - 1, set);
      }
   }
}
expfun void deepRemove(size_t position,
                       search_rangeset set)
{
   size_t index;
   if (set != NULL)
   {
      if (position < set->size)
      {
         deepFree(set->array[position]);

         index = position + 1;
         while(index < set->size)
         {
            put(elementAt(index, set), index - 1, set);
            index = index + 1;
         }
         setSize(set->size - 1, set);
      }
   }
}
expfun search_range popFirst(search_rangeset s)
{
   search_range popElement = firstElement(s);

   if (isEmpty(s) == false)
      remove(0, s);

   return popElement;
}
expfun search_range popElement(size_t position,
                               search_rangeset set)
{
   search_range popElement = elementAt(position, set);

   if (isEmpty(set) == false)
      remove(position, set);

   return popElement;
}
expfun search_range popLast(search_rangeset s)
{
   search_range popElement = lastElement(s);

   if (isEmpty(s) == false)
      remove(s->size - 1, s);

   return popElement;
}
expfun void append(search_rangeset src,
                   search_rangeset dest,
                   size_t level = 0)
{
   if (src != NULL)
   {
      size_t index = 0;

      if (level > 0)
      {
         while(index < src->size)
         {
            add(copy(elementAt(index, src), level - 1), dest);
            index = index + 1;
         }
      }
      else
      {
         while(index < src->size)
         {
            add(elementAt(index, src), dest);
            index = index + 1;
         }
      }
   }
}
expfun void deepAppend(search_rangeset src,
                       search_rangeset dest)
{
   if (src != NULL)
   {
      size_t index = 0;
      while(index < src->size)
      {
         add(deepCopy(elementAt(index, src)), dest);
         index = index + 1;
      }
   }
}
expfun search_rangeset copy(search_rangeset src,
                            size_t level = 0)
{
   search_rangeset s;

   if (src == NULL)
      return NULL;
   else
   {
      s = (search_rangeset) malloc (sizeof(search_rangeset_struct));
      if (s != NULL)
      {
         s->array = NULL;
         s->size = 0;
         if (level > 0)
            append(src, s, level - 1);
         else
            append(src, s);
      }
      else
         malloc_error("copy()");

      return s;
   }
}
expfun search_rangeset deepCopy(search_rangeset src)
{
   search_rangeset s;

   if (src == NULL)
      return NULL;
   else
   {
      s = (search_rangeset) malloc (sizeof(search_rangeset_struct));
      if (s != NULL)
      {
         s->array = NULL;
         s->size = 0;
         deepAppend(src, s);
      }
      else
         malloc_error("deepCopy()");

      return s;
   }
}
expfun search_rangeset select(search_rangeset src,
                              bool (*sel_f) (search_range),
                              bool state = true)
{
   search_rangeset set = search_rangesetNew();
   search_range arrayElement;
   size_t index = 0;
   while(index < size(src))
   {
      arrayElement = elementAt(index, src);
      if (sel_f(arrayElement) eq state)
         add(arrayElement, set);

      index = index + 1;
   }

   return set;
}
expfun void dump(text Offset,
                 search_rangeset s,
                 FILE* fp = stdout,
                 bool showEmpty = false)
{
   size_t index;

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

      if (s->array == NULL)
      {
         if (showEmpty)
            fprintf(fp, "%ssearch_range array : NULL\n", new_Offset);
      }
      else
      {
         if ((isEmpty(s) == false) || showEmpty)
         {
            fprintf(fp, "%ssize_t size : %zu\n", new_Offset, s->size);

            index = 0;
            while(index < s->size)
            {

               fprintf(fp, "%ssearch_range array[%zu],\n", new_Offset, index);
               dump(new_Offset, elementAt(index, s), fp, showEmpty);
               fprintf(fp, "%s\\end search_range[%zu]\n", new_Offset, index);

               index = index + 1;
            }
         }
      }

      fprintf(fp, "%s}\n", Offset);
   }
}
expfun void Free(search_rangeset s,
                 size_t level = 0)
{
   size_t index;

   if (s ne NULL)
   {
      if (level > 0)
      {

         index = 0;
         while(index < s->size)
         {
            Free(s->array[index], level - 1);

            index = index + 1;
         }
      }

      if (s->array ne NULL)
      {
         free((void *) s->array);
         s->array = NULL;
         s->size = 0;
      }

      free((void *) s);
   }
}
expfun void deepFree(search_rangeset s)
{
   size_t index;

   if (s ne NULL)
   {

      index = 0;
      while(index < s->size)
      {
         deepFree(s->array[index]);

         index = index + 1;
      }
      if (s->array ne NULL)
      {
         free((void *) s->array);
         s->array = NULL;
         s->size = 0;
      }

      free((void *) s);
   }
}
