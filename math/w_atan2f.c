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
 * wrapper atan2f(y,x)
 */

#include <math.h>
#include <math_private.h>


float
__atan2f (float y, float x)
{
  if (__builtin_expect (x == 0.0f && y == 0.0f, 0) && _LIB_VERSION == _SVID_)
    return __kernel_standard_f (y, x, 103); /* atan2(+-0,+-0) */

	return __ieee754_atan2f(y,x);
}
weak_alias (__atan2f, atan2f)
