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

#include <fenv.h>
#include <math.h>
#include <math_private.h>


/* wrapper j0l */
long double
__j0l (long double x)
{
  if (__builtin_expect (fabsl (x) > X_TLOSS, 0) && _LIB_VERSION != _IEEE_)
    /* j0(|x|>X_TLOSS) */
    return __kernel_standard (x, x, 234);

	return __ieee754_j0l(x);
}
weak_alias (__j0l, j0l)


/* wrapper y0l */
long double
__y0l (long double x)
{
  if (__builtin_expect (x <= 0.0L || x > X_TLOSS, 0) && _LIB_VERSION != _IEEE_)
    {
      if (x < 0.0L)
	{
	  /* d = zero/(x-x) */
	  feraiseexcept (FE_INVALID);
                    return __kernel_standard(x,x,209);
        }
      else if (x == 0.0L)
	/* d = -one/(x-x) */
	return __kernel_standard (x, x, 208);
      else
	/* y0(x>X_TLOSS) */
	return __kernel_standard (x, x, 235);
}

  return __ieee754_y0l (x);
}
weak_alias (__y0l, y0l)
