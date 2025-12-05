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

#define File_cc

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
 
#include "structures.h"
#include "std_macro.h"

#include "Constants.h"

#include "text.h"
#include "file.h"

expfun rwtext getBuffer(text filename)
{
   FILE *fi = openR(filename);
   char c;
   if (fi ne NULL)
   {
      rwtext buffer = rwtextNew(getFileSize(filename) + 1);
      int pos = 0;
      fscanf(fi, "%c", &c);
      while(feof(fi) eq 0) 
      {
         buffer[pos++] = c;
         fscanf(fi, "%c", &c);
      }
      Close(fi);
      buffer[pos] = '\0';
      return buffer;
   }

   return NULL;
}

expfun text getBackupFile(text newFile)
{
   int index;
   static char moveName[STRING_SIZE];

   if (existsFile(newFile))
   {
      sprintf(moveName, "%s.tmp", newFile);
      index = 1;
      while(existsFile(moveName))
      {
         sprintf(moveName, "%s.tmp%d", newFile, index);
         index = index + 1;
      }

      return moveName;
   }
   else
      return NULL;
}

expfun bool sysExistsFile(text filename)
{
    struct stat s;
    char *errstr;

    if (stat(filename, &s) == 0)
      return true;
    else
    {
        errstr = strerror(errno);
        fprintf(stderr, "****** Substitute : %s: %s\n", filename, errstr);
    }

    return false;
} 

expfun bool isRegFile(text filename)
{
    struct stat s;
    char *errstr;

    if (stat(filename, &s) == 0)
    {
        if (S_ISREG(s.st_mode))
            return true;
        else
            return false;
    }
    else
    {
        errstr = strerror(errno);
        fprintf(stderr, "****** Substitute : %s: %s\n", filename, errstr);
    }
    return false;
} 

static void doDiff(text oldFile, text newFile)
{
   char buffer[STRING_SIZE];
   sprintf(buffer, "diff %s %s", oldFile, newFile);
   system(buffer);
}

expfun void write(text buffer, text outfile, bool diff)
{
   FILE *fo;

   text backupFile = getBackupFile(outfile);

   fo = openW(outfile, true);
   if (fo ne NULL)
   {
      fprintf(fo, "%s", buffer);
      Close(fo);
   }

   if (diff)
      doDiff(backupFile, outfile);
}   
         
