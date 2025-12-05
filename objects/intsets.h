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

#ifndef intsets_INCLUDED
#define intsets_INCLUDED



// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern intsets intsetsNew(void);
   extern intsets intsetsNew(intset element);
   extern bool eqSelfArray(intsets a,
                           intsets b);
   extern bool eqArray(intsets a,
                       intsets b);
   extern bool eqSelf(intsets a,
                      intsets b);
   extern bool Eq(intsets a,
                  intsets b);
   extern intset* getArray(intsets i);
   extern bool hasArray(intsets i);
   extern size_t size(intsets i);
   extern bool isEmpty(intsets i);
   extern void addFirst(intset i,
                        intsets set);
   extern void add(intset i,
                   intsets set);
   extern void insert(intset i,
                      size_t position,
                      intsets set);
   extern intset firstElement(intsets i);
   extern intset elementAt(size_t position,
                           intsets set);
   extern intset elementAt(ssize_t position,
                           intsets set);
   extern intset lastElement(intsets i);
   extern void deepRemove(size_t position,
                          intsets set);
   extern intset popFirst(intsets i);
   extern intset popElement(size_t position,
                            intsets set);
   extern intset popLast(intsets i);
   extern void deepAppend(intsets src,
                          intsets dest);
   extern intsets deepCopy(intsets src);
   extern void deepFree(intsets i);

   #ifdef intsets_cc
      extern void setSize(size_t size,
                          intsets set,
                          intset initVal);
      extern void put(intset i,
                      size_t position,
                      intsets set,
                      intset initVal);
      extern void remove(size_t position,
                         intsets set,
                         size_t level);
      extern void append(intsets src,
                         intsets dest,
                         size_t level);
      extern intsets copy(intsets src,
                          size_t level);
      extern intsets select(intsets src,
                            bool (*sel_f) (intset),
                            bool state);
      extern void dump(text Offset,
                       intsets i,
                       FILE* fp,
                       bool showEmpty);
      extern void Free(intsets i,
                       size_t level);

   #else
      extern void setSize(size_t size,
                          intsets set,
                          intset initVal = NULL);
      extern void put(intset i,
                      size_t position,
                      intsets set,
                      intset initVal = NULL);
      extern void remove(size_t position,
                         intsets set,
                         size_t level = 0);
      extern void append(intsets src,
                         intsets dest,
                         size_t level = 0);
      extern intsets copy(intsets src,
                          size_t level = 0);
      extern intsets select(intsets src,
                            bool (*sel_f) (intset),
                            bool state = true);
      extern void dump(text Offset,
                       intsets i,
                       FILE* fp = stdout,
                       bool showEmpty = false);
      extern void Free(intsets i,
                       size_t level = 0);

   #endif
// End External Functions
#endif
