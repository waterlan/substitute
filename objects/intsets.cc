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

#define intsets_cc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"

#include "error.h"
#include "text.h"
#include "intset.h"
#include "intsets.h"


expfun intsets intsetsNew(void)
{
   intsets i = (intsets) malloc (sizeof(intsets_struct));
   if (i != NULL)
   {
      i->array = NULL;
      i->size = 0;
   }
   else
      malloc_error("intsetsNew()");

   return i;
}
expfun intsets intsetsNew(intset element)
{
   intsets i = intsetsNew();

   if (element != NULL)
      add(element, i);

   return i;
}
expfun bool eqSelfArray(intsets a,
                        intsets b)
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
expfun bool eqArray(intsets a,
                    intsets b)
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
expfun bool eqSelf(intsets a,
                   intsets b)
{
   if ((a == NULL) || (b == NULL))
      return false;
   else if (a == b)
      return true;
   else
      return false;
}
expfun bool Eq(intsets a,
               intsets b)
{
   if (eqSelf(a, b))
      return true;
   else if (eqArray(a, b) == false)
      return false;
   else
      return true;
}
expfun intset* getArray(intsets i)
{
   if (i != NULL)
      return i->array;
   else
      return NULL;
}
expfun bool hasArray(intsets i)
{
   if (isEmpty(i) == false)
      return true;
   else
      return false;
}
expfun size_t size(intsets i)
{
   if (i != NULL)
      return i->size;
   else
      return 0;
}
expfun void setSize(size_t size,
                    intsets set,
                    intset initVal = NULL)
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
            set->array = (intset *) malloc(sizeof(intset) * size);
         else
            set->array = (intset *) realloc((void *) set->array, sizeof(intset) * size);

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
expfun bool isEmpty(intsets i)
{
   if (size(i) > 0)
      return false;
   else
      return true;
}
expfun void addFirst(intset i,
                     intsets set)
{
   insert(i, 0, set);
}
expfun void add(intset i,
                intsets set)
{
   if (set != NULL)
   {
      setSize(set->size + 1, set);
      if (set->array != NULL)
         set->array[set->size - 1] = i;
      else
         malloc_error("add()");
   }
}
expfun void put(intset i,
                size_t position,
                intsets set,
                intset initVal = NULL)
{
   if (set != NULL)
   {
      if (position >= set->size)
         setSize(position + 1, set, initVal);
      if (set->array != NULL)
         set->array[position] = i;
      else
         malloc_error("put(i, position, set, initVal)");
   }
}
expfun void insert(intset i,
                   size_t position,
                   intsets set)
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
      put(i, position, set);
   }
}
expfun intset firstElement(intsets i)
{
   if (isEmpty(i) == false)
      return i->array[0];
   else
      return NULL;
}
expfun intset elementAt(size_t position,
                        intsets set)
{
   if (set != NULL)
   {
      if (position < set->size)
         return set->array[position];
   }

   return NULL;
}
expfun intset elementAt(ssize_t position,
                        intsets set)
{
   if (set != NULL)
   {
      if (0 <= position)
         return elementAt((size_t) position, set);
   }

   return NULL;
}
expfun intset lastElement(intsets i)
{
   if (isEmpty(i) == false)
      return i->array[i->size - 1];
   else
      return NULL;
}
expfun void remove(size_t position,
                   intsets set,
                   size_t level = 0)
{
   size_t index;
   if (set != NULL)
   {
      if (position < set->size)
      {
         if (level > 0)
         Free(set->array[position]);

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
                       intsets set)
{
   size_t index;
   if (set != NULL)
   {
      if (position < set->size)
      {
         Free(set->array[position]);

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
expfun intset popFirst(intsets i)
{
   intset popElement = firstElement(i);

   if (isEmpty(i) == false)
      remove(0, i);

   return popElement;
}
expfun intset popElement(size_t position,
                         intsets set)
{
   intset popElement = elementAt(position, set);

   if (isEmpty(set) == false)
      remove(position, set);

   return popElement;
}
expfun intset popLast(intsets i)
{
   intset popElement = lastElement(i);

   if (isEmpty(i) == false)
      remove(i->size - 1, i);

   return popElement;
}
expfun void append(intsets src,
                   intsets dest,
                   size_t level = 0)
{
   if (src != NULL)
   {
      size_t index = 0;

      if (level > 0)
      {
         while(index < src->size)
         {
            add(copy(elementAt(index, src)), dest);
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
expfun void deepAppend(intsets src,
                       intsets dest)
{
   if (src != NULL)
   {
      size_t index = 0;
      while(index < src->size)
      {
         add(copy(elementAt(index, src)), dest);
         index = index + 1;
      }
   }
}
expfun intsets copy(intsets src,
                    size_t level = 0)
{
   intsets i;

   if (src == NULL)
      return NULL;
   else
   {
      i = (intsets) malloc (sizeof(intsets_struct));
      if (i != NULL)
      {
         i->array = NULL;
         i->size = 0;
         if (level > 0)
            append(src, i, level - 1);
         else
            append(src, i);
      }
      else
         malloc_error("copy()");

      return i;
   }
}
expfun intsets deepCopy(intsets src)
{
   intsets i;

   if (src == NULL)
      return NULL;
   else
   {
      i = (intsets) malloc (sizeof(intsets_struct));
      if (i != NULL)
      {
         i->array = NULL;
         i->size = 0;
         deepAppend(src, i);
      }
      else
         malloc_error("deepCopy()");

      return i;
   }
}
expfun intsets select(intsets src,
                      bool (*sel_f) (intset),
                      bool state = true)
{
   intsets set = intsetsNew();
   intset arrayElement;
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
                 intsets i,
                 FILE* fp = stdout,
                 bool showEmpty = false)
{
   size_t index;

   text increment = " ";
   rwtext new_Offset = rwtextNew(strlen(Offset) + strlen(increment) + 1);
   sprintf(new_Offset, "%s%s", Offset, increment);

   if (i == NULL)
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

      if (i->array == NULL)
      {
         if (showEmpty)
            fprintf(fp, "%sintset array : NULL\n", new_Offset);
      }
      else
      {
         if ((isEmpty(i) == false) || showEmpty)
         {
            fprintf(fp, "%ssize_t size : %zu\n", new_Offset, i->size);

            index = 0;
            while(index < i->size)
            {

               fprintf(fp, "%sintset array[%zu],\n", new_Offset, index);
               dump(new_Offset, elementAt(index, i), fp, showEmpty);
               fprintf(fp, "%s\\end intset[%zu]\n", new_Offset, index);

               index = index + 1;
            }
         }
      }

      fprintf(fp, "%s}\n", Offset);
   }
}
expfun void Free(intsets i,
                 size_t level = 0)
{
   size_t index;

   if (i ne NULL)
   {
      if (level > 0)
      {

         index = 0;
         while(index < i->size)
         {
            Free(i->array[index]);

            index = index + 1;
         }
      }

      if (i->array ne NULL)
      {
         free((void *) i->array);
         i->array = NULL;
         i->size = 0;
      }

      free((void *) i);
   }
}
expfun void deepFree(intsets i)
{
   size_t index;

   if (i ne NULL)
   {

      index = 0;
      while(index < i->size)
      {
         Free(i->array[index]);

         index = index + 1;
      }
      if (i->array ne NULL)
      {
         free((void *) i->array);
         i->array = NULL;
         i->size = 0;
      }

      free((void *) i);
   }
}
