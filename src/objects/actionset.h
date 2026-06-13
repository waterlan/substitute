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

#ifndef actionset_INCLUDED
#define actionset_INCLUDED



// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern actionset actionsetNew(void);
   extern actionset actionsetNew(action element);
   extern bool eqSelfArray(actionset a,
                           actionset b);
   extern bool eqArray(actionset a,
                       actionset b);
   extern bool eqSelf(actionset a,
                      actionset b);
   extern bool Eq(actionset a,
                  actionset b);
   extern action* getArray(actionset a);
   extern bool hasArray(actionset a);
   extern size_t size(actionset a);
   extern bool isEmpty(actionset a);
   extern void addFirst(action a,
                        actionset set);
   extern void add(action a,
                   actionset set);
   extern void insert(action a,
                      size_t position,
                      actionset set);
   extern action firstElement(actionset a);
   extern action elementAt(size_t position,
                           actionset set);
   extern action elementAt(ssize_t position,
                           actionset set);
   extern action lastElement(actionset a);
   extern void deepRemove(size_t position,
                          actionset set);
   extern action popFirst(actionset a);
   extern action popElement(size_t position,
                            actionset set);
   extern action popLast(actionset a);
   extern void deepAppend(actionset src,
                          actionset dest);
   extern actionset deepCopy(actionset src);
   extern void deepFree(actionset a);

   #ifdef actionset_cc
      extern void setSize(size_t size,
                          actionset set,
                          action initVal);
      extern void put(action a,
                      size_t position,
                      actionset set,
                      action initVal);
      extern void remove(size_t position,
                         actionset set,
                         size_t level);
      extern void append(actionset src,
                         actionset dest,
                         size_t level);
      extern actionset copy(actionset src,
                            size_t level);
      extern actionset select(actionset src,
                              bool (*sel_f) (action),
                              bool state);
      extern void dump(text Offset,
                       actionset a,
                       FILE* fp,
                       bool showEmpty);
      extern void Free(actionset a,
                       size_t level);

   #else
      extern void setSize(size_t size,
                          actionset set,
                          action initVal = NULL);
      extern void put(action a,
                      size_t position,
                      actionset set,
                      action initVal = NULL);
      extern void remove(size_t position,
                         actionset set,
                         size_t level = 0);
      extern void append(actionset src,
                         actionset dest,
                         size_t level = 0);
      extern actionset copy(actionset src,
                            size_t level = 0);
      extern actionset select(actionset src,
                              bool (*sel_f) (action),
                              bool state = true);
      extern void dump(text Offset,
                       actionset a,
                       FILE* fp = stdout,
                       bool showEmpty = false);
      extern void Free(actionset a,
                       size_t level = 0);

   #endif
// End External Functions
#endif
