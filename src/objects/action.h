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

#ifndef action_INCLUDED
#define action_INCLUDED



// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern bool eqSelfMatchPat(text matchPat,
                              action a);
   extern bool eqMatchPat(text matchPat,
                          action a);
   extern bool eqSelfReplacePat(text replacePat,
                                action a);
   extern bool eqReplacePat(text replacePat,
                            action a);
   extern bool eqSelf(action a,
                      action b);
   extern bool Eq(action a,
                  action b);
   extern text getMatchPat(action a);
   extern text getReplacePat(action a);
   extern action setMatchPat(text matchPat,
                             action a);
   extern action setReplacePat(text replacePat,
                               action a);
   extern bool hasMatchPat(action a);
   extern bool hasReplacePat(action a);
   extern action deepCopy(action src);
   extern void deepFree(action a);

   #ifdef action_cc
      extern action actionNew(text matchPat,
                              text replacePat);
      extern action copy(action src,
                         size_t level);
      extern void dump(text Offset,
                       action a,
                       FILE* fp,
                       bool showEmpty);
      extern void Free(action a,
                       size_t level);

   #else
      extern action actionNew(text matchPat = NULL,
                              text replacePat = NULL);
      extern action copy(action src,
                         size_t level = 0);
      extern void dump(text Offset,
                       action a,
                       FILE* fp = stdout,
                       bool showEmpty = false);
      extern void Free(action a,
                       size_t level = 0);

   #endif
// End External Functions
#endif
