/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 *
 * Adapted for `long double' by Ulrich Drepper <drepper@cygnus.com>.
 *
 * Changed to use fyl2xp1 for values near 1, <drepper@cygnus.com>.
 * Adapted for x86-64 by Andreas Jaeger <aj@suse.de>.
 */

#include <machine/asm.h>

#ifdef __ELF__
	.section .rodata.cst8,"aM",@progbits,8
#else
	.text
#endif
	.p2align 3
	ASM_TYPE_DIRECTIVE(one,@object)
one:	.double 1.0
	ASM_SIZE_DIRECTIVE(one)
	/* It is not important that this constant is precise.  It is only
	   a value which is known to be on the safe side for using the
	   fyl2xp1 instruction.  */
	ASM_TYPE_DIRECTIVE(limit,@object)
limit:	.double 0.29
	ASM_SIZE_DIRECTIVE(limit)


#ifdef PIC
#define MO(op) op##(%rip)
#else
#define MO(op) op
#endif

	.text
ENTRY(__ieee754_log10l)
	fldlg2			// log10(2)
	fldt	8(%rsp)		// x : log10(2)
	fxam
	fnstsw
	fld	%st		// x : x : log10(2)
	testb	$1, %ah
	jnz	3f		// in case x is NaN or �Inf
4:	fsubl	MO(one)		// x-1 : x : log10(2)
	fld	%st		// x-1 : x-1 : x : log10(2)
	fabs			// |x-1| : x-1 : x : log10(2)
	fcompl	MO(limit)	// x-1 : x : log10(2)
	fnstsw			// x-1 : x : log10(2)
	andb	$0x45, %ah
	jz	2f
	fstp	%st(1)		// x-1 : log10(2)
	fyl2xp1			// log10(x)
	ret

2:	fstp	%st(0)		// x : log10(2)
	fyl2x			// log10(x)
	ret

3:	testb	$4, %ah
	jnz	4b		// in case x is �Inf
	fstp	%st(1)
	fstp	%st(1)
	ret
END(__ieee754_log10l)


ENTRY(__log10l_finite)
	fldlg2			// log10(2)
	fldt	8(%rsp)		// x : log10(2)
	fld	%st		// x : x : log10(2)
4:	fsubl	MO(one)		// x-1 : x : log10(2)
	fld	%st		// x-1 : x-1 : x : log10(2)
	fabs			// |x-1| : x-1 : x : log10(2)
	fcompl	MO(limit)	// x-1 : x : log10(2)
	fnstsw			// x-1 : x : log10(2)
	andb	$0x45, %ah
	jz	2b
	fstp	%st(1)		// x-1 : log10(2)
	fyl2xp1			// log10(x)
	ret
END(__log10l_finite)
