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

#define intset_cc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"

#include "error.h"
#include "text.h"
#include "intset.h"


expfun intset intsetNew(void)
{
   intset i = (intset) malloc (sizeof(intset_struct));
   if (i != NULL)
   {
      i->array = NULL;
      i->size = 0;
   }
   else
      malloc_error("intsetNew()");

   return i;
}
expfun intset intsetNew(int element)
{
   intset i = intsetNew();
   add(element, i);

   return i;
}
expfun bool eqArray(intset a,
                    intset b)
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
         if (elementAt(index, a) != elementAt(index, b))
            return false;

         index = index + 1;
      }
      return true;
   }
}
expfun bool eqSelf(intset a,
                   intset b)
{
   if ((a == NULL) || (b == NULL))
      return false;
   else if (a == b)
      return true;
   else
      return false;
}
expfun bool Eq(intset a,
               intset b)
{
   if (eqSelf(a, b))
      return true;
   else if (eqArray(a, b) == false)
      return false;
   else
      return true;
}
expfun int* getArray(intset i)
{
   if (i != NULL)
      return i->array;
   else
      return NULL;
}
expfun bool hasArray(intset i)
{
   if (isEmpty(i) == false)
      return true;
   else
      return false;
}
expfun size_t size(intset i)
{
   if (i != NULL)
      return i->size;
   else
      return 0;
}
expfun void setSize(size_t size,
                    intset set,
                    int initVal = 0)
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
            set->array = (int *) malloc(sizeof(int) * size);
         else
            set->array = (int *) realloc((void *) set->array, sizeof(int) * size);

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
expfun bool isEmpty(intset i)
{
   if (size(i) > 0)
      return false;
   else
      return true;
}
expfun void addFirst(int i,
                     intset set)
{
   insert(i, 0, set);
}
expfun void add(int i,
                intset set)
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
expfun void put(int i,
                size_t position,
                intset set,
                int initVal = 0)
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
expfun void insert(int i,
                   size_t position,
                   intset set)
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
expfun int firstElement(intset i)
{
   if (isEmpty(i) == false)
      return i->array[0];
   else
      return 0;
}
expfun int elementAt(size_t position,
                     intset set)
{
   if (set != NULL)
   {
      if (position < set->size)
         return set->array[position];
   }

   return 0;
}
expfun int elementAt(ssize_t position,
                     intset set)
{
   if (set != NULL)
   {
      if (0 <= position)
         return elementAt((size_t) position, set);
   }

   return 0;
}
expfun int lastElement(intset i)
{
   if (isEmpty(i) == false)
      return i->array[i->size - 1];
   else
      return 0;
}
expfun void remove(size_t position,
                   intset set)
{
   size_t index;
   if (set != NULL)
   {
      if (position < set->size)
      {
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
expfun int popFirst(intset i)
{
   int popElement = firstElement(i);

   if (isEmpty(i) == false)
      remove(0, i);

   return popElement;
}
expfun int popElement(size_t position,
                      intset set)
{
   int popElement = elementAt(position, set);

   if (isEmpty(set) == false)
      remove(position, set);

   return popElement;
}
expfun int popLast(intset i)
{
   int popElement = lastElement(i);

   if (isEmpty(i) == false)
      remove(i->size - 1, i);

   return popElement;
}
expfun void append(intset src,
                   intset dest)
{
   if (src != NULL)
   {
      size_t index = 0;
      while(index < src->size)
      {
         add(elementAt(index, src), dest);
         index = index + 1;
      }
   }
}
expfun intset copy(intset src)
{
   intset i;

   if (src == NULL)
      return NULL;
   else
   {
      i = (intset) malloc (sizeof(intset_struct));
      if (i != NULL)
      {
         i->array = NULL;
         i->size = 0;
         append(src, i);
      }
      else
         malloc_error("copy()");

      return i;
   }
}
expfun intset select(intset src,
                     bool (*sel_f) (int),
                     bool state = true)
{
   intset set = intsetNew();
   int arrayElement;
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
                 intset i,
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
            fprintf(fp, "%sint array : NULL\n", new_Offset);
      }
      else
      {
         if ((isEmpty(i) == false) || showEmpty)
         {
            fprintf(fp, "%ssize_t size : %zu\n", new_Offset, i->size);

            index = 0;
            while(index < i->size)
            {

               fprintf(fp, "%sint array[%zu] : %d\n", new_Offset, index, elementAt(index, i));

               index = index + 1;
            }
         }
      }

      fprintf(fp, "%s}\n", Offset);
   }
}
expfun void Free(intset i)
{
   if (i ne NULL)
   {
      if (i->array ne NULL)
      {
         free((void *) i->array);
         i->array = NULL;
         i->size = 0;
      }

      free((void *) i);
   }
}
