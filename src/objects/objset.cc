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

#define objset_cc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"

#include "error.h"
#include "text.h"
#include "objset.h"


expfun objset objsetNew(void)
{
   objset o = (objset) malloc (sizeof(objset_struct));
   if (o != NULL)
   {
      o->array = NULL;
      o->size = 0;
   }
   else
      malloc_error("objsetNew()");

   return o;
}
expfun objset objsetNew(void* element)
{
   objset o = objsetNew();

   if (element != NULL)
      add(element, o);

   return o;
}
expfun bool eqSelfArray(objset a,
                        objset b)
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
expfun bool eqArray(objset a,
                    objset b)
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
expfun bool eqSelf(objset a,
                   objset b)
{
   if ((a == NULL) || (b == NULL))
      return false;
   else if (a == b)
      return true;
   else
      return false;
}
expfun bool Eq(objset a,
               objset b)
{
   if (eqSelf(a, b))
      return true;
   else if (eqArray(a, b) == false)
      return false;
   else
      return true;
}
expfun void** getArray(objset o)
{
   if (o != NULL)
      return o->array;
   else
      return NULL;
}
expfun bool hasArray(objset o)
{
   if (isEmpty(o) == false)
      return true;
   else
      return false;
}
expfun size_t size(objset o)
{
   if (o != NULL)
      return o->size;
   else
      return 0;
}
expfun void setSize(size_t size,
                    objset set,
                    void* initVal = NULL)
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
            set->array = (void **) malloc(sizeof(void *) * size);
         else
            set->array = (void **) realloc((void *) set->array, sizeof(void *) * size);

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
expfun bool isEmpty(objset o)
{
   if (size(o) > 0)
      return false;
   else
      return true;
}
expfun void addFirst(void* v,
                     objset set)
{
   insert(v, 0, set);
}
expfun void add(void* v,
                objset set)
{
   if (set != NULL)
   {
      setSize(set->size + 1, set);
      if (set->array != NULL)
         set->array[set->size - 1] = v;
      else
         malloc_error("add()");
   }
}
expfun void put(void* v,
                size_t position,
                objset set,
                void* initVal = NULL)
{
   if (set != NULL)
   {
      if (position >= set->size)
         setSize(position + 1, set, initVal);
      if (set->array != NULL)
         set->array[position] = v;
      else
         malloc_error("put(v, position, set, initVal)");
   }
}
expfun void insert(void* v,
                   size_t position,
                   objset set)
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
      put(v, position, set);
   }
}
expfun void* firstElement(objset o)
{
   if (isEmpty(o) == false)
      return o->array[0];
   else
      return NULL;
}
expfun void* elementAt(size_t position,
                       objset set)
{
   if (set != NULL)
   {
      if (position < set->size)
         return set->array[position];
   }

   return NULL;
}
expfun void* elementAt(ssize_t position,
                       objset set)
{
   if (set != NULL)
   {
      if (0 <= position)
         return elementAt((size_t) position, set);
   }

   return NULL;
}
expfun void* lastElement(objset o)
{
   if (isEmpty(o) == false)
      return o->array[o->size - 1];
   else
      return NULL;
}
expfun void remove(size_t position,
                   objset set)
{
   size_t index;
   if (set != NULL)
   {
      if (position < set->size)
      {
         if (set->array[position] ne NULL)
            free((void *) set->array[position]);

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
expfun void* popFirst(objset o)
{
   void *popElement = firstElement(o);

   if (isEmpty(o) == false)
      remove(0, o);

   return popElement;
}
expfun void* popElement(size_t position,
                        objset set)
{
   void *popElement = elementAt(position, set);

   if (isEmpty(set) == false)
      remove(position, set);

   return popElement;
}
expfun void* popLast(objset o)
{
   void *popElement = lastElement(o);

   if (isEmpty(o) == false)
      remove(o->size - 1, o);

   return popElement;
}
expfun void append(objset src,
                   objset dest)
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
expfun objset copy(objset src)
{
   objset o;

   if (src == NULL)
      return NULL;
   else
   {
      o = (objset) malloc (sizeof(objset_struct));
      if (o != NULL)
      {
         o->array = NULL;
         o->size = 0;
         append(src, o);
      }
      else
         malloc_error("copy()");

      return o;
   }
}
expfun objset select(objset src,
                     bool (*sel_f) (void *),
                     bool state = true)
{
   objset set = objsetNew();
   void *arrayElement;
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
                 objset o,
                 FILE* fp = stdout,
                 bool showEmpty = false)
{
   size_t index;

   text increment = " ";
   rwtext new_Offset = rwtextNew(strlen(Offset) + strlen(increment) + 1);
   sprintf(new_Offset, "%s%s", Offset, increment);

   if (o == NULL)
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

      if (o->array == NULL)
      {
         if (showEmpty)
            fprintf(fp, "%svoid * array : NULL\n", new_Offset);
      }
      else
      {
         if ((isEmpty(o) == false) || showEmpty)
         {
            fprintf(fp, "%ssize_t size : %zu\n", new_Offset, o->size);

            index = 0;
            while(index < o->size)
            {

               fprintf(fp, "%svoid * array[%zu] : %p\n", new_Offset, index, elementAt(index, o));

               index = index + 1;
            }
         }
      }

      fprintf(fp, "%s}\n", Offset);
   }
}
expfun void Free(objset o,
                 size_t level = 0)
{
   size_t index;

   if (o ne NULL)
   {
      if (level > 0)
      {

         index = 0;
         while(index < o->size)
         {
            if (o->array[index] ne NULL)
               free((void *) o->array[index]);

            index = index + 1;
         }
      }

      if (o->array ne NULL)
      {
         free((void *) o->array);
         o->array = NULL;
         o->size = 0;
      }

      free((void *) o);
   }
}
expfun void deepFree(objset o)
{
   size_t index;

   if (o ne NULL)
   {

      index = 0;
      while(index < o->size)
      {
         if (o->array[index] ne NULL)
            free((void *) o->array[index]);

         index = index + 1;
      }
      if (o->array ne NULL)
      {
         free((void *) o->array);
         o->array = NULL;
         o->size = 0;
      }

      free((void *) o);
   }
}
