/* Test and measure STRLEN functions.
   Copyright (C) 1999, 2002, 2003, 2005, 2011 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Written by Jakub Jelinek <jakub@redhat.com>, 1999.
   Added wcslen support by Liubov Dmitrieva <liubov.dmitrieva@gmail.com>, 2011

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

#define TEST_MAIN
#include "test-string.h"

#ifndef WIDE
# define STRLEN strlen
# define CHAR char
# define MAX_CHAR CHAR_MAX
#else
# include <wchar.h>
# define STRLEN wcslen
# define CHAR wchar_t
# define MAX_CHAR WCHAR_MAX
#endif

typedef size_t (*proto_t) (const CHAR *);

size_t
simple_STRLEN (const CHAR *s)
{
  const CHAR *p;

  for (p = s; *p; ++p);
  return p - s;
}

#ifndef WIDE
size_t
builtin_strlen (const CHAR *p)
{
  return __builtin_strlen (p);
}
IMPL (builtin_strlen, 0)
#endif

IMPL (simple_STRLEN, 0)
IMPL (STRLEN, 1)


static void
do_one_test (impl_t *impl, const CHAR *s, size_t exp_len)
{
  size_t len = CALL (impl, s);
  if (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      return;
    }

  if (HP_TIMING_AVAIL)
    {
      hp_timing_t start __attribute ((unused));
      hp_timing_t stop __attribute ((unused));
      hp_timing_t best_time = ~ (hp_timing_t) 0;
      size_t i;

      for (i = 0; i < 32; ++i)
	{
	  HP_TIMING_NOW (start);
	  CALL (impl, s);
	  HP_TIMING_NOW (stop);
	  HP_TIMING_BEST (best_time, start, stop);
	}

      printf ("\t%zd", (size_t) best_time);
    }
}

static void
do_test (size_t align, size_t len)
{
  size_t i;

  align &= 63;
  if (align + sizeof(CHAR) * len >= page_size)
    return;

  CHAR *buf = (CHAR *) (buf1);

  for (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % MAX_CHAR;
  buf[align + len] = 0;

  if (HP_TIMING_AVAIL)
    printf ("Length %4zd, alignment %2zd:", len, align);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), len);

  if (HP_TIMING_AVAIL)
    putchar ('\n');
}

static void
do_random_tests (void)
{
  size_t i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + page_size - 512 * sizeof(CHAR));

  for (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      if (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      if (j > 512)
	j = 512;

      for (i = 0; i < j; i++)
	{
	  if (i == len + align)
	    p[i] = 0;
	  else
	    {
	      p[i] = random () & 255;
	      if (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	if (CALL (impl, (CHAR *) (p + align)) != len)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd) %zd != %zd, p %p",
		   n, impl->name, align, CALL (impl, (CHAR *) (p + align)),
		   len, p);
	    ret = 1;
	  }
    }
}

int
test_main (void)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  /* Checking with only 4 * N alignments for wcslen, other alignments are wrong for wchar_t type arrays*/

  for (i = 1; i < 8; ++i)
    {
    do_test (sizeof(CHAR) * i, i);
    do_test (0, i);
    }

  for (i = 2; i <= 12; ++i)
    {
      do_test (0, 1 << i);
      do_test (sizeof(CHAR) * 7, 1 << i);
      do_test (sizeof(CHAR) * i, 1 << i);
      do_test (sizeof(CHAR) * i, (size_t)((1 << i) / 1.5));
    }

  do_random_tests ();
  return ret;
}

#include "../test-skeleton.c"
