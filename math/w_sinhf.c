/* w_sinhf.c -- float version of w_sinh.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
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
 * wrapper sinhf(x)
 */

#include <math.h>
#include <math_private.h>

float
__sinhf (float x)
{
	float z = __ieee754_sinhf (x);
	if (__builtin_expect (!__finitef (z), 0) && __finitef (x)
	    && _LIB_VERSION != _IEEE_)
	    return __kernel_standard_f (x, x, 125); /* sinhf overflow */

	    return z;
}
weak_alias (__sinhf, sinhf)
