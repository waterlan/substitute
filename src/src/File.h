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

#ifndef File_INCLUDED
#define File_INCLUDED

// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions
   extern rwtext getBuffer(text filename);
   extern text getBackupFile(text newFile);
   extern bool sysExistsFile(text filename);
   extern bool isRegFile(text filename);
   extern void write(text buffer, text outfile, bool diff);
// End External Functions
#endif
