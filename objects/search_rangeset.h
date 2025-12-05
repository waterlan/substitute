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

#ifndef search_rangeset_INCLUDED
#define search_rangeset_INCLUDED



// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern search_rangeset search_rangesetNew(void);
   extern search_rangeset search_rangesetNew(search_range element);
   extern bool eqSelfArray(search_rangeset a,
                           search_rangeset b);
   extern bool eqArray(search_rangeset a,
                       search_rangeset b);
   extern bool eqSelf(search_rangeset a,
                      search_rangeset b);
   extern bool Eq(search_rangeset a,
                  search_rangeset b);
   extern search_range* getArray(search_rangeset s);
   extern bool hasArray(search_rangeset s);
   extern size_t size(search_rangeset s);
   extern bool isEmpty(search_rangeset s);
   extern void addFirst(search_range s,
                        search_rangeset set);
   extern void add(search_range s,
                   search_rangeset set);
   extern void insert(search_range s,
                      size_t position,
                      search_rangeset set);
   extern search_range firstElement(search_rangeset s);
   extern search_range elementAt(size_t position,
                                 search_rangeset set);
   extern search_range elementAt(ssize_t position,
                                 search_rangeset set);
   extern search_range lastElement(search_rangeset s);
   extern void deepRemove(size_t position,
                          search_rangeset set);
   extern search_range popFirst(search_rangeset s);
   extern search_range popElement(size_t position,
                                  search_rangeset set);
   extern search_range popLast(search_rangeset s);
   extern void deepAppend(search_rangeset src,
                          search_rangeset dest);
   extern search_rangeset deepCopy(search_rangeset src);
   extern void deepFree(search_rangeset s);

   #ifdef search_rangeset_cc
      extern void setSize(size_t size,
                          search_rangeset set,
                          search_range initVal);
      extern void put(search_range s,
                      size_t position,
                      search_rangeset set,
                      search_range initVal);
      extern void remove(size_t position,
                         search_rangeset set,
                         size_t level);
      extern void append(search_rangeset src,
                         search_rangeset dest,
                         size_t level);
      extern search_rangeset copy(search_rangeset src,
                                  size_t level);
      extern search_rangeset select(search_rangeset src,
                                    bool (*sel_f) (search_range),
                                    bool state);
      extern void dump(text Offset,
                       search_rangeset s,
                       FILE* fp,
                       bool showEmpty);
      extern void Free(search_rangeset s,
                       size_t level);

   #else
      extern void setSize(size_t size,
                          search_rangeset set,
                          search_range initVal = NULL);
      extern void put(search_range s,
                      size_t position,
                      search_rangeset set,
                      search_range initVal = NULL);
      extern void remove(size_t position,
                         search_rangeset set,
                         size_t level = 0);
      extern void append(search_rangeset src,
                         search_rangeset dest,
                         size_t level = 0);
      extern search_rangeset copy(search_rangeset src,
                                  size_t level = 0);
      extern search_rangeset select(search_rangeset src,
                                    bool (*sel_f) (search_range),
                                    bool state = true);
      extern void dump(text Offset,
                       search_rangeset s,
                       FILE* fp = stdout,
                       bool showEmpty = false);
      extern void Free(search_rangeset s,
                       size_t level = 0);

   #endif
// End External Functions
#endif
