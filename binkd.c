/*
 *  binkd.c -- binkd's main
 *
 *  binkd.c is a part of binkd project
 *
 *  Copyright (C) 1996-2003  Dima Maloff 5047/13 and others
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: binkd.c,v 2.35 2003/06/11 07:44:21 gul Exp $
 *
 * $Log: binkd.c,v $
 * Revision 2.35  2003/06/11 07:44:21  gul
 * Cosmetics
 *
 * Revision 2.34  2003/06/10 19:15:25  gul
 * Also one commandline parser fix
 *
 * Revision 2.32  2003/06/10 07:28:25  gul
 * Fix patch about commandline parsing
 *
 * Revision 2.31  2003/06/09 13:27:28  stas
 * New command line parser
 *
 * Revision 2.30  2003/05/10 00:30:36  hbrew
 * binkd9x: -u option now support '--all' service name (uninstall all services).
 * Unneeded spaces cleanup.
 *
 * Revision 2.29  2003/05/04 08:45:30  gul
 * Lock semaphores more safely for resolve and IP-addr print
 *
 * Revision 2.28  2003/05/01 09:55:01  gul
 * Remove -crypt option, add global -r option (disable crypt).
 *
 * Revision 2.27  2003/03/31 21:48:59  gul
 * Avoid infinite recursion
 *
 * Revision 2.26  2003/03/31 19:53:08  gul
 * Close socket before exit
 *
 * Revision 2.25  2003/03/31 19:35:16  gul
 * Clean semaphores usage
 *
 * Revision 2.24  2003/03/11 11:42:23  gul
 * Use event semaphores for exit threads
 *
 * Revision 2.23  2003/03/11 00:04:25  gul
 * Use patches for compile under MSDOS by MSC 6.0 with IBMTCPIP
 *
 * Revision 2.22  2003/03/10 10:39:23  gul
 * New include file common.h
 *
 * Revision 2.21  2003/03/10 08:38:07  gul
 * Make n_servers/n_clients changes thread-safe
 *
 * Revision 2.20  2003/03/05 13:21:50  gul
 * Fix warnings
 *
 * Revision 2.19  2003/03/04 07:27:11  gul
 * Put OS to log on start
 *
 * Revision 2.18  2003/03/03 09:43:07  gul
 * Cosmetics changes
 *
 * Revision 2.17  2003/03/01 17:42:32  gul
 * Added tzset() call to main() start
 *
 * Revision 2.16  2003/03/01 17:33:25  gul
 * Clean daemonize code
 *
 * Revision 2.15  2003/03/01 15:55:02  gul
 * Current outgoing address is now attibute of session, but not node
 *
 * Revision 2.14  2003/02/28 20:39:08  gul
 * Code cleanup:
 * change "()" to "(void)" in function declarations;
 * change C++-style comments to C-style
 *
 * Revision 2.13  2003/02/22 20:19:54  gul
 * Update copyrightes, 2002->2003
 *
 * Revision 2.12  2003/02/22 14:30:18  gul
 * Make nNod var static
 *
 * Revision 2.11  2003/02/21 16:47:57  gul
 * Remove <socks.h> file and USE_SOCKS macro
 *
 * Revision 2.10  2002/12/10 22:05:29  gul
 * binkd/win32 bugfix
 *
 * Revision 2.9  2002/11/13 07:49:27  gul
 * Fix typo
 *
 * Revision 2.8  2002/11/12 16:55:58  gul
 * Run as service under win9x
 *
 * Revision 2.7  2002/07/22 19:48:30  gul
 * Update usage
 *
 * Revision 2.6  2001/11/07 13:46:20  gul
 * bugfix (added saved_argc)
 *
 * Revision 2.5  2001/10/29 19:31:44  gul
 * Added -h option (print usage)
 *
 * Revision 2.4  2001/10/28 14:52:58  gul
 * Cyrillic filenames fix
 *
 * Revision 2.3  2001/08/24 13:23:28  da
 * binkd/binkd.c
 * binkd/readcfg.c
 * binkd/readcfg.h
 * binkd/server.c
 * binkd/nt/service.c
 *
 * Revision 2.2  2001/05/23 15:44:09  gul
 * help-message fixed (-C option)
 *
 * Revision 2.1  2001/01/16 03:53:23  gul
 * Added -D switch (run as daemon)
 *
 * Revision 2.0  2001/01/10 12:12:37  gul
 * Binkd is under CVS again
 *
 *
 * nsoveiko@doe.carleton.ca 1998/12/14
 * creation of pid_file is now logged and warnings produced
 *
 * Revision 1.15  1998/05/08  03:35:47  mff
 * Added -P switch, brushed up error msgs
 *
 * Revision 1.14  1997/11/03  06:10:39  mff
 * +nodes_init()
 *
 * Revision 1.13  1997/10/23  04:20:53  mff
 * pidfiles fixed, ...
 *
 * Revision 1.12  1997/06/16  05:52:07  mff
 * Added -C, copyright note
 *
 * Revision 1.10  1997/05/17  08:44:42  mff
 * Changed cmd line processing a bit
 *
 * Revision 1.9  1997/03/09  07:16:31  mff
 * Added command line parsing, support for inetd
 *
 * Revision 1.8  1997/02/07  06:42:59  mff
 * Under UNIXs SIGHUP forces binkd to restart
 *
 * Revision 1.7  1997/02/01  05:55:24  mff
 * Changed SIGCHLD support
 *
 * Revision 1.5  1996/12/14  07:00:32  mff
 * Now we use branch() and set_break_handlers()
 *
 * Revision 1.3  1996/12/07  12:26:37  mff
 * SOCKS support by msh
 *
 * Revision 1.1.1 1996/12/02  18:26:00  ufm
 *    Port to NT
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>

#include "Config.h"
#include "sys.h"
#include "iphdr.h"
#include "common.h"
#include "readcfg.h"
#include "server.h"
#include "client.h"
#include "tools.h"
#include "bsy.h"
#include "protocol.h"
#include "assert.h"
#include "binlog.h"
#include "setpttl.h"
#include "sem.h"
#ifdef UNIX
#include "unix/daemonize.h"
#endif

#ifdef WIN32
#include <windows.h>
#include "nt/service.h"
#ifdef BINKDW9X
#include "nt/win9x.h"
#endif
#endif

#ifdef HAVE_THREADS
#include "sem.h"
MUTEXSEM hostsem = 0;
MUTEXSEM resolvsem = 0;
MUTEXSEM varsem = 0;
EVENTSEM eothread = 0;
EVENTSEM exitcmgr = 0;
#ifdef OS2
MUTEXSEM fhsem = 0;
#endif
#endif

/*
 * Global variables
 */
int pidcmgr = 0;		       /* pid for clientmgr */
int pidsmgr = 0;		       /* pid for server */
SOCKET inetd_socket = 0;

char *configpath = NULL;               /* Config file name */

#ifdef HAVE_FORK
static void chld (int signo)
{
#include "reapchld.inc"
}
#endif

#if defined(UNIX) || defined(AMIGA) || (defined(OS2) && defined(HAVE_FORK))
jmp_buf jb;
static void hup (int signo)
{
  Log (2, "got SIGHUP");
  longjmp (jb, 1);
}
#endif

void usage (void)
{
#if defined(WIN32) && !defined(BINKDW9X)
	char *s=NULL;
	if(checkservice() > 0)
	{
	  s="iu\0  -i[(service-name)]  install WindowsNT service\n"
	    "  -u[(service-name)]  UNinstall WindowsNT service\n";
	}
#endif

#if defined(BINKDW9X)
	AllocTempConsole();
#endif

  printf ("usage: binkd [-Cc"
#if defined(BINKD_DAEMONIZE)
          "D"
#endif
#if defined(UNIX) || defined(OS2) || defined(AMIGA)
	  "i"
#elif defined(BINKDW9X)
	  "iut"
#elif defined(WIN32)
	  "T%s"
#endif
	  "pqrsvmh] [-P node] config"
#ifdef OS2
	  " [socket]"
#endif
	  "\n"
#ifdef BINKD_DAEMONIZE
	  "  -D       run as daemon\n"
#endif
#if defined(HAVE_FORK) || defined(BINKDW9X)
	  "  -C       reload on config change\n"
#else
	  "  -C       exit(3) on config change\n"
#endif
	  "  -c       run client only\n"
#if defined(UNIX) || defined(OS2) || defined(AMIGA)
	  "  -i       run from inetd\n"
#elif defined(BINKDW9X)
	  "  -i[(service-name)][q]        install Win9x service\n"
	  "  -u[(service-name|--all)][q]  UNinstall Win9x service\n"
	  "  -t[start|stop|restart][(service-name|--all)][q]  status|control service(s)\n"
#elif defined(WIN32)
	  "  -T       minimize to Tray\n"
	  "%s"
#endif
	  "  -P node  poll a node\n"
	  "  -p       run client only, poll, quit\n"
	  "  -q       be quiet\n"
	  "  -r       disable crypt traffic\n"
	  "  -s       run server only\n"
	  "  -v       be verbose / dump version and quit\n"
	  "  -m       disable CRAM-MD5 authorization\n"
	  "  -h       print this help\n"
	  "\n"
	  "Copyright (c) 1996-2003 Dima Maloff and others.\n"
#if defined(WIN32) && !defined(BINKDW9X)
	  ,s?s:"", s?s+3:""
#endif
	  );

  puts ("\n"
    "This program is free software; you can redistribute it and/or modify\n"
    "it under the terms of the GNU General Public License as published by\n"
	  "the Free Software Foundation. See COPYING.\n"
	  "\n"
	  "Report bugs to 2:463/68 or binkd-bugs@happy.kiev.ua.");
  exit (1);
}

/* Command line flags */
#ifndef WIN32
int inetd_flag = 0;		       /* Run from inetd (-i) */
#endif
#ifdef BINKD_DAEMONIZE
int daemon_flag = 0;		       /* Run as daemon (-D) */
#endif
int server_flag = 0;		       /* Run servermgr (-s) */
int client_flag = 0;		       /* Run clientmgr (-c) */
int poll_flag = 0;		       /* Run clientmgr, make all jobs, quit
				        * (-p) */
int quiet_flag = 0;		       /* Be quiet (-q) */
int verbose_flag = 0;		       /* Be verbose / print version (-v) */
int checkcfg_flag = 0;		       /* exit(3) on config change (-C) */
int no_MD5 = 0;			       /* disable MD5 flag (-m) */
int no_crypt = 0;		       /* disable CRYPT (-r) */

struct polls{
  char *addr;
  struct polls *next;
} *psPolls = NULL;                     /* Create polls (-P) */

#ifdef WIN32
enum serviceflags service_flag = w32_noservice;  /* install, uninstall, start, stop, restart wnt/w9x service */
char *service_name = NULL;
#ifndef BINKDW9X
int tray_flag = 0;                     /* minimize to tray */
#endif
#endif

/* Parse and check command line parameters. Return config file name or NULL
 * On error prints usage information and exit (see usage() function)
 */
char *parseargs (int argc, char *argv[])
{
  char *cfgfile=NULL;
  char *s=NULL;
  int i;
  struct polls *psP;

  for (i = 1; i < argc; ++i)
  {
#if defined(WIN32)
    char *st;

    if (argv[i][0] == '\001'){ /* binkd called as NT Service */
      service_flag = w32_run_as_service;
      i++;
      if(argv[i] && argv[i][0]=='-' && argv[i][1]=='('){
        service_name = strdup(argv[i]+2);
        if( (s=strchr(service_name,')')) ){
          *s='\0';
        }else{
          Log (0, "%s: parenthness mismatched in parameter '%s'", argv[0], argv[i]);
          usage();        /* Todo: send message to event log */
        }
      }else{
        Log(0, "%s: illegal parameter!", argv[0]);
        usage();
      }
      break; /* skip command line processing */
    }
    else
#endif
    if (argv[i][0] == '-')
    {
      s = argv[i] + 1;

      do
      {
	switch (*s)
	  {
	    case '-':
	      /* GNU-style options */
	      if (!strcmp (s + 1, "help"))
		usage ();
	      else
		Log (0, "%s: --%s: unknown command line switch", argv[0], s + 1);
	    case 'C':
	      checkcfg_flag = 1;
	      break;
	    case 'c':
	      client_flag = 1;
	      break;
#if defined(UNIX) || defined(OS2) || defined(AMIGA)
	    case 'i':
	      inetd_flag = 1;
	      break;
#endif
#if defined(WIN32)
#if !defined (BINKDW9X)
	    case 'T':
	      tray_flag = 1;
	      break;
#endif

	    case 't': /* service control/query */
              if ((service_flag != w32_noservice) && (service_flag != w32_run_as_service)) {
                Log (0, "%s: '-t' command line switch can't mixed with '-i', '-u' and other '-t'", argv[0]);
                usage();
              }
              switch (*(++s)){
              case '(':  /* -t(servicename) */
              case '\0': /* -t */
                if (!service_flag) service_flag = w32_queryservice; /* if not service (prevent overwrite) */
                break;
              case 'q':  /* -tq or -tq(servicename) */
                service_flag = w32_queryservice;
                break;
              case 's':
                if(strncmp(s,"start",5)==0){
                  service_flag = w32_startservice;
                  s+=5;
                }
                else if(strncmp(s,"stop",4)==0){
                  service_flag = w32_stopservice;
                  s+=4;
                }
                else{
                  Log (0, "%s: '-t': invalid argument '%s'", argv[0], s);
                  usage();
                }
                break;
              case 'r':
                if(strncmp(s,"restart",7)==0){
                  service_flag = w32_restartservice;
                  s+=7;
                }else{
                  Log (0, "%s: '-t': invalid argument '%s'", argv[0], s);
                  usage();
                }
                break;
              default:
                Log (0, "%s: '-t': invalid argument '%s'", argv[0], s);
                usage();
              }

              switch ( *s ){
              case '(':
                if( (st=strchr(s,')')) ){
                  if (service_flag != w32_run_as_service){ /* skip if run as service*/
                    if (service_name){ /* prevent overwrite service name */
                      Log(0, "%s: '%s': service name specified before, can't overwrite!", argv[0], argv[i]);
                      usage();
                    }else{
                      *st='\0';
                      service_name = strdup(s+1);
                      *st=')';
                    }
                  }
                  s=st+1;
                }else{
                  Log (0, "%s: '-t': parenthness mismatched in argument '%s'", argv[0], s);
                  usage();
                }
              case '\0':
                continue;
              }
	      break;

	    case 'i': /* install service */
              if (service_flag == w32_run_as_service) break;
              if ( service_flag==w32_installservice
                || service_flag==w32_uninstallservice
                || service_flag==w32_queryservice
                || service_flag==w32_startservice
                || service_flag==w32_restartservice
                || service_flag==w32_stopservice
                 ){
                Log (0, "%s: '-i' command line switch can't mixed with '-i', '-t' and other '-u'", argv[0]);
                usage();
              }
              switch ( *++s ){
              case '(':
                if( (st=strchr(s,')')) ){
                  if (!service_flag){ /* prevent overwrite service name */
                    *st='\0';
                    service_name = strdup(s+1);
                    *st=')';
                  }
                  s=st+1;
                }else{
                  Log (0, "%s: '-i': parenthness mismatched in argument '%s'", argv[0], s);
                  usage();
                }
                if(!service_flag)
                  service_flag = w32_installservice;
              case '\0':
                if(!service_flag)
                  service_flag = w32_installservice;
                continue;
              }
	      break;

	    case 'u': /* uninstall service */
              if (service_flag == w32_run_as_service) break;
              if ( service_flag==w32_installservice
                || service_flag==w32_uninstallservice
                || service_flag==w32_queryservice
                || service_flag==w32_startservice
                || service_flag==w32_restartservice
                || service_flag==w32_stopservice
                 ){
                Log (0, "%s: '-u' command line switch can't mixed with '-i', '-t' and other '-u'", argv[0]);
                usage();
              }
              switch ( *++s ){
              case '(':
                if( (st=strchr(s,')')) ){
                  if (!service_flag){ /* prevent overwrite service name */
                    *st='\0';
                    service_name = strdup(s+1);
                    *st=')';
                  }
                  s=st+1;
                }else{
                  Log (0, "%s: '-u': parenthness mismatched in argument '%s'", argv[0], s);
                  usage();
                }
                if(!service_flag)
                  service_flag = w32_uninstallservice;
              case '\0':
                if(!service_flag)
                  service_flag = w32_uninstallservice;
                continue;
              }
	      break;
#endif

	    case 'P': /* create poll to node */
	      if (*(++s) == 0)
	      {
		++i;
		if (argv[i] == 0)
		  Log (0, "%s: -P: missing requred argument", argv[0]);
		else{
		  psP=psPolls;
		  psPolls = malloc(sizeof(psPolls));
                  psPolls->next = psP;
                  psPolls->addr = argv[i];
		}
              }else{
		  psP=psPolls;
		  psPolls = malloc(sizeof(psPolls));
                  psPolls->next = psP;
                  psPolls->addr = s;
              }
	      goto BREAK_WHILE;

	    case 'p': /* run clients and exit */
	      poll_flag = client_flag = 1;
	      break;

	    case 'q': /* quiet */
	      quiet_flag = 1;
	      break;

	    case 's': /* run server only */
	      server_flag = 1;
	      break;

	    case 'm': /* MD5 off */
	      no_MD5 = 1;
	      /* fallthrough */

	    case 'r': /* CRYPT off */
	      no_crypt = 1;
	      break;

	    case 'v': /* verbose */
	      ++verbose_flag;
	      break;

#ifdef BINKD_DAEMONIZE
	    case 'D': /* run as unix daemon */
	      daemon_flag = 1;
	      *s = 'U';
	    case 'U': /* internal use only, already daemonized */
	      break;
#endif

	    case 'h': /* display command line help */
	      usage();

	    default:  /* unknown parameter/option */
	      Log (0, "%s: -%c: unknown command line switch", argv[0], *s);

	    case 0:   /* call without parameters */
	      usage ();
	  }
	++s;
      }
      while (*s);
  BREAK_WHILE:;
    }
    else if (!cfgfile)
    {
      cfgfile = argv[i];
    }
  }

  return cfgfile;
}

#ifdef BINKDW9X
int binkd_main (int argc, char *argv[], char *envp[])
#else
int main (int argc, char *argv[], char *envp[])
#endif
{
  char tmp[128];
#if defined(BINKD_DAEMONIZE)
  int  nochdir;
#endif
#if defined(HAVE_FORK)
  char **saved_argv;

  /* save argv as setproctitle() under some systems will change it */
  saved_argv = mkargv (argc, argv);

  configpath = parseargs(argc, saved_argv);
#else
  configpath = parseargs(argc, argv);
#endif

  tzset();

#if defined(WIN32) && !defined(BINKDW9X)
  if(service(argc, argv, envp) && service_flag!=w32_run_as_service){
    Log(0, "Windows NT service error");
    exit(-1);
  }
#endif

  if (poll_flag && server_flag)
    Log (0, "-p and -s cannot be used together");

  /* No command line options: run both client and server */
  if (!client_flag && !server_flag)
    client_flag = server_flag = 1;


  InitSem (&hostsem);
  InitSem (&resolvsem);
  InitSem (&varsem);
  InitEventSem (&eothread);
  InitEventSem (&exitcmgr);
#ifdef OS2
  InitSem (&fhsem);
#endif

#if defined(UNIX) || defined(OS2) || defined(AMIGA)
  if (inetd_flag)
  {
    inetd_socket = 0;
#ifdef OS2
    if ((inetd_socket = atoi (argv[argc - 1])) == 0)
      Log (0, "%s: bad socket number", argv[argc - 1]);
#endif
#ifdef EMX
    if ((inetd_socket = _impsockhandle (inetd_socket, 0)) == -1)
      Log (0, "_impsockhandle: %s", strerror (errno));
#endif
  }
#endif

  if (verbose_flag >= 3)
    debugcfg = 1;

  /* Init for ftnnode.c */
  nodes_init ();

  if (configpath)
    readcfg (configpath);
  else if (verbose_flag)
  {
#if defined(WIN32) && defined(BINKDW9X)
    AllocTempConsole();
#endif

    printf ("Binkd " MYVER " (" __DATE__ " " __TIME__ "%s)\n", get_os_string ());
    exit (0);
  }
  else if(!configpath){
    Log (0, "%s: invalid command line: config name must be specified", argv[0]);
    usage();
  }
  else
    usage ();

  if (quiet_flag)
  {
    percents = 0;
    conlog = 0;
    printq = 0;
  }
  switch (verbose_flag)
    {
      case 0:
	break;
      case 1:
	percents = printq = 1;
	loglevel = conlog = 4;
	break;
      case 2:
      case 3:
      default:
	percents = printq = 1;
	loglevel = conlog = 6;
	break;
    }

  print_args (tmp, sizeof (tmp), argv + 1);
#ifdef WIN32
  if(service_flag==w32_run_as_service)
    Log (4, "BEGIN service '%s', " MYNAME "/" MYVER "%s%s", service_name, get_os_string(), tmp);
  else
    Log (4, "BEGIN standalone, " MYNAME "/" MYVER "%s%s", get_os_string(), tmp);
#else
  Log (4, "BEGIN, " MYNAME "/" MYVER "%s%s", get_os_string(), tmp);
#endif
  if (sock_init ())
    Log (0, "sock_init: %s", TCPERR ());

  bsy_init ();
  BinLogInit ();
  rnd ();
  initsetproctitle (argc, argv, envp);
#ifdef WIN32
  SetFileApisToOEM();
#endif

  /* Set up break handler, set up exit list if needed */
  if (!set_break_handlers ())
    Log (0, "cannot install break handlers");

#ifdef HAVE_FORK
  signal (SIGCHLD, chld);
#endif

  { /* Create polls and release polls list */
    struct polls *psP;
    while(psPolls){
      poll_node (psPolls->addr);
      psP = psPolls;
      psPolls = psPolls->next;
      free(psP);
    }
  }

#if defined(UNIX) || defined(OS2) || defined(AMIGA)
  if (inetd_flag)
  {
    protocol (inetd_socket, 0, NULL);
    soclose (inetd_socket);
    exit (0);
  }
#endif

#ifdef BINKD_DAEMONIZE
  if (daemon_flag)
  {
	 if (!server_flag)
		 Log (0, "Only server can be run in the daemon mode");
	 else
	 {
		 if (argv[0][0] == '/')
			nochdir = 0;
		 else
		 {
			nochdir = 1;
		 	/* Log (6, "Run with relative path, will not chdir to /"); */
		 }

		 if (binkd_daemonize(nochdir) < 0)
		 Log (0, "Cannot daemonize");
	 }
  }
#endif

  if (client_flag && !server_flag)
  {
#if defined(UNIX) || defined(AMIGA) || (defined(OS2) && defined(HAVE_FORK))
    if (setjmp(jb))
      goto binkdrestart;
    else
      signal (SIGHUP, hup);
#endif
    clientmgr (0);
    exit (0);
  }

  pidsmgr = (int) getpid ();
  if (client_flag && (pidcmgr = branch (clientmgr, 0, 0)) < 0)
  {
    Log (0, "cannot branch out");
  }

#if defined(HAVE_FORK)
  if (setjmp (jb))
  {
binkdrestart:
    exitfunc();
    print_args (tmp, sizeof (tmp), saved_argv + 1);
    Log (2, "exec %s%s", saved_argv[0], tmp);
    if (execv (saved_argv[0], saved_argv) == -1)
      Log (1, "execv: %s", strerror (errno));
  }
  else
  {
    signal (SIGHUP, hup);
  }
#endif

  if (*pid_file)
  {
    if ( unlink (pid_file) == 0 ) /* successfully unlinked, i.e.
                                     an old pid_file was found */
	Log (1, "unexpected pid_file: %s: unlinked", pid_file);
    else
    {
	int current_log_level = 1;
	switch ( errno )
	{
	   case ENOENT :	/* file not found or null pathname */
		current_log_level = 8; /* it's ok */
		break;
	   default :
		break;
	}
	Log (current_log_level, "unlink_pid_file: %s: %s", pid_file, strerror (errno));
    }
    if ( create_sem_file (pid_file) == 0 ) /* could not create pid_file */
	if (loglevel < 5) /* not logged in create_sem_file() */
	    Log (1, "create_sem_file: %s: %s", pid_file, strerror (errno));
  }

  servmgr (0);

#ifdef WIN32
  if(service_name) free(service_name);
#endif
  return 0;
}
