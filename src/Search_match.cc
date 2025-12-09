// Copyright (C) 1994-2006 Ondrej Popp
// Copyright (C) 2012 Erwin Waterlander
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
#include <stdlib.h>
#include <string.h> 
#include <regex.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

#include "std_macro.h"
#include "structures.h"

#include "Constants.h"
                    
#include "text.h"
#include "nameset.h"
#include <command.h>

#include "search_range.h"
#include "search_rangeset.h"
#include <search_match.h>
#include "arithmetic.h"
#include <action.h>
#include "Action.h"
#include <actionset.h>
#include "Actionset.h"
#include "Command.h"
#include "File.h"
#include "file.h"

static int getSearchFlags(bool caseSensitive = true)
{
   if (caseSensitive eq true)
      return REG_EXTENDED|REG_NEWLINE;
   else
      return REG_EXTENDED|REG_NEWLINE|REG_ICASE;
}

expfun bool isEmpty(search_match s)
{
   return isEmpty(getRanges(s));
} 

expfun size_t size(search_match s)
{
   return size(getRanges(s));
} 

expfun void extend_search_match(search_match s, text buffer, regoff_t match_offset, bool verbose)
{  
   int error; 
   char error_msg[STRING_SIZE]; 
   regex_t re; 
   regmatch_t pmatch[STRING_SIZE];
    
   search_range r;   
   regoff_t offset;
   size_t nmatch;  

   size_t index;  
   search_rangeset subranges;
   search_range    sub_r;

   error = regcomp(&re, s->pattern, s->flags);
   if (error ne 0)
   {
      (void) regerror(error,&re, error_msg, sizeof(error_msg));
      fprintf(stderr, "** WARNING : %s\n", error_msg);
   }  
   else
   { 
      offset = 0;     
      if (re.re_nsub < STRING_SIZE)
         nmatch = 1 + re.re_nsub;
      else
         nmatch = STRING_SIZE;

    /*  TRACE(fprintf(stdout, "nmatch %d nsub %d\n", nmatch, re.re_nsub);)  */

      error = regexec(&re, buffer, nmatch, pmatch, 0); 
      while(error eq 0)
      {  
      /*  TRACE(fprintf(stdout, "pmatch[0].rm_so %d\n", pmatch[0].rm_so);) 
          TRACE(fprintf(stdout, "pmatch[0].rm_eo %d\n", pmatch[0].rm_eo);)  */ 

         if (pmatch[0].rm_eo > pmatch[0].rm_so)
         {
            r = search_rangeNew(pmatch[0].rm_so*((regoff_t) sizeof(char)) + match_offset + offset,
                                (pmatch[0].rm_eo - 1)*((regoff_t) sizeof(char)) + match_offset + offset);
             
            if (re.re_nsub > 0)
            {  
               subranges = search_rangesetNew();
               index = 1;
               while(index <= re.re_nsub)
               {
                  if (pmatch[index].rm_eo > pmatch[index].rm_so)
                  {
                     sub_r = search_rangeNew(pmatch[index].rm_so*((regoff_t) sizeof(char)) + match_offset + offset,
                                             (pmatch[index].rm_eo - 1)*((regoff_t) sizeof(char)) + match_offset + offset);
                     add(sub_r, subranges);
                  }
                  else
                     add(NULL, subranges);

            /*      TRACE(fprintf(stdout, "pmatch[%d].rm_so %d\n", index, pmatch[index].rm_so);) 
                  TRACE(fprintf(stdout, "pmatch[%d].rm_eo %d\n", index, pmatch[index].rm_eo);)   */

                  index = index + 1;
               }
               r->subranges = subranges;
            }
   
           /*   TRACE(fprintf(stdout, "r->begin %d r->end %d\n", r->begin, r->end);)  */

            add(r, s->ranges);  
            offset = offset + pmatch[0].rm_eo*((regoff_t) sizeof(char));
            error = regexec(&re, buffer + offset, nmatch, pmatch, 0); 
         }
         else 
            break;
      }

      if (isEmpty(s))
      {
         if (verbose)
            fprintf(stderr, "no match\n");
      }
      else
         fprintf(stderr, "matches : %zu\n", size(s));
   }

   regfree(&re);  
/*   TRACE(fprintf(stdout, "matchcount %d\n", size(getRanges(s));) */
}  

expfun search_match getSearchMatch(text buffer, text pattern, int flags, bool verbose = false)
{  
   search_match s = search_matchNew(textNew(pattern), flags);
   extend_search_match(s, buffer, 0, verbose);
   return s;
}  

expfun search_match getSearchMatch(text buffer, text pattern, bool verbose = false)
{
   return getSearchMatch(buffer, pattern, getSearchFlags(), verbose);
}

static text get_match_pattern(text buffer, search_range r)
{
   static rwtext string = NULL;  

   size_t length = limitNeg((size_t) (getEnd(r) - getBegin(r) + 1));

   if (length > 0)
   {
      if (string eq NULL)
         string = rwtextNew(length + 1);
      else
         string = (rwtext) realloc((void *) string, sizeof(char) * (length + 1));

      strncpy(string, buffer + getBegin(r), length);
      string[length] = '\0';
   }
   return string; 
}

static search_range get_match_range(text replace_pat, search_range r, size_t *operator_length)
{
   static rwtext string = NULL; 
   size_t length = strlen(replace_pat); 

   size_t  index; 
   ssize_t subrange_index;  

   search_rangeset subranges;

   if ((replace_pat[0] eq '$') and (r ne NULL))
   {
      if ((length > 2)  cand (replace_pat[1] eq '\\'))
      {
          if (string eq NULL)
            string = rwtextNew(length + 1);
         else
            string = (rwtext) realloc((void *) string, sizeof(char) * (length + 1));  

         strcpy(string, replace_pat + 2);

         index = 0;
         while(index < strlen(string))
         {
            if(isdigit(string[index]) eq 0)
            {
               string[index] = '\0';
               break;
            }
            index = index + 1;
         }

         if (strlen(string) > 0)
         {    
            subranges = getSubranges(r);
            subrange_index = atoi(string) - 1; 

            *operator_length = 2 + strlen(string);

            return elementAt(subrange_index, subranges);
         }
         else
         {
            *operator_length = 1;
            return r;
         }
      }
      else
      {  
         *operator_length = 1;
         return r;
      }
   }
   else
   {
      *operator_length = 0;
      return NULL;
   }
}

static text reduce_replace_pat(text replace_pat, text buffer, search_range r)
{
   static rwtext string = NULL; 
    
   size_t replace_pat_length = strlen(replace_pat); 
   size_t string_length = replace_pat_length;

   size_t index;
   size_t offset;  

   size_t match_operator_length;

   search_range match_r;  
   text  match_pattern;

   if (string eq NULL)
      string = rwtextNew(string_length + 1);
   else
      string = (rwtext) realloc((void *) string, sizeof(char) * (string_length + 1));

   index = 0; 
   offset = 0;
   while(index < replace_pat_length)
   {
      if (replace_pat[index] eq '$')
      {
         match_r = get_match_range(replace_pat + index, r, &match_operator_length);
         if (match_r ne NULL)
         {
            match_pattern = get_match_pattern(buffer, match_r);
            if (match_pattern ne NULL)
            { 
               TRACE(fprintf(stdout, "match pat '%s'\n", match_pattern);) 
               string_length = string_length + strlen(match_pattern); 
               string = (rwtext) realloc((void *) string, sizeof(char) * (string_length + 1));
               strcpy(string + offset, match_pattern); 
               offset = offset + strlen(match_pattern);
            }
         }
         if (match_operator_length > 1)
            index = index + match_operator_length - 1;
      }
      else
      {
         if ((replace_pat[index] eq '\\') and ((index + 1) < replace_pat_length))
         {
            string[offset] = replace_pat[index + 1];
            index = index + 1;
         }
         else
            string[offset] = replace_pat[index];

         offset = offset + 1;
      }

      index = index + 1; 
   }

   string[offset] = '\0';  

   return string;
}

static rwtext substitute(text pattern, text replacePat, text buffer, int flags, bool verbose = false)
{
   search_match sm = getSearchMatch(buffer, pattern, flags, verbose);
   rwtext resultBuffer;
   text reducedPat;

   if (isEmpty(sm) eq false)
   {  
      search_rangeset set = getRanges(sm);
      search_range    r;
      search_range    prev_r;

      size_t resultLength = strlen(buffer) + strlen(replacePat)*size(set);
      resultBuffer = rwtextNew(resultLength + 1);

      resultBuffer[0] = '\0';
      size_t fillLength = 0;
      size_t subLength;         

      size_t index = 0;
      while(index < size(set))
      {
         r = elementAt(index, set);
         
         if (index > 0)
         {   
            prev_r = elementAt(index - 1, set);
            subLength = limitNeg((size_t) (getBegin(r) - getEnd(prev_r) - 1));
            if (subLength > 0)
            {
               strncpy(resultBuffer + fillLength, buffer + getEnd(prev_r) + 1, subLength);
               fillLength = fillLength + subLength;
            }
         }
         else if (getBegin(r) > 0)
         {
            strncpy(resultBuffer + fillLength, buffer, (size_t) getBegin(r));
            fillLength = fillLength + (size_t) getBegin(r);
         }   
         
         reducedPat = reduce_replace_pat(replacePat, buffer, r);
         subLength = strlen(reducedPat); 
         if (subLength > strlen(replacePat))
         {
            resultLength = resultLength + subLength;
            resultBuffer = (rwtext) realloc((void *) resultBuffer, sizeof(char) * (resultLength + 1));
         }
         strcpy(resultBuffer + fillLength, reducedPat); 
         fillLength = fillLength + subLength;

         index = index + 1;
      }

      if ((size_t) getEnd(r) < strlen(buffer) - 1)
         strcpy(resultBuffer + fillLength, buffer + getEnd(r) + 1);
   }
   else
      resultBuffer = (rwtext) buffer;

   Free(sm);

   return resultBuffer;
}

static void writeSubstCommand(text fileName, action a, FILE *fp)
{
   fprintf(fp, "Substitute : %s for %s in %s\n", getReplacePat(a), getMatchPat(a), fileName);
} 

expfun rwtext substitute(int argc, char **argv, rwtext startBuffer, text fileName)
{
   actionset actions = getActions(argc, argv);
   action a;
   rwtext curBuffer = startBuffer;
   rwtext newBuffer; 

   int flags;
   if (inArgList("-i", argc, argv))
      flags = getSearchFlags(false);
   else
      flags = getSearchFlags(true);

   bool verbose = inArgList("-v", argc, argv);

   size_t index = 0;
   while(index < size(actions))
   {
      a = elementAt(index, actions);
      if (isSubstitute(a))
      {  
         if (verbose)
            writeSubstCommand(fileName, a, stderr);

         newBuffer = substitute(getMatchPat(a), getReplacePat(a), curBuffer, flags, verbose);
         if (newBuffer ne curBuffer)
         {
            if (verbose eq false)
               writeSubstCommand(fileName, a, stderr);

            if (curBuffer ne startBuffer) 
               free((void *) curBuffer);

            curBuffer = newBuffer;
         }
      }

      index = index + 1;
   }

   return curBuffer;
}

#if  defined(__TURBOC__) || defined(__DJGPP__) || defined(__MINGW32__) || defined(__WATCOMC__) || defined(_MSC_VER)
/* Some compilers have no chown(). */
#define NO_CHOWN 1
#endif


expfun void substitute(int argc, char **argv)
{
   int fileIndex = getBeginFileList(argc, argv);
   text fileName;
   rwtext buffer;
   rwtext newBuffer;
   char *errstr;
   struct stat StatBuf;

   while(fileIndex < argc)
   {
      fileName = argv[fileIndex];
      if (sysExistsFile(fileName))
      { 
         if(isRegFile(fileName))
         {
            /* get input file permissions */
            if (stat(fileName, &StatBuf))
            {
                errstr = strerror(errno);
                fprintf(stderr, "%s : %s: %s\n", "****** Substitute", fileName, errstr);
            }
            buffer = getBuffer(fileName);
            newBuffer = substitute(argc, argv, buffer, fileName);
            if (newBuffer ne buffer)
            { 
               write(newBuffer, fileName, inArgList("-diff", argc, argv));
               free((void *) newBuffer);
               /* restore original file permissions */
               if (chmod (fileName, StatBuf.st_mode))
               {
                  errstr = strerror(errno);
                  fprintf(stderr, "%s : failed to restore permissions on %s: %s\n", "****** Substitute", fileName, errstr);
               }
               /* restore original file owner and group */
               /* Required when a different user (e.g. root) has write permission on the original file. */
               /* Make sure that the original owner can still access the file. */
               /* Make sure that others are not able to read the file who could not read the file before. */
#ifndef NO_CHOWN
               if (chown(fileName, StatBuf.st_uid, StatBuf.st_gid))
               {
                    errstr = strerror(errno);
                    fprintf(stderr, "%s : Failed to change the owner and group of output file %s: %s\n", "****** Substitute", fileName, errstr);
               }
#endif
            }
            free((void *) buffer);
         } 
         else
            fprintf(stderr, "****** Substitute : skipped non regular file '%s'\n", fileName);
      }

      fileIndex = fileIndex + 1;
   }
}
 
