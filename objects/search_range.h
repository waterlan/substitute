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

#ifndef search_range_INCLUDED
#define search_range_INCLUDED



// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern bool eqBegin(int begin,
                       search_range s);
   extern bool eqEnd(int end,
                     search_range s);
   extern bool eqSelfSubranges(search_rangeset subranges,
                               search_range s);
   extern bool eqSubranges(search_rangeset subranges,
                           search_range s);
   extern bool eqSelf(search_range a,
                      search_range b);
   extern bool Eq(search_range a,
                  search_range b);
   extern int getBegin(search_range s);
   extern int getEnd(search_range s);
   extern search_rangeset getSubranges(search_range s);
   extern search_range setBegin(int begin,
                                search_range s);
   extern search_range setEnd(int end,
                              search_range s);
   extern search_range setSubranges(search_rangeset subranges,
                                    search_range s);
   extern bool hasSubranges(search_range s);
   extern search_range deepCopy(search_range src);
   extern void deepFree(search_range s);

   #ifdef search_range_cc
      extern search_range search_rangeNew(int begin,
                                          int end);
      extern search_range copy(search_range src,
                               size_t level);
      extern void dump(text Offset,
                       search_range s,
                       FILE* fp,
                       bool showEmpty);
      extern void Free(search_range s,
                       size_t level);

   #else
      extern search_range search_rangeNew(int begin = 0,
                                          int end = 0);
      extern search_range copy(search_range src,
                               size_t level = 0);
      extern void dump(text Offset,
                       search_range s,
                       FILE* fp = stdout,
                       bool showEmpty = false);
      extern void Free(search_range s,
                       size_t level = 0);

   #endif
// End External Functions
#endif
