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

#ifndef structures_INCLUDED
#define structures_INCLUDED

#include <stdlib.h>

#ifndef C3PO_BASIC_TYPES_INCLUDED
#define C3PO_BASIC_TYPES_INCLUDED

   typedef       char* rwtext;
   typedef const char* text;

   typedef struct nameset_struct
   {
      text *array;
      size_t size;
   } nameset_struct, *nameset;

   typedef struct intset_struct
   {
      int *array;
      size_t size;
   } intset_struct, *intset;

   typedef struct intsets_struct
   {
      intset *array;
      size_t size;
   } intsets_struct, *intsets;

   typedef struct objset_struct
   {
      void **array;
      size_t size;
   } objset_struct, *objset;

#endif


   typedef struct search_rangeset_struct
   {
      struct search_range_struct **array; /* forward reference to array of search_ranges due to recursion... */
      size_t size;
   } search_rangeset_struct, *search_rangeset;

   typedef struct search_range_struct
   {
      int begin;
      int end;
      search_rangeset subranges;
   } search_range_struct, *search_range;

   typedef struct search_match_struct
   {
      text pattern;
      int flags;
      bool valid;
      search_rangeset ranges;
   } search_match_struct, *search_match;

   typedef struct action_struct
   {
      text matchPat;
      text replacePat;
   } action_struct, *action;

   typedef struct actionset_struct
   {
      action *array;
      size_t size;
   } actionset_struct, *actionset;

#endif
