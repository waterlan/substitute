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

#ifndef std_macro_INCLUDED
#define std_macro_INCLUDED



#ifndef NO_C3PO_OPERATORS

#ifndef NO_C3PO_EQ
#define    eq      ==              /* Logical 'equals'                        */
#endif

#ifndef NO_C3PO_NE
#define    ne      !=              /* Logical inequality                      */
#endif

#ifdef NEED_C3PO_NOT
#define    not      !              /* Logical 'NOT'                           */
#endif

#ifndef NO_C3PO_BNOT
#define    bnot      ~              /* Bitwise 'NOT'  (one's complement)       */
#endif

#ifndef NO_C3PO_CAND
#define    cand      &&              /* Conditional 'AND'                       */
#endif

#ifdef NEED_C3PO_AND
#define    and      &&              /* Logical 'AND'                           */
#endif

#ifndef NO_C3PO_BAND
#define    band      &              /* Bitwise 'AND'                           */
#endif

#ifndef NO_C3PO_COR
#define    cor      ||              /* Conditional 'OR'                        */
#endif

#ifdef NEED_C3PO_OR
#define    or      ||              /* Logical 'OR'                            */
#endif

#ifndef NO_C3PO_BOR
#define    bor      |              /* Bitwise 'OR'                            */
#endif

#ifndef NO_C3PO_BXOR
#define    bxor      ^              /* Bitwise exclusive 'OR'                  */
#endif

#ifndef NO_C3PO_MOD
#define    mod      %              /* Remainder operator                      */
#endif

#endif // NO_C3PO_OPERATORS

#ifndef NULL
#define    NULL      0              /* Null pointer                            */
#endif

#ifndef EOF
#define    EOF      -1              /* end of file                             */
#endif

#ifdef PSEUDO_BOOL

#ifdef HAS_FUTURE_RESERVED_BOOL
#define bool c3po_bool
#endif

typedef    int bool;                /* pseudo boolean                         */

#ifndef true
#define    true      1              /* pseudo boolean true value */
#endif

#ifndef false
#define    false      0              /* pseudo boolean false value */
#endif

#endif // PSEUDO_BOOL

#define    expvar                   /* export variable                        */
#define    expfun                   /* export function                        */

#ifdef SETTRACE
#define TRACE(x) x
#else
#define TRACE(x)
#endif

#endif
