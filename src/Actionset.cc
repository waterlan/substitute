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

#include "structures.h"
#include "std_macro.h"

#include "text.h"
#include "Command.h"
#include "action.h"
#include "actionset.h" 
#include "arithmetic.h" 

static text correct(text pattern)
{
   int undefined = 0;
   size_t length = strlen(pattern);
   size_t index;
   rwtext new_pattern = rwtextNew(length + 1);
   size_t new_index = 0;
   for (index = 0; index < limitNeg(length - 1); index = index + 1)
   {
      if ( pattern[index] == '\\' )
      {
         switch(pattern[index + 1])
         {
            case  't' :  new_pattern[new_index] = '\t';
                         break;

            case  'n' :   new_pattern[new_index] = '\n';
                          break;

            default   :   undefined = 1;
                          break;
         }
         if (undefined == 0)
            index = index + 1;
         else
            new_pattern[new_index] = pattern[index];
      }
      else
         new_pattern[new_index] = pattern[index];
      new_index = new_index + 1;
   }     
   if (index == length - 1)
   {
      new_pattern[new_index] = pattern[index];
      new_index = new_index + 1;
   }
   new_pattern[new_index] = '\0';

   return new_pattern;
}

expfun actionset getActions(int argc, char **argv)
{
   action a;
   actionset actions = actionsetNew();
   int index;
   int beginFiles = getBeginFileList(argc, argv); 

   if (argc > 1)
   {  
      int firstForIndex = Index("for", argc, argv);
      // before first for there is room for options...

      index = firstForIndex - 1;
      if (index > 0)
      {
         while(index < beginFiles - 2)
         {
            if (Eq(argv[index + 1], "for"))
            {   
               a = actionNew(correct(argv[index+2]), correct(argv[index]));
               add(a, actions);
            }
            else
               fprintf(stderr, "syntax error near : %s %s %s, (ignored) \n", 
                                argv[index], argv[index + 1], argv[index + 2]);

            index = index + 3;
         }
      }
      else                                                                                                
         fprintf(stderr, "syntax error near begin, missing 'for', or first argument before 'for'\n"); 
   }
          
   return actions;
}      
      
