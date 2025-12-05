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

#ifndef command_INCLUDED
#define command_INCLUDED




// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern bool inArgList(text name,
                         int argc,
                         char** argv);
   extern text getArg(text name,
                      int argc,
                      char** argv);
   extern nameset getArgs(text name,
                          int argc,
                          char** argv);
   extern bool isInt(text t);
   extern bool isFloat(text t);
   extern void dumpCommandline(text file,
                               size_t argc,
                               char** argv);

   #ifdef command_cc

   #else

   #endif
// End External Functions
#endif
