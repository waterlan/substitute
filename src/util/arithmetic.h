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

#ifndef arithmetic_INCLUDED
#define arithmetic_INCLUDED




// Extra Forward Declarations
// End Extra Forward Declarations

// External Functions

   #ifdef arithmetic_cc
      extern size_t limitMax(size_t value,
                             size_t resetVal);
      extern size_t limitNeg(size_t value,
                             size_t resetVal);
      extern size_t limitNeg(ssize_t value,
                             size_t resetVal);

   #else
      extern size_t limitMax(size_t value,
                             size_t resetVal = 0);
      extern size_t limitNeg(size_t value,
                             size_t resetVal = 0);
      extern size_t limitNeg(ssize_t value,
                             size_t resetVal = 0);

   #endif
// End External Functions
#endif
