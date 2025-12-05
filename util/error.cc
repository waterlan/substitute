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

#define error_cc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"

#include "text.h"


static FILE *LOG_STREAM = stdout;
static FILE *ERR_STREAM = stderr;

expfun void setLogStream(FILE* stream)
{
   LOG_STREAM = stream;
}
expfun FILE * getLogStream(void)
{
   return LOG_STREAM;
}
expfun void setErrorStream(FILE* stream)
{
   ERR_STREAM = stream;
}
expfun FILE * getErrorStream(void)
{
   return ERR_STREAM;
}
expfun void beep(size_t number_times)
{
   size_t counter = 0;
   while (counter < number_times)
   {
      fprintf(stderr, "\007");
      counter = counter + 1;
   }
}
expfun void malloc_error(text function_name)
{
   beep(1);
   perror (concat("error in ", function_name));
   exit(1);
}
