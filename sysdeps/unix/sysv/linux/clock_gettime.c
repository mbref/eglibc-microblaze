/* clock_gettime -- Get current time from a POSIX clockid_t.  Linux version.
   Copyright (C) 2003,2004,2005,2006,2007,2010,2011 Free Software Foundation, Inc.
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

#include <sysdep.h>
#include <errno.h>
#include <time.h>
#include "kernel-posix-cpu-timers.h"
#include <kernel-features.h>

#ifndef HAVE_CLOCK_GETTIME_VSYSCALL
# undef INTERNAL_VSYSCALL
# define INTERNAL_VSYSCALL INTERNAL_SYSCALL
# undef INLINE_VSYSCALL
# define INLINE_VSYSCALL INLINE_SYSCALL
#else
# include <bits/libc-vdso.h>
#endif

#ifndef SYSCALL_GETTIME
# define SYSCALL_GETTIME(id, tp) \
  INLINE_VSYSCALL (clock_gettime, 2, id, tp)
#endif
#ifndef INTERNAL_GETTIME
# define INTERNAL_GETTIME(id, tp) \
  INTERNAL_VSYSCALL (clock_gettime, err, 2, id, tp)
#endif

#ifdef __ASSUME_POSIX_TIMERS

/* This means the REALTIME and MONOTONIC clock are definitely
   supported in the kernel.  */
# define SYSDEP_GETTIME							      \
  SYSDEP_GETTIME_CPUTIME;						      \
  case CLOCK_REALTIME:							      \
  case CLOCK_MONOTONIC:							      \
    retval = SYSCALL_GETTIME (clock_id, tp);				      \
    break

# define __libc_missing_posix_timers 0
#elif defined __NR_clock_gettime
/* Is the syscall known to exist?  */
int __libc_missing_posix_timers attribute_hidden;

static inline int
maybe_syscall_gettime (clockid_t clock_id, struct timespec *tp)
{
  int e = EINVAL;

  if (!__libc_missing_posix_timers)
    {
      INTERNAL_SYSCALL_DECL (err);
      int r = INTERNAL_GETTIME (clock_id, tp);
      if (!INTERNAL_SYSCALL_ERROR_P (r, err))
	return 0;

      e = INTERNAL_SYSCALL_ERRNO (r, err);
      if (e == ENOSYS)
	{
	  __libc_missing_posix_timers = 1;
	  e = EINVAL;
	}
    }

  return e;
}

/* The REALTIME and MONOTONIC clock might be available.  Try the
   syscall first.  */
# define SYSDEP_GETTIME							      \
  SYSDEP_GETTIME_CPUTIME;						      \
  case CLOCK_REALTIME:							      \
  case CLOCK_MONOTONIC:							      \
  case CLOCK_MONOTONIC_RAW:						      \
  case CLOCK_REALTIME_COARSE:						      \
  case CLOCK_MONOTONIC_COARSE:						      \
    retval = maybe_syscall_gettime (clock_id, tp);			      \
    if (retval == 0)							      \
      break;								      \
    /* Fallback code.  */						      \
    if (retval == EINVAL && clock_id == CLOCK_REALTIME)			      \
      retval = realtime_gettime (tp);					      \
    else 								      \
      {									      \
	__set_errno (retval);						      \
	retval = -1;							      \
      }									      \
    break
#endif

#ifdef __NR_clock_gettime
/* We handled the REALTIME clock here.  */
# define HANDLED_REALTIME	1
# define HANDLED_CPUTIME	1

# if __ASSUME_POSIX_CPU_TIMERS > 0

#  define SYSDEP_GETTIME_CPU(clock_id, tp) \
  retval = SYSCALL_GETTIME (clock_id, tp); \
  break
#  define SYSDEP_GETTIME_CPUTIME	/* Default catches them too.  */

# else

int __libc_missing_posix_cpu_timers attribute_hidden;

static int
maybe_syscall_gettime_cpu (clockid_t clock_id, struct timespec *tp)
{
  int e = EINVAL;

  if (!__libc_missing_posix_cpu_timers)
    {
      INTERNAL_SYSCALL_DECL (err);
      int r = INTERNAL_GETTIME (clock_id, tp);
      if (!INTERNAL_SYSCALL_ERROR_P (r, err))
	return 0;

      e = INTERNAL_SYSCALL_ERRNO (r, err);
# ifndef __ASSUME_POSIX_TIMERS
      if (e == ENOSYS)
	{
	  __libc_missing_posix_timers = 1;
	  __libc_missing_posix_cpu_timers = 1;
	  e = EINVAL;
	}
      else
# endif
	{
	  if (e == EINVAL)
	    {
# ifdef HAVE_CLOCK_GETRES_VSYSCALL
	      /* Check whether the kernel supports CPU clocks at all.
		 If not, record it for the future.  */
	      r = INTERNAL_VSYSCALL (clock_getres, err, 2,
				     MAKE_PROCESS_CPUCLOCK (0, CPUCLOCK_SCHED),
				     NULL);
# else
	      /* Check whether the kernel supports CPU clocks at all.
		 If not, record it for the future.  */
	      r = INTERNAL_SYSCALL (clock_getres, err, 2,
				    MAKE_PROCESS_CPUCLOCK (0, CPUCLOCK_SCHED),
				    NULL);
# endif
	      if (INTERNAL_SYSCALL_ERROR_P (r, err))
		__libc_missing_posix_cpu_timers = 1;
	    }
	}
    }

  return e;
}

#  define SYSDEP_GETTIME_CPU(clock_id, tp) \
  retval = maybe_syscall_gettime_cpu (clock_id, tp);			      \
  if (retval == 0)							      \
    break;								      \
  if (retval != EINVAL || !__libc_missing_posix_cpu_timers)		      \
    {									      \
      __set_errno (retval);						      \
      retval = -1;							      \
      break;								      \
    }									      \
  retval = -1 /* Otherwise continue on to the HP_TIMING version.  */;

static inline int
maybe_syscall_gettime_cputime (clockid_t clock_id, struct timespec *tp)
{
  return maybe_syscall_gettime_cpu
    (clock_id == CLOCK_THREAD_CPUTIME_ID
     ? MAKE_THREAD_CPUCLOCK (0, CPUCLOCK_SCHED)
     : MAKE_PROCESS_CPUCLOCK (0, CPUCLOCK_SCHED),
     tp);
}

#  define SYSDEP_GETTIME_CPUTIME					      \
    case CLOCK_PROCESS_CPUTIME_ID:					      \
    case CLOCK_THREAD_CPUTIME_ID:					      \
      retval = maybe_syscall_gettime_cputime (clock_id, tp);		      \
      if (retval == 0)							      \
	break;								      \
      if (retval != EINVAL || !__libc_missing_posix_cpu_timers)		      \
	{								      \
	  __set_errno (retval);						      \
	  retval = -1;							      \
	  break;							      \
	}								      \
      retval = hp_timing_gettime (clock_id, tp);			      \
      break
#  if !HP_TIMING_AVAIL
#   define hp_timing_gettime(clock_id, tp) (__set_errno (EINVAL), -1)
#  endif

# endif
#endif

#include <sysdeps/unix/clock_gettime.c>
