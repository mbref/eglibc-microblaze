/* Round long double to integer away from zero.
   Copyright (C) 1997, 2007, 2011 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

   The GNU C Library is free software; you can redistribute it and/or
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

#include <math.h>

#include "math_private.h"


static const long double huge = 1.0e4930L;


long double
__roundl (long double x)
{
  int32_t j0;
  u_int32_t se, i1, i0;

  GET_LDOUBLE_WORDS (se, i0, i1, x);
  j0 = (se & 0x7fff) - 0x3fff;
  if (j0 < 31)
    {
      if (j0 < 0)
	{
	  math_force_eval (huge + x);
	      se &= 0x8000;
	      i0 = i1 = 0;
	      if (j0 == -1)
		{
		  se |= 0x3fff;
		  i0 = 0x80000000;
		}
	    }
      else
	{
	  u_int32_t i = 0x7fffffff >> j0;
	  if (((i0 & i) | i1) == 0)
	    /* X is integral.  */
	    return x;

	      /* Raise inexact if x != 0.  */
	  math_force_eval (huge + x);
	      u_int32_t j = i0 + (0x40000000 >> j0);
	      if (j < i0)
		se += 1;
	      i0 = (j & ~i) | 0x80000000;
	      i1 = 0;
	    }
	}
  else if (j0 > 62)
    {
      if (j0 == 0x4000)
	/* Inf or NaN.  */
	return x + x;
      else
	return x;
    }
  else
    {
      u_int32_t i = 0xffffffff >> (j0 - 31);
      if ((i1 & i) == 0)
	/* X is integral.  */
	return x;

      math_force_eval (huge + x);
	  /* Raise inexact if x != 0.  */
	  u_int32_t j = i1 + (1 << (62 - j0));
	  if (j < i1)
	    {
	      u_int32_t k = i0 + 1;
	      if (k < i0)
		{
		  se += 1;
		  k |= 0x80000000;
		}
	      i0 = k;
	    }
	  i1 = j;
      i1 &= ~i;
    }

  SET_LDOUBLE_WORDS (x, se, i0, i1);
  return x;
}
weak_alias (__roundl, roundl)
