/*
 *  ftnnode.h -- Handle our links
 *
 *  ftnnode.h is a part of binkd project
 *
 *  Copyright (C) 1996  Dima Maloff, 5047/13
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: ftnnode.h,v 2.9 2003/06/12 08:30:57 val Exp $
 *
 * $Log: ftnnode.h,v $
 * Revision 2.9  2003/06/12 08:30:57  val
 * check pkt header feature, see keyword 'check-pkthdr'
 *
 * Revision 2.8  2003/05/01 09:55:01  gul
 * Remove -crypt option, add global -r option (disable crypt).
 *
 * Revision 2.7  2003/03/31 19:35:16  gul
 * Clean semaphores usage
 *
 * Revision 2.6  2003/03/11 00:04:25  gul
 * Use patches for compile under MSDOS by MSC 6.0 with IBMTCPIP
 *
 * Revision 2.5  2003/03/01 15:55:02  gul
 * Current outgoing address is now attibute of session, but not node
 *
 * Revision 2.4  2003/02/28 20:39:08  gul
 * Code cleanup:
 * change "()" to "(void)" in function declarations;
 * change C++-style comments to C-style
 *
 * Revision 2.3  2003/02/22 15:53:46  gul
 * Bugfix with locking array of nodes in multithread version
 *
 * Revision 2.2  2003/02/22 11:45:41  gul
 * Do not resolve hosts if proxy or socks5 using
 *
 * Revision 2.1  2001/02/15 11:03:18  gul
 * Added crypt traffic possibility
 *
 * Revision 2.0  2001/01/10 12:12:38  gul
 * Binkd is under CVS again
 *
 * Revision 1.6  1997/11/03  06:10:39  mff
 * +nodes_init()
 *
 * Revision 1.5  1997/10/23  04:06:48  mff
 * many changes to hide pNod int ftnnode.c
 *
 * Revision 1.4  1997/08/19  21:32:09  mff
 * host/port replaced with hosts -- ASCIIz in "host1,host2,..,hostN" form
 *
 * Revision 1.3  1997/06/16  05:49:13  mff
 * Removed bitmapped flavours.
 *
 * Revision 1.2  1997/02/07  07:07:00  mff
 * busy, flvrs, hold_until, ibox, obox, obox_flvr
 *
 * Revision 1.1  1996/12/29  09:41:45  mff
 * Initial revision
 *
 */
#ifndef _ftnnode_h
#define _ftnnode_h

#include <stdio.h>
#include "Config.h"
#include "ftnaddr.h"
#include "iphdr.h"

#define MAXPWDLEN 40

typedef struct _FTN_NODE FTN_NODE;
struct _FTN_NODE
{
  char *hosts;			       /* "host1:port1,host2:port2,*" */

  FTN_ADDR fa;
  char pwd[MAXPWDLEN + 1];
  char obox_flvr;
  char *obox;
  char *ibox;
  int NR_flag;
  int ND_flag;
  int MD_flag;
  int HC_flag;
  int restrictIP;

  time_t hold_until;
  int busy;			       /* 0=free, 'c'=.csy, other=.bsy */
  int mail_flvr;		       /* -1=no mail, other=it's flavour */
  int files_flvr;		       /* -1=no files, other=it's flavour */
};

/*
 * Call this before all others functions from this file.
 */
void nodes_init (void);

/*
 * Call this before exit to free resources.
 */
void nodes_deinit (void);

/*
 * Lock and release pNod array
 */
void locknodesem (void);
void releasenodesem (void);

/*
 * Return up/downlink info by fidoaddress. 0 == node not found
 */
FTN_NODE *get_node_info (FTN_ADDR *fa);

/*
 * Find up/downlink info by fidoaddress and write info into node var.
 * Return pointer to node structure or NULL if node not found.
 */
FTN_NODE *get_node (FTN_ADDR *fa, FTN_NODE *node);

/*
 * Add a new node, or edit old settings for a node
 *
 * 1 -- ok, 0 -- error;
 */
int add_node (FTN_ADDR *fa, char *hosts, char *pwd, char obox_flvr,
	      char *obox, char *ibox, int NR_flag, int ND_flag,
	      int MD_flag, int restrictIP, int HC_flag);

#define NR_ON       1
#define NR_OFF      0
#define NR_USE_OLD -1		       /* Use old value */

#define ND_ON       1
#define ND_OFF      0
#define ND_USE_OLD -1		       /* Use old value */

#define HC_ON       1
#define HC_OFF     -1
#define HC_USE_OLD  0                  /* Use old value, default value */

/*
 * Iterates through nodes while func() == 0.
 */
int foreach_node (int (*func) (FTN_NODE *fn, void *a2), void *a3);

/*
 * Dump node list
 */
void print_node_info (FILE *out);

/*
 * Create a poll for an address (in "z:n/n.p" format) (0 -- bad)
 */
#define POLL_NODE_FLAVOUR 'i'
int poll_node (char *s);

#endif
