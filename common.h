/*
 *  common.h -- common binkd declarations
 *
 *  common.h is a part of binkd project
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: common.h,v 2.9 2003/08/26 16:06:26 stream Exp $
 *
 * $Log: common.h,v $
 * Revision 2.9  2003/08/26 16:06:26  stream
 * Reload configuration on-the fly.
 *
 * Warning! Lot of code can be broken (Perl for sure).
 * Compilation checked only under OS/2-Watcom and NT-MSVC (without Perl)
 *
 * Revision 2.8  2003/07/19 06:59:34  hbrew
 * Complex patch:
 * * nt/w32tools.c: Fix warnings
 * * nt/w32tools.c: Fix typo in #ifdef
 * * nt/win9x.c: Fix type in #include
 * * Config.h, sys.h, branch.c, nt/service.c,
 *     nt/win9x.c, : _beginthread()-->BEGINTHREAD()
 * * binkd.c, common.h, mkfls/nt95-msvc/Makefile.dep,
 *     nt/service.c, nt/w32tools.c,nt/win9x.c: cosmitic code cleanup
 *
 * Revision 2.7  2003/07/18 10:30:33  stas
 * New functions: IsNT(), Is9x(); small code cleanup
 *
 * Revision 2.6  2003/07/16 15:08:49  stas
 * Fix NT services to use getopt(). Improve logging for service
 *
 * Revision 2.5  2003/06/20 10:37:02  val
 * Perl hooks for binkd - initial revision
 *
 * Revision 2.4  2003/06/09 13:27:28  stas
 * New command line parser
 *
 * Revision 2.3  2003/05/01 09:55:01  gul
 * Remove -crypt option, add global -r option (disable crypt).
 *
 * Revision 2.2  2003/03/10 10:57:45  gul
 * Extern declarations moved to header files
 *
 * Revision 2.1  2003/03/10 10:34:52  gul
 * *** empty log message ***
 *
 *
 */
#ifndef _common_h
#define _common_h

#include "iphdr.h"

#ifdef HAVE_THREADS
int add_socket(SOCKET sockfd);
int del_socket(SOCKET sockfd);
#else
#define add_socket(sockfd)
#define del_socket(sockfd)
#endif

#if defined(OS2) && defined(HAVE_THREADS)
void rel_grow_handles(int nh);
#else
#define rel_grow_handles(nh)
#endif

#ifdef WIN32
enum serviceflags{
   w32_noservice=0,
   w32_installservice=1,
   w32_uninstallservice=-1,
   w32_startservice=2,
   w32_stopservice=-2,
   w32_restartservice=3,
   w32_queryservice=4,
   w32_run_as_service=-4
 };
#define CTRL_SERVICESTOP_EVENT    254
#define CTRL_SERVICERESTART_EVENT 255
#endif

/*
 * Get free space in a directory
 */
unsigned long getfree (char *path);

/*
 * Set up break handler, set up exit list if needed
 */
int set_break_handlers (void);

/*
 * Runs a new thread or forks
 */
int branch (void (*) (void *), void *, size_t);

/*
 * From breaksig.c -- binkd runs this from exitlist or
 * from signal handler (Under NT)
 */
void exitfunc (void);

extern int n_servers, n_clients;
extern int binkd_exit;
extern int checkcfg_flag;	/* exit(3) on config change */
extern int pidcmgr;		/* pid for clientmgr */
extern int pidCmgr;             /* real pid for clientmgr (not 0) */
extern int pidsmgr;		/* pid for server */
extern int no_MD5;
extern int no_crypt;
extern int server_flag, client_flag;
extern int poll_flag;
extern int inetd_flag;
extern int quiet_flag;
extern int verbose_flag;
#ifdef BINKD_DAEMONIZE
extern int daemon_flag;
#endif
#ifdef WIN32
#ifndef BINKDW9X
extern int tray_flag;
extern int isService;
#endif
#endif

#endif
