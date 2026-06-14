// Copyright (C) 1994-2026 Ondrej Popp
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef Search_match_INCLUDED
#define Search_match_INCLUDED
   extern bool isEmpty(search_match s);
   extern int size(search_match s);
   extern void extend_search_match(search_match s, text buffer, int match_offset, bool notify);
   extern search_match getSearchMatch(text buffer, text pattern, int flags, bool notify = false);
   extern search_match getSearchMatch(text buffer, text pattern, bool notify = false);
   extern text substitute(int argc, char **argv, text startBuffer, text fileName);
   extern void substitute(int argc, char **argv);
#endif
