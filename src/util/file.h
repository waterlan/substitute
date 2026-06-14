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

#ifndef file_INCLUDED
#define file_INCLUDED




// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern text getBasename(text filename);
   extern text stripSuffix(text filename);
   extern bool existsFile(text filename);
   extern FILE * openA(text filename);
   extern bool isOpen(FILE* fp);
   extern void Close(FILE* fp);
   extern unsigned long getFileSize(text filename);

   #ifdef file_cc
      extern FILE * openR(text filename,
                          bool Warn);
      extern FILE * openW(text filename,
                          bool Backup);

   #else
      extern FILE * openR(text filename,
                          bool Warn = true);
      extern FILE * openW(text filename,
                          bool Backup = false);

   #endif
// End External Functions
#endif
