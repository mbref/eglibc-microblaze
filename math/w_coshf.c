/* w_coshf.c -- float version of w_cosh.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 * Optimizations by Ulrich Drepper <drepper@gmail.com>, 2011.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/* 
 * wrapper coshf(x)
 */

#include <math.h>
#include <math_private.h>

float
__coshf (float x)
{
	float z = __ieee754_coshf (x);
	if (__builtin_expect (!__finitef (z), 0) && __finitef (x)
	    && _LIB_VERSION != _IEEE_)
		return __kernel_standard_f (x, x, 105); /* cosh overflow */

	    return z;
}
weak_alias (__coshf, coshf)
