/* w_lgammaf_r.c -- float version of w_lgamma_r.c.
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
 * wrapper float lgammaf_r(float x, int *signgamp)
 */

#include <math.h>
#include <math_private.h>


float
__lgammaf_r(float x, int *signgamp)
{
	float y = __ieee754_lgammaf_r(x,signgamp);
	if(__builtin_expect(!__finitef(y), 0)
	   && __finitef(x) && _LIB_VERSION != _IEEE_)
		return __kernel_standard_f(x, x,
					   __floorf(x)==x&&x<=0.0f
					   ? 115 /* lgamma pole */
					   : 114); /* lgamma overflow */

            return y;
}             
weak_alias (__lgammaf_r, lgammaf_r)
