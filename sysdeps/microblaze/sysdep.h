/* Assembler macros for microblaze.

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

#include <sysdeps/generic/sysdep.h>

#ifdef __ASSEMBLER__

/* Syntactic details of assembler.  */

# ifdef HAVE_ELF

/* ELF uses byte-counts for .align, most others use log2 of count of bytes.  */
#  define ALIGNARG(log2) 1<<log2
/* For ELF we need the `.type' directive to make shared libs work right.  */
#  define ASM_TYPE_DIRECTIVE(name,typearg) .type name,typearg
#  define ASM_SIZE_DIRECTIVE(name) .size name,.-name

/* In ELF C symbols are asm symbols.  */
#  undef NO_UNDERSCORES
#  define NO_UNDERSCORES

# else

#  define ALIGNARG(log2) log2
#  define ASM_TYPE_DIRECTIVE(name,type)	/* Nothing is specified.  */
#  define ASM_SIZE_DIRECTIVE(name)	/* Nothing is specified.  */

# endif


/* Define an entry point visible from C.

   There is currently a bug in gdb which prevents us from specifying
   incomplete stabs information.  Fake some entries here which specify
   the current source file.  */
# define ENTRY(name)							      \
  .globl C_SYMBOL_NAME(name);						      \
  ASM_TYPE_DIRECTIVE (C_SYMBOL_NAME(name),@function);			      \
  .align ALIGNARG(2);							      \
  C_LABEL(name)								      \
  CALL_MCOUNT

# undef END
# define END(name) ASM_SIZE_DIRECTIVE(name)


/* If compiled for profiling, call `_mcount' at the start of each function.  */
# ifdef	PROF
/* The mcount code relies on a normal frame pointer being on the stack
   to locate our caller, so push one just for its benefit.  */
#  define CALL_MCOUNT \
  addik r1,r1,-4;	\
  swi r15,r1,0;		\
  brlid r15,JUMPTARGET(mcount); \
  nop;			\
  lwi r15,r1,0;		\
  addik r1,r1,4;
# else
#  define CALL_MCOUNT		/* Do nothing.  */
# endif

# ifdef	NO_UNDERSCORES
/* Since C identifiers are not normally prefixed with an underscore
   on this system, the asm identifier `syscall_error' intrudes on the
   C name space.  Make sure we use an innocuous name.  */
#  define syscall_error	__syscall_error
#  define mcount	_mcount
# endif

# define PSEUDO(name, syscall_name, args)				      \
  .globl syscall_error;							      \
  ENTRY (name)								      \
    DO_CALL (syscall_name, args);					      \
    /* jcc JUMPTARGET(syscall_error) FIXME */

# define ret \
  rtsd r15,8; nop;

# undef PSEUDO_END
# define PSEUDO_END(name)						      \
  END (name)

# undef JUMPTARGET
# ifdef PIC
#  define JUMPTARGET(name)	name##@PLTPC
# else
#  define JUMPTARGET(name)	name
# endif

/* Assembler local label name */
#define L(name) $L##name

#define MICROBLAZE_HIDDEN_DEF_REAL(x) \
hidden_def(x)

#define MICROBLAZE_HIDDEN_DEF(x) MICROBLAZE_HIDDEN_DEF_REAL(C_SYMBOL_NAME(x))

#endif	/* __ASSEMBLER__ */
