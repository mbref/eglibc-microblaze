/*
 * IBM Accurate Mathematical Library
 * Written by International Business Machines Corp.
 * Copyright (C) 2001, 2011 Free Software Foundation, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/******************************************************************/
/*                                                                */
/* MODULE_NAME:mpatan.h                                           */
/*                                                                */
/* common data and variables prototype and definition             */
/******************************************************************/

#ifndef MPATAN_H
#define MPATAN_H

extern const number __atan_xm[8] attribute_hidden;
extern const number __atan_twonm1[33] attribute_hidden;
extern const number __atan_twom[8] attribute_hidden;
extern const number __atan_one attribute_hidden;
extern const number __atan_two attribute_hidden;
extern const int __atan_np[33] attribute_hidden;


#ifndef AVOID_MPATAN_H
#ifdef BIG_ENDI
  const number
	    __atan_xm[8] = {                         /* x[m]   */
/**/                  {{0x00000000, 0x00000000} }, /* 0.0    */
/**/                  {{0x3f8930be, 0x00000000} }, /* 0.0123 */
/**/                  {{0x3f991687, 0x00000000} }, /* 0.0245 */
/**/                  {{0x3fa923a2, 0x00000000} }, /* 0.0491 */
/**/                  {{0x3fb930be, 0x00000000} }, /* 0.0984 */
/**/                  {{0x3fc95810, 0x00000000} }, /* 0.198  */
/**/                  {{0x3fda7ef9, 0x00000000} }, /* 0.414  */
/**/                  {{0x3ff00000, 0x00000000} }, /* 1.0    */
                    };
  const number
 __atan_twonm1[33] = {                             /* 2n-1   */
/**/                  {{0x00000000, 0x00000000} }, /* 0      */
/**/                  {{0x00000000, 0x00000000} }, /* 0      */
/**/                  {{0x00000000, 0x00000000} }, /* 0      */
/**/                  {{0x00000000, 0x00000000} }, /* 0      */
/**/                  {{0x40260000, 0x00000000} }, /* 11     */
/**/                  {{0x402e0000, 0x00000000} }, /* 15     */
/**/                  {{0x40330000, 0x00000000} }, /* 19     */
/**/                  {{0x40350000, 0x00000000} }, /* 21     */
/**/                  {{0x40390000, 0x00000000} }, /* 25     */
/**/                  {{0x403d0000, 0x00000000} }, /* 29     */
/**/                  {{0x40408000, 0x00000000} }, /* 33     */
/**/                  {{0x40428000, 0x00000000} }, /* 37     */
/**/                  {{0x40448000, 0x00000000} }, /* 41     */
/**/                  {{0x40468000, 0x00000000} }, /* 45     */
/**/                  {{0x40488000, 0x00000000} }, /* 49     */
/**/                  {{0x404a8000, 0x00000000} }, /* 53     */
/**/                  {{0x404b8000, 0x00000000} }, /* 55     */
/**/                  {{0x404d8000, 0x00000000} }, /* 59     */
/**/                  {{0x404f8000, 0x00000000} }, /* 63     */
/**/                  {{0x4050c000, 0x00000000} }, /* 67     */
/**/                  {{0x4051c000, 0x00000000} }, /* 71     */
/**/                  {{0x4052c000, 0x00000000} }, /* 75     */
/**/                  {{0x4053c000, 0x00000000} }, /* 79     */
/**/                  {{0x4054c000, 0x00000000} }, /* 83     */
/**/                  {{0x40554000, 0x00000000} }, /* 85     */
/**/                  {{0x40564000, 0x00000000} }, /* 89     */
/**/                  {{0x40574000, 0x00000000} }, /* 93     */
/**/                  {{0x40584000, 0x00000000} }, /* 97     */
/**/                  {{0x40594000, 0x00000000} }, /* 101    */
/**/                  {{0x405a4000, 0x00000000} }, /* 105    */
/**/                  {{0x405b4000, 0x00000000} }, /* 109    */
/**/                  {{0x405c4000, 0x00000000} }, /* 113    */
/**/                  {{0x405d4000, 0x00000000} }, /* 117    */
                    };

  const number
    __atan_twom[8] = {                             /* 2**m   */
/**/                  {{0x3ff00000, 0x00000000} }, /*   1.0  */
/**/                  {{0x40000000, 0x00000000} }, /*   2.0  */
/**/                  {{0x40100000, 0x00000000} }, /*   4.0  */
/**/                  {{0x40200000, 0x00000000} }, /*   8.0  */
/**/                  {{0x40300000, 0x00000000} }, /*  16.0  */
/**/                  {{0x40400000, 0x00000000} }, /*  32.0  */
/**/                  {{0x40500000, 0x00000000} }, /*  64.0  */
/**/                  {{0x40600000, 0x00000000} }, /* 128.0  */
                    };

  const number
/**/ __atan_one     = {{0x3ff00000, 0x00000000} }, /* 1      */
/**/ __atan_two     = {{0x40000000, 0x00000000} }; /* 2      */

#else
#ifdef LITTLE_ENDI

  const number
      __atan_xm[8] = {                             /* x[m]   */
/**/                  {{0x00000000, 0x00000000} }, /* 0.0    */
/**/                  {{0x00000000, 0x3f8930be} }, /* 0.0123 */
/**/                  {{0x00000000, 0x3f991687} }, /* 0.0245 */
/**/                  {{0x00000000, 0x3fa923a2} }, /* 0.0491 */
/**/                  {{0x00000000, 0x3fb930be} }, /* 0.0984 */
/**/                  {{0x00000000, 0x3fc95810} }, /* 0.198  */
/**/                  {{0x00000000, 0x3fda7ef9} }, /* 0.414  */
/**/                  {{0x00000000, 0x3ff00000} }, /* 1.0    */
                    };
  const number
__atan_twonm1[33] = {                             /* 2n-1   */
/**/                  {{0x00000000, 0x00000000} }, /* 0      */
/**/                  {{0x00000000, 0x00000000} }, /* 0      */
/**/                  {{0x00000000, 0x00000000} }, /* 0      */
/**/                  {{0x00000000, 0x00000000} }, /* 0      */
/**/                  {{0x00000000, 0x40260000} }, /* 11     */
/**/                  {{0x00000000, 0x402e0000} }, /* 15     */
/**/                  {{0x00000000, 0x40330000} }, /* 19     */
/**/                  {{0x00000000, 0x40350000} }, /* 21     */
/**/                  {{0x00000000, 0x40390000} }, /* 25     */
/**/                  {{0x00000000, 0x403d0000} }, /* 29     */
/**/                  {{0x00000000, 0x40408000} }, /* 33     */
/**/                  {{0x00000000, 0x40428000} }, /* 37     */
/**/                  {{0x00000000, 0x40448000} }, /* 41     */
/**/                  {{0x00000000, 0x40468000} }, /* 45     */
/**/                  {{0x00000000, 0x40488000} }, /* 49     */
/**/                  {{0x00000000, 0x404a8000} }, /* 53     */
/**/                  {{0x00000000, 0x404b8000} }, /* 55     */
/**/                  {{0x00000000, 0x404d8000} }, /* 59     */
/**/                  {{0x00000000, 0x404f8000} }, /* 63     */
/**/                  {{0x00000000, 0x4050c000} }, /* 67     */
/**/                  {{0x00000000, 0x4051c000} }, /* 71     */
/**/                  {{0x00000000, 0x4052c000} }, /* 75     */
/**/                  {{0x00000000, 0x4053c000} }, /* 79     */
/**/                  {{0x00000000, 0x4054c000} }, /* 83     */
/**/                  {{0x00000000, 0x40554000} }, /* 85     */
/**/                  {{0x00000000, 0x40564000} }, /* 89     */
/**/                  {{0x00000000, 0x40574000} }, /* 93     */
/**/                  {{0x00000000, 0x40584000} }, /* 97     */
/**/                  {{0x00000000, 0x40594000} }, /* 101    */
/**/                  {{0x00000000, 0x405a4000} }, /* 105    */
/**/                  {{0x00000000, 0x405b4000} }, /* 109    */
/**/                  {{0x00000000, 0x405c4000} }, /* 113    */
/**/                  {{0x00000000, 0x405d4000} }, /* 117    */
                    };

  const number
    __atan_twom[8] = {                             /* 2**m   */
/**/                  {{0x00000000, 0x3ff00000} }, /*   1.0  */
/**/                  {{0x00000000, 0x40000000} }, /*   2.0  */
/**/                  {{0x00000000, 0x40100000} }, /*   4.0  */
/**/                  {{0x00000000, 0x40200000} }, /*   8.0  */
/**/                  {{0x00000000, 0x40300000} }, /*  16.0  */
/**/                  {{0x00000000, 0x40400000} }, /*  32.0  */
/**/                  {{0x00000000, 0x40500000} }, /*  64.0  */
/**/                  {{0x00000000, 0x40600000} }, /* 128.0  */
                    };

  const number
/**/ __atan_one    = {{0x00000000, 0x3ff00000} }, /* 1      */
/**/ __atan_two    = {{0x00000000, 0x40000000} }; /* 2      */

#endif
#endif

  const int
    __atan_np[33] = { 0, 0, 0, 0, 6, 8,10,11,13,15,17,19,21,23,25,27,28,
	       30,32,34,36,38,40,42,43,45,47,49,51,53,55,57,59};

#endif
#endif

#define  ONE       __atan_one.d
#define  TWO       __atan_two.d
