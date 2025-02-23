/* Copyright (C) 2011 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@gmail.com>, 2011.

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


/*
 * wrapper exp10f(x)
 */

#include <math.h>
#include <math_private.h>

float
__exp10f (float x)
{
  float z = __ieee754_exp10f (x);
  if (__builtin_expect (!__finitef (z), 0)
      && __finitef (x) && _LIB_VERSION != _IEEE_)
	    /* exp10f overflow (146) if x > 0, underflow (147) if x < 0.  */
    return __kernel_standard_f (x, x, 146 + !!__signbitf (x));

	return z;
}
weak_alias (__exp10f, exp10f)
strong_alias (__exp10f, __pow10f)
weak_alias (__pow10f, pow10f)
