/* Copyright (C) 2002, 2003, 2004, 2005 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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

#include <stdint.h>
#include <sysdep.h>


typedef int8_t atomic8_t;
typedef uint8_t uatomic8_t;
typedef int_fast8_t atomic_fast8_t;
typedef uint_fast8_t uatomic_fast8_t;

typedef int32_t atomic32_t;
typedef uint32_t uatomic32_t;
typedef int_fast32_t atomic_fast32_t;
typedef uint_fast32_t uatomic_fast32_t;

typedef intptr_t atomicptr_t;
typedef uintptr_t uatomicptr_t;
typedef intmax_t atomic_max_t;
typedef uintmax_t uatomic_max_t;

//void __microblaze_link_error (void);

/* REVISIT: This is not atomic, we need to use a swap instruction */
#define atomic_exchange_acq(mem, newvalue)          \
   ({ __typeof (*mem) result;                       \
      result = *mem;                                \
      *mem = newvalue;                              \
      result; })

/* Atomic compare and exchange.  These sequences are not actually atomic;
   there is a race if *MEM != OLDVAL and we are preempted between the two
   swaps.  */

#define __arch_compare_and_exchange_val_8_acq(mem, newval, oldval) 	\
   ({ __typeof (*mem) archmem = (*mem);           \
      __typeof (oldval) archold = (oldval);       \
      if (archmem == oldval) *mem = newval;       \
      archold; })

#define __arch_compare_and_exchange_val_16_acq(mem, newval, oldval)     \
  (abort (), (__typeof (*mem)) 0)

/* REVISIT : This is not atomic */
#define __arch_compare_and_exchange_val_32_acq(mem, newval, oldval)	\
   ({ __typeof (*mem) archmem = (*mem);           \
      __typeof (oldval) archold = (oldval);       \
      if (archmem == oldval) *mem = newval;       \
      archold; })

#define __arch_compare_and_exchange_val_64_acq(mem, newval, oldval) \
  (abort (), (__typeof (*mem)) 0)
