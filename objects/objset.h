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

#ifndef objset_INCLUDED
#define objset_INCLUDED



// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern objset objsetNew(void);
   extern objset objsetNew(void* element);
   extern bool eqSelfArray(objset a,
                           objset b);
   extern bool eqArray(objset a,
                       objset b);
   extern bool eqSelf(objset a,
                      objset b);
   extern bool Eq(objset a,
                  objset b);
   extern void** getArray(objset o);
   extern bool hasArray(objset o);
   extern size_t size(objset o);
   extern bool isEmpty(objset o);
   extern void addFirst(void* v,
                        objset set);
   extern void add(void* v,
                   objset set);
   extern void insert(void* v,
                      size_t position,
                      objset set);
   extern void* firstElement(objset o);
   extern void* elementAt(size_t position,
                          objset set);
   extern void* elementAt(ssize_t position,
                          objset set);
   extern void* lastElement(objset o);
   extern void remove(size_t position,
                      objset set);
   extern void* popFirst(objset o);
   extern void* popElement(size_t position,
                           objset set);
   extern void* popLast(objset o);
   extern void append(objset src,
                      objset dest);
   extern objset copy(objset src);
   extern void deepFree(objset o);

   #ifdef objset_cc
      extern void setSize(size_t size,
                          objset set,
                          void* initVal);
      extern void put(void* v,
                      size_t position,
                      objset set,
                      void* initVal);
      extern objset select(objset src,
                           bool (*sel_f) (void *),
                           bool state);
      extern void dump(text Offset,
                       objset o,
                       FILE* fp,
                       bool showEmpty);
      extern void Free(objset o,
                       size_t level);

   #else
      extern void setSize(size_t size,
                          objset set,
                          void* initVal = NULL);
      extern void put(void* v,
                      size_t position,
                      objset set,
                      void* initVal = NULL);
      extern objset select(objset src,
                           bool (*sel_f) (void *),
                           bool state = true);
      extern void dump(text Offset,
                       objset o,
                       FILE* fp = stdout,
                       bool showEmpty = false);
      extern void Free(objset o,
                       size_t level = 0);

   #endif
// End External Functions
#endif
