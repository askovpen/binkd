/*
 *  Config.h -- misc defines
 *
 *  Config.h is a part of binkd project
 *
 *  Copyright (C) 1996-1998  Dima Maloff, 5047/13
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: Config.h,v 2.10.2.10 2003/10/15 14:48:16 stas Exp $
 *
 * $Log: Config.h,v $
 * Revision 2.10.2.10  2003/10/15 14:48:16  stas
 * Auto increase patchlevel, set 0.9.5p4-stable
 * Fix NT service stop
 *
 * Revision 2.10.2.9  2003/10/08 10:32:50  gul
 * Auto increase patchlevel, set 0.9.5p3-stable
 * Fix exit threads in exitfunc()
 *
 * Revision 2.10.2.8  2003/10/07 08:54:22  hbrew
 * Auto increase patchlevel, set 0.9.5p2-stable
 * '\r\n' --> '\n'
 *
 * Revision 2.10.2.7  2003/09/14 12:20:04  gul
 * Clean use pointers to pNod array
 *
 * Revision 2.10.2.6  2003/09/04 18:18:04  gul
 * *** empty log message ***
 *
 * Revision 2.10.2.5  2003/06/11 18:21:15  gul
 * *** empty log message ***
 *
 * Revision 2.10.2.4  2003/06/11 18:10:19  stas
 * Auto increase patchlevel
 *
 * Revision 2.10.2.3  2003/06/11 18:10:16  stas
 * Fix script's bug
 *
 * Revision 2.10.2.2  2003/06/11 13:27:24  gul
 * Auto increase patchlevel
 *
 * Revision 2.10.2.1  2003/06/06 16:17:38  gul
 * Change version
 *
 * Revision 2.10  2003/03/11 09:21:29  gul
 * Fixed OS/2 Watcom compilation
 *
 * Revision 2.9  2003/03/11 00:04:25  gul
 * Use patches for compile under MSDOS by MSC 6.0 with IBMTCPIP
 *
 * Revision 2.8  2003/03/10 12:16:53  gul
 * Use HAVE_DOS_H macro
 *
 * Revision 2.7  2003/03/10 10:39:23  gul
 * New include file common.h
 *
 * Revision 2.6  2003/03/01 20:16:27  gul
 * OS/2 IBM C support
 *
 * Revision 2.5  2003/02/28 19:13:55  gul
 * Added prodcode
 *
 * Revision 2.4  2003/02/22 21:53:39  gul
 * Typo in comment
 *
 * Revision 2.3  2002/11/12 16:55:58  gul
 * Run as service under win9x
 *
 * Revision 2.2  2001/12/25 17:13:15  gul
 * mingw _sleep() fix
 *
 * Revision 2.1  2001/09/24 10:31:39  gul
 * Build under mingw32
 *
 * Revision 2.0  2001/01/10 12:12:37  gul
 * Binkd is under CVS again
 *
 * Revision 1.6  1997/10/23  04:22:28  mff
 * Important -- MAX_BLKSIZE is now 0x7FFF (32*1024 was error)
 */

#ifndef _Config_h
#define _Config_h

#ifdef __WATCOMC__
  #include <stdlib.h>
  #ifndef MAXPATHLEN
    #define MAXPATHLEN _MAX_PATH
  #endif
#elif defined (VISUALCPP)
  #include <direct.h>
  #ifndef MAXPATHLEN
    #define MAXPATHLEN _MAX_PATH
  #endif
#elif defined (__MINGW32__)
  #include <limits.h>
  #ifndef MAXPATHLEN
    #define MAXPATHLEN PATH_MAX
  #endif
#elif defined (IBMC) || defined(__MSC__)
  #ifndef _MAX_PATH
    #include <stdlib.h>
  #endif
  #ifndef MAXPATHLEN
    #define MAXPATHLEN _MAX_PATH
  #endif
#else
  #include <sys/param.h>
#endif

/* Please, no spaces here! */
#define PRTCLNAME "binkp"
#define PRTCLVER "1.1"
#define MYNAME "binkd"
#define MYVER "0.9.5p4-stable"

#define PRODCODE 0x13FF  /* by FTSCPROD */

/* Environment */
#define MAX_ENV_VAR_NAME 256
#if defined(OS2) || defined(WIN32) || defined(DOS)
  #define PATH_SEPARATOR "\\"
#else
  #define PATH_SEPARATOR "/"
#endif

/* Protocol */
#define DEF_PORT 24554
#define DEF_TIMEOUT (5*60)
#define MIN_BLKSIZE 128
#define MAX_BLKSIZE 0x7fffu                 /* Don't change! */
#define DEF_BLKSIZE (4*1024u)
#define MAX_NETNAME 255

#ifndef CHECKCFG_INTERVAL		    /* Can be defined in Makefile */
#define CHECKCFG_INTERVAL rescan_delay
#endif

#define MAILBOX                             /* fileboxes suport */

/* System... */
#define STACKSIZE (256*1024)
#define MKTMPFILE_TRYES 20

#ifndef O_BINARY
  #define O_BINARY 0
#endif
#if defined(__WATCOMC__) || defined(VISUALCPP) || defined(__MINGW32__) || defined(IBMC) || defined(__MSC__)
  #define MKDIR(s) mkdir(s)
#else
  #define MKDIR(s) mkdir(s, 0755)
#endif
#ifndef OS
  #if defined(BINKDW9X)
    #define OS "Win9x"
  #elif defined(WIN32)
    #define OS "Win32"
  #elif defined(OS2)
    #define OS "OS2"
  #elif defined(DOS)
    #define OS "DOS"
  #endif
#endif

#ifdef __MINGW32__
#define open  _open
#define close _close
#define read  _read
#define write _write
#define stat  _stat
#define fstat _fstat
#define sleep(sec) _sleep((sec)*1000ul)
#define snprintf  _snprintf
#define vsnprintf _vsnprintf
#endif

/* Pragmas */
#ifdef __WATCOMC__
  #pragma off (unreferenced);
#endif

#endif
