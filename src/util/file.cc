// Copyright (C) 1994-2006 Ondrej Popp
// Copyright (C) 2003-2011 Erwin Waterlander
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

#define file_cc

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "std_macro.h"
#include "structures.h"

#include "error.h"
#include "Constants.h"


expfun text getBasename(text filename)
{
   static char base[200];
   ssize_t i;
   strcpy(base, filename);
   i = (ssize_t) strlen(base) - 1;
   while(i >= 0)
   {
      if (base[i] eq '/')
         return base + i + 1;
      i = i - 1;
   }
   return base;
}
expfun text stripSuffix(text filename)
{
   static char core[200];
   ssize_t i;
   strcpy(core, getBasename(filename));
   i = (ssize_t) strlen(core) - 1;
   while(i >= 0)
   {
      if (core[i] eq '.')
         core[i] = '\0';
      i = i - 1;
   }
   return core;
}
expfun FILE * openR(text filename,
                    bool Warn = true)
{
   FILE *fi = fopen(filename, "r");
   if ((fi == NULL) && Warn)
      fprintf(getErrorStream(), "\n** WARNING : couldn't open '%s', (ignored) ...\n", filename);

   return fi;
}
expfun bool existsFile(text filename)
{
   FILE *fp = openR(filename, false);
   if (fp != NULL)
   {
      fclose(fp);
      return true;
   }
   else
      return false;
}
expfun FILE * openW(text filename,
                    bool Backup = false)
{
   size_t index;
   char moveName[STRING_SIZE];
   FILE *fo;
   char *errstr;

   if (existsFile(filename) &&
       Backup)
   {
      sprintf(moveName, "%s.tmp", filename);
      index = 1;
      while(existsFile(moveName))
      {
         sprintf(moveName, "%s.tmp%zu", filename, index);
         index = index + 1;
      }

      if (rename(filename, moveName) == -1)
      {
	  errstr = strerror(errno);
	  fprintf(stderr, "****** Substitute : problems renaming %s to %s: %s\n", filename, moveName, errstr);
      }
      else
          fprintf(getLogStream(), "\n- existing file '%s' has been moved to '%s',", filename, moveName);
   }

   fo = fopen(filename, "w");
   if (fo != NULL)
      fprintf(getLogStream(), "\n- generating '%s'\n", filename);
   else
   {
      errstr = strerror(errno);
      fprintf(getErrorStream(), "\n- couldn't open '%s' for write: %s\n", filename, errstr);
      fprintf(getErrorStream(), "- using stdout...\n");
      fo = stdout;
   }

   return fo;
}
expfun FILE * openA(text filename)
{
   FILE *fo = fopen(filename, "a");
   if (fo != NULL)
      fprintf(getLogStream(), "\n- appending to '%s'\n", filename);
   else
   {
      fprintf(getErrorStream(), "\n- couldn't open '%s', using stdout...\n", filename);
      fo = stdout;
   }

   return fo;
}
expfun bool isOpen(FILE* fp)
{
   if ((fp != NULL) &&
       (fp != stdout) &&
       (fp != stderr))
      return true;
   else
      return false;
}
expfun void Close(FILE* fp)
{
   if (isOpen(fp))
      fclose(fp);
}
expfun unsigned long getFileSize(text filename)
{
   struct stat s;
   if (stat(filename, &s) == 0)
      return (unsigned long) s.st_size;
   else
      return 0;
}
