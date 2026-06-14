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

#include <stdio.h>

#include "structures.h"
#include "std_macro.h"

#include "text.h"

expfun int Index(text arg, int argc, char **argv)
{
   int index = 0;
   while(index < argc)
   {
      if (Eq(argv[index], arg))
        return index; 

      index = index + 1;
   }

   return -1;
}

expfun int getBeginFileList(int argc, char **argv)
{
   return Index("in", argc, argv) + 1;
}

