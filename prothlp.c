/*
 *  prothlp.c -- Some tools for protocol.c
 *
 *  prothlp.c is a part of binkd project
 *
 *  Copyright (C) 1997  Dima Maloff, 5047/13
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: prothlp.c,v 2.0 2001/01/10 12:12:38 gul Exp $
 *
 * $Log: prothlp.c,v $
 * Revision 2.0  2001/01/10 12:12:38  gul
 * Binkd is under CVS again
 *
 * Revision 1.3  1997/11/05  01:11:29  mff
 * bt+ arcshield
 *
 * Revision 1.2  1997/10/23  04:00:17  mff
 * minor changes
 *
 * Revision 1.1  1997/03/28  06:49:13  mff
 * Initial revision
 *
 */

#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Config.h"
#include "sys.h"
#include "ftnq.h"
#include "prothlp.h"
#include "srif.h"
#include "assert.h"

int tfile_cmp (TFILE *a, char *netname, size_t size, time_t time)
{
  int rc = strcmp (a->netname, netname);

  if (rc == 0)
  {
    if (a->size != size)
      return a->size - size;
    if (a->time != time)
      return a->time - time;
    return 0;
  }
  else
    return rc;
}

/* Adds a file to killlist */
void add_to_killlist (KILLLIST **killlist, int *n_killlist, char *name, int cond)
{
  *killlist = xrealloc (*killlist, sizeof (KILLLIST) * (*n_killlist + 1));
  memset (*killlist + *n_killlist, 0, sizeof (KILLLIST));
  strnzcpy ((*killlist)[*n_killlist].name, name, MAXPATHLEN);
  (*killlist)[*n_killlist].cond = cond;
  ++*n_killlist;
}

void q_to_killlist (KILLLIST **killlist, int *n_killlist, FTNQ *q)
{
  FTNQ *curr;

  for (curr = q; curr; curr = curr->next)
  {
    if (curr->action == 'a')
    {
      curr->action = 0;
      add_to_killlist (killlist, n_killlist, curr->path, 0);
    }
  }
}

void free_killlist (KILLLIST **killlist, int *n_killlist)
{
  free (*killlist);
  *killlist = 0;
  *n_killlist = 0;
}

/*
 * Process killlist. flag == 's': successful session
 */
void process_killlist (KILLLIST *killlist, int n_killlist, int flag)
{
  int i;

  Log (6, "processing kill list");
  for (i = 0; i < n_killlist; ++i)
    if (killlist[i].cond != 's' || (flag == 's' && killlist[i].cond == 's'))
      delete (killlist[i].name);
}

/* Adds a file to rcvdlist */
void add_to_rcvdlist (RCVDLIST **rcvdlist, int *n_rcvdlist, char *name)
{
  *rcvdlist = xrealloc (*rcvdlist, sizeof (RCVDLIST) * (*n_rcvdlist + 1));
  memset (*rcvdlist + *n_rcvdlist, 0, sizeof (RCVDLIST));
  strnzcpy ((*rcvdlist)[*n_rcvdlist].name, name, MAXPATHLEN);
  ++*n_rcvdlist;
}

void free_rcvdlist (RCVDLIST **rcvdlist, int *n_rcvdlist)
{
  free (*rcvdlist);
  *rcvdlist = 0;
  *n_rcvdlist = 0;
}

void netname (char *s, TFILE *q)
{
  static char *weekext[] = {"su", "mo", "tu", "we", "th", "fr", "sa"};

  if (q->type == 'm')
  {
    sprintf (s, "%08lx.pkt", rnd ());
  }
  else if (q->type == 'r')
  {
    sprintf (s, "%08lx.req", rnd ());
  }
  else
  {
    char *z = max (max (strrchr (q->path, '\\'), strrchr (q->path, '/')), strrchr (q->path, ':'));

    z = z ? z + 1 : q->path;
    strnzcpy (s, z, MAX_NETNAME);

    /* gul: bt+ arcshield */
    if ((z = strrchr (s, '.')) != NULL)
      if (strlen (++z) == 3)
	if ((*z >= '0') && (*z < '7') && (z[1] == '#'))
	  memcpy (z, weekext[*z - '0'], 2);

    z = strquote(s, SQ_CNTRL | SQ_SPACE);
    strnzcpy (s, z, MAX_NETNAME);
    free (z);
  }
}
