/*
 *  readcfg.h -- read config
 *
 *  readcfg.h is a part of binkd project
 *
 *  Copyright (C) 1996-1997  Dima Maloff, 5047/13
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: readcfg.h,v 2.0 2001/01/10 12:12:39 gul Exp $
 *
 * $Log: readcfg.h,v $
 * Revision 2.0  2001/01/10 12:12:39  gul
 * Binkd is under CVS again
 *
 * Revision 1.7  1997/10/23  03:44:03  mff
 * +fdinhist, +fdouthist, +root_domain
 *
 * 1997/07/11  11:51:17  maxb
 * Added fdinhist and fdouthist keywords.
 *
 * Revision 1.6  1997/06/16  05:42:30  mff
 * Added binlog and tzoff keywords.
 *
 * Revision 1.5  1997/03/28  06:36:28  mff
 * Added "exec" keyword
 */
#ifndef _readcfg_h
#define _readcfg_h

#include "Config.h"
#include "iphdr.h"
#include "ftnaddr.h"
#include "ftndom.h"
#include "ftnnode.h"

#define MAXINCLUDELEVEL 8
#define MAXCFGLINE 1024

#define MAXSYSTEMNAME 120
#define MAXSYSOPNAME 120
#define MAXLOCATIONNAME 120
#define MAXNODEINFO 120

extern int nAddr;
extern FTN_ADDR *pAddr;
extern int iport;
extern int oport;
extern int oblksize;
extern int nettimeout;
extern int rescan_delay;
extern int call_delay;
extern int max_servers;
extern int max_clients;
extern char sysname[MAXSYSTEMNAME + 1];
extern char sysop[MAXSYSOPNAME + 1];
extern char location[MAXLOCATIONNAME + 1];
extern char nodeinfo[MAXNODEINFO + 1];
extern char inbound[MAXPATHLEN + 1];
extern char inbound_nonsecure[MAXPATHLEN + 1];
extern char temp_inbound[MAXPATHLEN + 1];
extern int kill_dup_partial_files;
extern int kill_old_partial_files;
extern int kill_old_bsy;
extern int minfree;
extern int minfree_nonsecure;
extern int tries;
extern int hold;
extern int hold_skipped;
extern int backresolv;
extern int send_if_pwd;
extern int debugcfg;
extern char logpath[MAXPATHLEN + 1];
extern char binlogpath[MAXPATHLEN + 1];
extern char fdinhist[MAXPATHLEN + 1];
extern char fdouthist[MAXPATHLEN + 1];
extern char pid_file[MAXPATHLEN + 1];
extern int loglevel;
extern int conlog;
extern int printq;
extern int percents;
extern int tzoff;
extern char root_domain[MAXHOSTNAMELEN + 1];
extern int prescan;
#ifdef MAILBOX
/* FileBoxes dir */
extern char tfilebox[MAXPATHLEN + 1];
/* BrakeBoxes dir */
extern char bfilebox[MAXPATHLEN + 1];
extern int deleteablebox;
#endif
#ifdef HTTPS
extern char proxy[MAXHOSTNAMELEN + 40];
extern char socks[MAXHOSTNAMELEN + 40];
#endif
extern struct conflist_type 
  { char *path;
    struct conflist_type *next;
    unsigned long mtime;
  } *config_list;

/*
 * Parses and reads the path as a config
 */
void readcfg (char *path);

int  get_host_and_port (int n, char *host, unsigned short *port, char *src, FTN_ADDR *fa);

#endif
