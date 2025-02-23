/* Copyright (C) 1995,1997,1998,1999,2000,2002 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@gnu.ai.mit.edu>, August 1995.

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

#include <errno.h>
#include <sys/shm.h>
#include <ipc_priv.h>

#include <sysdep.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <bp-checks.h>

/* Attach the shared memory segment associated with SHMID to the data
   segment of the calling process.  SHMADDR and SHMFLG determine how
   and where the segment is attached.  */

void *
shmat (shmid, shmaddr, shmflg)
     int shmid;
     const void *shmaddr;
     int shmflg;
{
  INTERNAL_SYSCALL_DECL(err);
  unsigned long resultvar;

#if __BOUNDED_POINTERS__
  size_t length = ~0;
  struct shmid_ds shmds;
  /* It's unfortunate that we need to make another system call to get
     the shared memory segment length...  */
  if (shmctl (shmid, IPC_STAT, &shmds) == 0)
    length = shmds.shm_segsz;
#endif

  resultvar = INTERNAL_SYSCALL (shmat, err, 3, shmid, __ptrvalue ((void *) shmaddr), shmflg);
  if (INTERNAL_SYSCALL_ERROR_P (resultvar, err))
    {
      __set_errno (INTERNAL_SYSCALL_ERRNO (resultvar, err));
      return (void *) -1l;
    }

  return BOUNDED_N (resultvar, length);
}
