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

#ifndef nameset_INCLUDED
#define nameset_INCLUDED



// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern nameset namesetNew(void);
   extern nameset namesetNew(text element);
   extern bool eqSelfArray(nameset a,
                           nameset b);
   extern bool eqArray(nameset a,
                       nameset b);
   extern bool eqSelf(nameset a,
                      nameset b);
   extern bool Eq(nameset a,
                  nameset b);
   extern text* getArray(nameset n);
   extern bool hasArray(nameset n);
   extern size_t size(nameset n);
   extern bool isEmpty(nameset n);
   extern void addFirst(text t,
                        nameset set);
   extern void add(text t,
                   nameset set);
   extern void insert(text t,
                      size_t position,
                      nameset set);
   extern text firstElement(nameset n);
   extern text elementAt(size_t position,
                         nameset set);
   extern text elementAt(ssize_t position,
                         nameset set);
   extern text lastElement(nameset n);
   extern void deepRemove(size_t position,
                          nameset set);
   extern text popFirst(nameset n);
   extern text popElement(size_t position,
                          nameset set);
   extern text popLast(nameset n);
   extern void deepAppend(nameset src,
                          nameset dest);
   extern nameset deepCopy(nameset src);
   extern void deepFree(nameset n);

   #ifdef nameset_cc
      extern void setSize(size_t size,
                          nameset set,
                          text initVal);
      extern void put(text t,
                      size_t position,
                      nameset set,
                      text initVal);
      extern void remove(size_t position,
                         nameset set,
                         size_t level);
      extern void append(nameset src,
                         nameset dest,
                         size_t level);
      extern nameset copy(nameset src,
                          size_t level);
      extern nameset select(nameset src,
                            bool (*sel_f) (text),
                            bool state);
      extern void dump(text Offset,
                       nameset n,
                       FILE* fp,
                       bool showEmpty);
      extern void Free(nameset n,
                       size_t level);

   #else
      extern void setSize(size_t size,
                          nameset set,
                          text initVal = NULL);
      extern void put(text t,
                      size_t position,
                      nameset set,
                      text initVal = NULL);
      extern void remove(size_t position,
                         nameset set,
                         size_t level = 0);
      extern void append(nameset src,
                         nameset dest,
                         size_t level = 0);
      extern nameset copy(nameset src,
                          size_t level = 0);
      extern nameset select(nameset src,
                            bool (*sel_f) (text),
                            bool state = true);
      extern void dump(text Offset,
                       nameset n,
                       FILE* fp = stdout,
                       bool showEmpty = false);
      extern void Free(nameset n,
                       size_t level = 0);

   #endif
// End External Functions
#endif
