/*
 *  srif.h -- Create flags or run external programs on mail events
 *
 *  srif.h is a part of binkd project
 *
 *  Copyright (C) 1996-1997  Dima Maloff, 5047/13
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: srif.h,v 2.3 2003/08/26 16:06:27 stream Exp $
 *
 * $Log: srif.h,v $
 * Revision 2.3  2003/08/26 16:06:27  stream
 * Reload configuration on-the fly.
 *
 * Warning! Lot of code can be broken (Perl for sure).
 * Compilation checked only under OS/2-Watcom and NT-MSVC (without Perl)
 *
 * Revision 2.2  2003/08/23 15:51:51  stream
 * Implemented common list routines for all linked records in configuration
 *
 * Revision 2.1  2002/02/22 00:18:34  gul
 * Run by-file events with the same command-line once after session
 *
 * Revision 2.0  2001/01/10 12:12:39  gul
 * Binkd is under CVS again
 *
 * Revision 1.3  1997/10/23  03:37:25  mff
 * *** empty log message ***
 *
 * Revision 1.2  1997/03/28  06:12:48  mff
 * Changes to support SRIF: + evt_run(), etc.
 */
#ifndef _srif_h
#define _srif_h

#include "ftnq.h"
#include "protoco2.h"

typedef struct _EVT_FLAG EVT_FLAG;
struct _EVT_FLAG
{
  EVT_FLAG *next;
  char *path;				    /* Set this flag if != NULL */
  char *command;			    /* Run this command if != NULL */
  char *pattern;
  int imm;				    /* Immediate flag */
};

/*
 * Tests if filename matches any of EVT_FLAG's patterns.
 */
int evt_test (EVTQ **eq, char *filename, BINKD_CONFIG *config);

/*
 * Runs external programs using S.R.I.F. interface
 * if the name matches one of our "exec"'s
 */
FTNQ *evt_run (EVTQ **eq, FTNQ *q, char *filename0, FTN_ADDR *fa,
               int nfa, int prot, int listed, char *peer_name, STATE *st, BINKD_CONFIG *config);

/*
 * Sets flags for all matched with evt_test events
 */
void evt_set (EVTQ *eq);

#endif
