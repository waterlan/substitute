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

#define actionset_cc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"

#include "error.h"
#include "text.h"
#include "action.h"
#include "actionset.h"


expfun actionset actionsetNew(void)
{
   actionset a = (actionset) malloc (sizeof(actionset_struct));
   if (a != NULL)
   {
      a->array = NULL;
      a->size = 0;
   }
   else
      malloc_error("actionsetNew()");

   return a;
}
expfun actionset actionsetNew(action element)
{
   actionset a = actionsetNew();

   if (element != NULL)
      add(element, a);

   return a;
}
expfun bool eqSelfArray(actionset a,
                        actionset b)
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
expfun bool eqArray(actionset a,
                    actionset b)
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
expfun bool eqSelf(actionset a,
                   actionset b)
{
   if ((a == NULL) || (b == NULL))
      return false;
   else if (a == b)
      return true;
   else
      return false;
}
expfun bool Eq(actionset a,
               actionset b)
{
   if (eqSelf(a, b))
      return true;
   else if (eqArray(a, b) == false)
      return false;
   else
      return true;
}
expfun action* getArray(actionset a)
{
   if (a != NULL)
      return a->array;
   else
      return NULL;
}
expfun bool hasArray(actionset a)
{
   if (isEmpty(a) == false)
      return true;
   else
      return false;
}
expfun size_t size(actionset a)
{
   if (a != NULL)
      return a->size;
   else
      return 0;
}
expfun void setSize(size_t size,
                    actionset set,
                    action initVal = NULL)
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
            set->array = (action *) malloc(sizeof(action) * size);
         else
            set->array = (action *) realloc((void *) set->array, sizeof(action) * size);

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
expfun bool isEmpty(actionset a)
{
   if (size(a) > 0)
      return false;
   else
      return true;
}
expfun void addFirst(action a,
                     actionset set)
{
   insert(a, 0, set);
}
expfun void add(action a,
                actionset set)
{
   if (set != NULL)
   {
      setSize(set->size + 1, set);
      if (set->array != NULL)
         set->array[set->size - 1] = a;
      else
         malloc_error("add()");
   }
}
expfun void put(action a,
                size_t position,
                actionset set,
                action initVal = NULL)
{
   if (set != NULL)
   {
      if (position >= set->size)
         setSize(position + 1, set, initVal);
      if (set->array != NULL)
         set->array[position] = a;
      else
         malloc_error("put(a, position, set, initVal)");
   }
}
expfun void insert(action a,
                   size_t position,
                   actionset set)
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
      put(a, position, set);
   }
}
expfun action firstElement(actionset a)
{
   if (isEmpty(a) == false)
      return a->array[0];
   else
      return NULL;
}
expfun action elementAt(size_t position,
                        actionset set)
{
   if (set != NULL)
   {
      if (position < set->size)
         return set->array[position];
   }

   return NULL;
}
expfun action elementAt(ssize_t position,
                        actionset set)
{
   if (set != NULL)
   {
      if (0 <= position)
         return elementAt((size_t) position, set);
   }

   return NULL;
}
expfun action lastElement(actionset a)
{
   if (isEmpty(a) == false)
      return a->array[a->size - 1];
   else
      return NULL;
}
expfun void remove(size_t position,
                   actionset set,
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
                       actionset set)
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
expfun action popFirst(actionset a)
{
   action popElement = firstElement(a);

   if (isEmpty(a) == false)
      remove(0, a);

   return popElement;
}
expfun action popElement(size_t position,
                         actionset set)
{
   action popElement = elementAt(position, set);

   if (isEmpty(set) == false)
      remove(position, set);

   return popElement;
}
expfun action popLast(actionset a)
{
   action popElement = lastElement(a);

   if (isEmpty(a) == false)
      remove(a->size - 1, a);

   return popElement;
}
expfun void append(actionset src,
                   actionset dest,
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
expfun void deepAppend(actionset src,
                       actionset dest)
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
expfun actionset copy(actionset src,
                      size_t level = 0)
{
   actionset a;

   if (src == NULL)
      return NULL;
   else
   {
      a = (actionset) malloc (sizeof(actionset_struct));
      if (a != NULL)
      {
         a->array = NULL;
         a->size = 0;
         if (level > 0)
            append(src, a, level - 1);
         else
            append(src, a);
      }
      else
         malloc_error("copy()");

      return a;
   }
}
expfun actionset deepCopy(actionset src)
{
   actionset a;

   if (src == NULL)
      return NULL;
   else
   {
      a = (actionset) malloc (sizeof(actionset_struct));
      if (a != NULL)
      {
         a->array = NULL;
         a->size = 0;
         deepAppend(src, a);
      }
      else
         malloc_error("deepCopy()");

      return a;
   }
}
expfun actionset select(actionset src,
                        bool (*sel_f) (action),
                        bool state = true)
{
   actionset set = actionsetNew();
   action arrayElement;
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
                 actionset a,
                 FILE* fp = stdout,
                 bool showEmpty = false)
{
   size_t index;

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

      if (a->array == NULL)
      {
         if (showEmpty)
            fprintf(fp, "%saction array : NULL\n", new_Offset);
      }
      else
      {
         if ((isEmpty(a) == false) || showEmpty)
         {
            fprintf(fp, "%ssize_t size : %zu\n", new_Offset, a->size);

            index = 0;
            while(index < a->size)
            {

               fprintf(fp, "%saction array[%zu],\n", new_Offset, index);
               dump(new_Offset, elementAt(index, a), fp, showEmpty);
               fprintf(fp, "%s\\end action[%zu]\n", new_Offset, index);

               index = index + 1;
            }
         }
      }

      fprintf(fp, "%s}\n", Offset);
   }
}
expfun void Free(actionset a,
                 size_t level = 0)
{
   size_t index;

   if (a ne NULL)
   {
      if (level > 0)
      {

         index = 0;
         while(index < a->size)
         {
            Free(a->array[index], level - 1);

            index = index + 1;
         }
      }

      if (a->array ne NULL)
      {
         free((void *) a->array);
         a->array = NULL;
         a->size = 0;
      }

      free((void *) a);
   }
}
expfun void deepFree(actionset a)
{
   size_t index;

   if (a ne NULL)
   {

      index = 0;
      while(index < a->size)
      {
         deepFree(a->array[index]);

         index = index + 1;
      }
      if (a->array ne NULL)
      {
         free((void *) a->array);
         a->array = NULL;
         a->size = 0;
      }

      free((void *) a);
   }
}
