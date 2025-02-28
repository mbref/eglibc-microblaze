/* The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _SYS_REG_H
#define _SYS_REG_H	1

/* Index into an array of 4 byte integers returned from ptrace for
   location of the users' stored general purpose registers. */

#define PT_D1 0
#define PT_D2 1
#define PT_D3 2
#define PT_D4 3
#define PT_D5 4
#define PT_D6 5
#define PT_D7 6
#define PT_A0 7
#define PT_A1 8
#define PT_A2 9
#define PT_A3 10
#define PT_A4 11
#define PT_A5 12
#define PT_A6 13
#define PT_D0 14
#define PT_USP 15
#define PT_ORIG_D0 16
#define PT_SR 17
#define PT_PC 18
#define PT_FP0 21
#define PT_FP1 24
#define PT_FP2 27
#define PT_FP3 30
#define PT_FP4 33
#define PT_FP5 36
#define PT_FP6 39
#define PT_FP7 42
#define PT_FPCR 45
#define PT_FPSR 46
#define PT_FPIAR 47

#endif	/* _SYS_REG_H */
