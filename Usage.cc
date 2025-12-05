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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "std_macro.h"
#include "structures.h"

#include "text.h"
#include "error.h"
#include "Version.h"

expfun void Usage(int argc,
                  char** argv)
{
    beep(1);
    printVersion(argv);

    printf("\n****** usage (substitute) : %s [options] 'replacement1' for 'pattern1' ['replacement..' for 'pattern..'].. in filename_list \n", argv[0]);
    printf("       options,\n");
    printf("       -v    : verbose, report also when nothing is matched\n");
    printf("       -diff : do a diff on modified files\n");
    printf("       -i    : ignore case\n");
}
