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

#define arithmetic_cc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"



expfun size_t limitMax(size_t value,
                       size_t resetVal = 0)
{
   if (value eq (size_t) -1)
      return resetVal;
   else
      return value;
}
expfun size_t limitNeg(size_t value,
                       size_t resetVal = 0)
{
   if ((ssize_t) value < 0)
      return resetVal;
   else
      return value;
}
expfun size_t limitNeg(ssize_t value,
                       size_t resetVal = 0)
{
   if (value < 0)
      return resetVal;
   else
      return (size_t) value;
}
