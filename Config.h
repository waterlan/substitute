XCOMM Copyright (C) 1994-2006 Ondrej Popp
XCOMM 
XCOMM This program is free software; you can redistribute it and/or
XCOMM modify it under the terms of the GNU General Public License
XCOMM as published by the Free Software Foundation; either version 2
XCOMM of the License, or (at your option) any later version.
XCOMM 
XCOMM This program is distributed in the hope that it will be useful,
XCOMM but WITHOUT ANY WARRANTY; without even the implied warranty of
XCOMM MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
XCOMM GNU General Public License for more details.
XCOMM 
XCOMM You should have received a copy of the GNU General Public License
XCOMM along with this program; if not, write to the Free Software
XCOMM Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

OBJDIR = .
#define PassCDebugFlags 'CXXDEBUGFLAGS=$(CXXDEBUGFLAGS)'
CXXDEBUGFLAGS = -g

#ifdef HPArchitecture
   CXX_COMMON_OPTIONS = $(TRACE) -z -Wall -Wextra -Wconversion -Wsign-conversion -Werror
#else
#ifdef cygwinArchitecture
   CXX_COMMON_OPTIONS = $(TRACE) -Dcygwin -Wall -Wextra -Wconversion -Wsign-conversion -Werror
#else
   CXX_COMMON_OPTIONS = $(TRACE) -Wall -Wextra -Wconversion -Wsign-conversion -Werror
#endif /* cygwinArchitecture */
#endif /* HPArchitecture */

CXX_TOPLEVEL_OPTIONS = $(CXX_COMMON_OPTIONS) -Wno-unused-parameter

CXX_PARSER_OPTIONS = $(CXX_COMMON_OPTIONS) -Wno-conversion -Wno-sign-conversion -Wno-unused-label -Wno-unused-parameter

CXX_SRC_OPTIONS = $(CXX_COMMON_OPTIONS)

CXX_OBJECT_OPTIONS = $(CXX_COMMON_OPTIONS)

#ifndef LinuxArchitecture
   /*
    * MAKE should be set to gnu-make,
    * it is best to alias or link 'make' to gnu-make
    */

   MAKE = make
#endif

CXX = g++
