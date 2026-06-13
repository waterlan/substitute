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

#ifndef intset_INCLUDED
#define intset_INCLUDED



// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern intset intsetNew(void);
   extern intset intsetNew(int element);
   extern bool eqArray(intset a,
                       intset b);
   extern bool eqSelf(intset a,
                      intset b);
   extern bool Eq(intset a,
                  intset b);
   extern int* getArray(intset i);
   extern bool hasArray(intset i);
   extern size_t size(intset i);
   extern bool isEmpty(intset i);
   extern void addFirst(int i,
                        intset set);
   extern void add(int i,
                   intset set);
   extern void insert(int i,
                      size_t position,
                      intset set);
   extern int firstElement(intset i);
   extern int elementAt(size_t position,
                        intset set);
   extern int elementAt(ssize_t position,
                        intset set);
   extern int lastElement(intset i);
   extern void remove(size_t position,
                      intset set);
   extern int popFirst(intset i);
   extern int popElement(size_t position,
                         intset set);
   extern int popLast(intset i);
   extern void append(intset src,
                      intset dest);
   extern intset copy(intset src);
   extern void Free(intset i);

   #ifdef intset_cc
      extern void setSize(size_t size,
                          intset set,
                          int initVal);
      extern void put(int i,
                      size_t position,
                      intset set,
                      int initVal);
      extern intset select(intset src,
                           bool (*sel_f) (int),
                           bool state);
      extern void dump(text Offset,
                       intset i,
                       FILE* fp,
                       bool showEmpty);

   #else
      extern void setSize(size_t size,
                          intset set,
                          int initVal = 0);
      extern void put(int i,
                      size_t position,
                      intset set,
                      int initVal = 0);
      extern intset select(intset src,
                           bool (*sel_f) (int),
                           bool state = true);
      extern void dump(text Offset,
                       intset i,
                       FILE* fp = stdout,
                       bool showEmpty = false);

   #endif
// End External Functions
#endif
