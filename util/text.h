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

#ifndef text_INCLUDED
#define text_INCLUDED




// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern rwtext rwtextNew(size_t size);
   extern text textNew(size_t size);
   extern rwtext rwtextNew(text string);
   extern text textNew(text string);
   extern bool Eq(text a,
                  text b);
   extern bool eqSelf(text a,
                      text b);
   extern text concat(text a,
                      text b);
   extern text concat(text a,
                      text b,
                      text c);
   extern text concat(text a,
                      text b,
                      text c,
                      text d);
   extern text toString(int i);
   extern text toString(double d);
   extern text toString(size_t s);
   extern text toString(ssize_t s);

   #ifdef text_cc
      extern text repeat(text pattern,
                         size_t amount,
                         int bufferNr);
      extern text Spaces(size_t amount,
                         int bufferNr);
      extern text Tab(size_t amount,
                      int bufferNr);

   #else
      extern text repeat(text pattern,
                         size_t amount,
                         int bufferNr = -1);
      extern text Spaces(size_t amount,
                         int bufferNr = 0);
      extern text Tab(size_t amount,
                      int bufferNr = 0);

   #endif
// End External Functions
#endif
