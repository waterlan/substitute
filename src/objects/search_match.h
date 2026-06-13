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

#ifndef search_match_INCLUDED
#define search_match_INCLUDED



// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern bool eqSelfPattern(text pattern,
                             search_match s);
   extern bool eqPattern(text pattern,
                         search_match s);
   extern bool eqFlags(int flags,
                       search_match s);
   extern bool eqValid(bool validIn,
                       search_match s);
   extern bool eqSelfRanges(search_rangeset ranges,
                            search_match s);
   extern bool eqRanges(search_rangeset ranges,
                        search_match s);
   extern bool eqSelf(search_match a,
                      search_match b);
   extern bool Eq(search_match a,
                  search_match b);
   extern text getPattern(search_match s);
   extern int getFlags(search_match s);
   extern bool valid(search_match s);
   extern search_rangeset getRanges(search_match s);
   extern search_match setPattern(text pattern,
                                  search_match s);
   extern search_match setFlags(int flags,
                                search_match s);
   extern search_match setValid(bool valid,
                                search_match s);
   extern search_match setRanges(search_rangeset ranges,
                                 search_match s);
   extern bool hasPattern(search_match s);
   extern bool hasRanges(search_match s);
   extern search_match deepCopy(search_match src);
   extern void deepFree(search_match s);

   #ifdef search_match_cc
      extern search_match search_matchNew(text pattern,
                                          int flags);
      extern search_match copy(search_match src,
                               size_t level);
      extern void dump(text Offset,
                       search_match s,
                       FILE* fp,
                       bool showEmpty);
      extern void Free(search_match s,
                       size_t level);

   #else
      extern search_match search_matchNew(text pattern = NULL,
                                          int flags = 0);
      extern search_match copy(search_match src,
                               size_t level = 0);
      extern void dump(text Offset,
                       search_match s,
                       FILE* fp = stdout,
                       bool showEmpty = false);
      extern void Free(search_match s,
                       size_t level = 0);

   #endif
// End External Functions
#endif
