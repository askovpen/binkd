/*
 *  xalloc.c -- wrappers for malloc(), realloc(), strdup()
 *
 *  xalloc.c is a part of binkd project
 *
 *  Copyright (C) 1998  Dima Maloff, 5047/13
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: xalloc.c,v 2.2 2003/08/26 16:06:27 stream Exp $
 *
 * $Log: xalloc.c,v $
 * Revision 2.2  2003/08/26 16:06:27  stream
 * Reload configuration on-the fly.
 *
 * Warning! Lot of code can be broken (Perl for sure).
 * Compilation checked only under OS/2-Watcom and NT-MSVC (without Perl)
 *
 * Revision 2.1  2003/04/06 20:28:43  gul
 * minor bugfix
 *
 * Revision 2.0  2001/01/10 12:12:39  gul
 * Binkd is under CVS again
 *
 * Revision 1.1  1998/05/08  03:37:28  mff
 * Initial revision
 *
 */

#include <stdlib.h>
#include <string.h>
#include "tools.h"

void *xalloc (size_t size)
{
  void *p = malloc (size);

  if (!p)
    Log (0, "Not enough memory (failed to allocate %lu byte(s))",
	 (unsigned long) size);
  memset(p, 0xEE, size);
  return p;
}

void *xrealloc (void *ptr, size_t size)
{
  void *p = realloc (ptr, size);

  if (!p)
    Log (0, "Not enough memory (failed to realloc %p to %lu byte(s))",
	 ptr, (unsigned long) size);
  return p;
}

void *xstrdup (const char *str)
{
  void *p = xalloc (strlen (str) + 1);

  strcpy (p, str);
  return p;
}

void xfree(void *p)
{
  if (p)
    free(p);
}
