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
 * $Id: Config.h,v 2.132 2003/08/21 15:40:37 gul Exp $
 *
 * $Log: Config.h,v $
 * Revision 2.132  2003/08/21 15:40:37  gul
 * Auto increase patchlevel, set 0.9.6a-119
 * Change building commandline for service under win32
 * (patch by Alexander Reznikov)
 *
 * Revision 2.131  2003/08/21 07:24:42  gul
 * Auto increase patchlevel, set 0.9.6a-118
 * Use local buffer in Log() with HAVE_FORK
 *
 * Revision 2.130  2003/08/20 07:33:40  hbrew
 * Auto increase patchlevel, set 0.9.6a-117
 * Addon for 'Avoid double exitfunc() call' patch
 *
 * Revision 2.129  2003/08/19 19:41:41  gul
 * Auto increase patchlevel, set 0.9.6a-116
 * Fix warnings
 *
 * Revision 2.128  2003/08/19 18:08:10  gul
 * Auto increase patchlevel, set 0.9.6a-115
 * Avoid double exitfunc() call
 *
 * Revision 2.127  2003/08/19 18:01:09  stream
 * Auto increase patchlevel, set 0.9.6a-114
 * Fix unix compilation
 *
 * Revision 2.126  2003/08/19 10:16:13  gul
 * Auto increase patchlevel, set 0.9.6a-113
 * Rename trunc() -> trunc_file() due to conflict under OS/2 EMX
 *
 * Revision 2.125  2003/08/19 10:13:17  gul
 * Auto increase patchlevel, set 0.9.6a-112
 * Change Log() semaphoring
 *
 * Revision 2.124  2003/08/18 17:19:14  stream
 * Auto increase patchlevel, set 0.9.6a-111
 * Partially implemented new configuration parser logic (required for config reload)
 *
 * Revision 2.123  2003/08/18 15:44:53  stream
 * Auto increase patchlevel, set 0.9.6a-110
 * New function last_slash(): Return pointer to last directory separator
 * in file name, or NULL if no path present.
 *
 * Revision 2.122  2003/08/18 09:41:03  gul
 * Auto increase patchlevel, set 0.9.6a-109
 * Little cleanup in handle perl errors
 *
 * Revision 2.121  2003/08/18 09:15:41  gul
 * Auto increase patchlevel, set 0.9.6a-108
 * Cosmetics
 *
 * Revision 2.120  2003/08/18 08:23:05  gul
 * Auto increase patchlevel, set 0.9.6a-107
 * Return log semaphoring
 *
 * Revision 2.119  2003/08/18 07:35:11  val
 * Auto increase patchlevel, set 0.9.6a-106
 * multiple changes:
 * - hide-aka/present-aka logic
 * - address mask matching via pmatch
 * - delay_ADR in STATE (define DELAY_ADR removed)
 * - ftnaddress_to_str changed to xftnaddress_to_str (old version #define'd)
 * - parse_ftnaddress now sets zone to domain default if it's omitted
 *
 * Revision 2.118  2003/08/18 07:29:41  val
 * Auto increase patchlevel, set 0.9.6a-105
 * multiple changes:
 * - perl error handling made via fork/thread
 * - on_log() perl hook
 * - perl: msg_send(), on_send(), on_recv()
 * - unless using threads define log buffer via xalloc()
 *
 * Revision 2.117  2003/08/17 19:07:12  gul
 * Auto increase patchlevel, set 0.9.6a-104
 * Fix typo
 *
 * Revision 2.116  2003/08/17 10:38:57  gul
 * Auto increase patchlevel, set 0.9.6a-103
 * Return semaphoring for log and binlog
 *
 * Revision 2.115  2003/08/17 08:12:07  gul
 * Auto increase patchlevel, set 0.9.6a-102
 * Fix typo
 *
 * Revision 2.114  2003/08/16 09:47:27  gul
 * Auto increase patchlevel, set 0.9.6a-101
 * Autodetect tzoff if not specified
 *
 * Revision 2.113  2003/08/16 09:08:35  gul
 * Auto increase patchlevel, set 0.9.6a-100
 * Binlog semaphoring removed
 *
 * Revision 2.112  2003/08/16 06:21:14  gul
 * Auto increase patchlevel, set 0.9.6a-99
 * Log() semaphoring removed
 *
 * Revision 2.111  2003/08/15 08:48:52  gul
 * Auto increase patchlevel, set 0.9.6a-98
 * Compilation error fixed
 *
 * Revision 2.110  2003/08/14 14:19:39  gul
 * Auto increase patchlevel, set 0.9.6a-97
 * Drop remote AKA with another password on outgoing sessions
 *
 * Revision 2.109  2003/08/14 12:56:31  gul
 * Auto increase patchlevel, set 0.9.6a-96
 * Make Log() thread-safe
 *
 * Revision 2.108  2003/08/14 11:43:21  val
 * Auto increase patchlevel, set 0.9.6a-95
 * free allocated log buffer in exitfunc()
 *
 * Revision 2.107  2003/08/14 08:29:24  gul
 * Auto increase patchlevel, set 0.9.6a-94
 * Use snprintf() from sprintf.c if no such libc function
 *
 * Revision 2.106  2003/08/14 07:42:40  val
 * Auto increase patchlevel, set 0.9.6a-93
 * vsnprintf() function, taken from libsasl sources
 *
 * Revision 2.105  2003/08/14 07:40:08  val
 * Auto increase patchlevel, set 0.9.6a-92
 * migrate from vfprintf() to vsnprintf() in Log(), new keyword `nolog'
 *
 * Revision 2.104  2003/08/14 07:39:36  val
 * migrate from vfprintf() to vsnprintf() in Log(), new keyword `nolog'
 *
 * Revision 2.103  2003/08/13 11:59:23  gul
 * Auto increase patchlevel, set 0.9.6a-91
 * Undo my prev patch, sorry ;)
 *
 * Revision 2.102  2003/08/13 11:49:07  gul
 * Auto increase patchlevel, set 0.9.6a-90
 * correct previous fix
 *
 * Revision 2.101  2003/08/13 11:35:28  hbrew
 * Auto increase patchlevel, set 0.9.6a-89
 * Fix warning.
 *
 * Revision 2.100  2003/08/13 08:20:47  val
 * Auto increase patchlevel, set 0.9.6a-88
 * try to avoid mixing Log() output and Perl errors in stderr
 *
 * Revision 2.99  2003/08/13 08:02:53  val
 * Auto increase patchlevel, set 0.9.6a-87
 * define DELAY_ADR ifdef WITH_PERL (todo: provide more flexible logic)
 *
 * Revision 2.98  2003/08/12 09:35:50  gul
 * Auto increase patchlevel, set 0.9.6a-86
 * Cosmetics
 *
 * Revision 2.97  2003/08/12 09:31:47  val
 * Auto increase patchlevel, set 0.9.6a-85
 * don't strlower() mask in flag/exec since we now use pmatch_ncase()
 *
 * Revision 2.96  2003/08/12 09:23:03  val
 * Auto increase patchlevel, set 0.9.6a-84
 * migrate from pmatch() to pmatch_ncase()
 *
 * Revision 2.95  2003/08/11 08:36:43  gul
 * Auto increase patchlevel, set 0.9.6a-83
 * workaround winsock bug
 *
 * Revision 2.94  2003/08/11 08:33:18  val
 * Auto increase patchlevel, set 0.9.6a-82
 * better error handling in perl hooks
 *
 * Revision 2.93  2003/08/05 05:36:16  hbrew
 * Auto increase patchlevel, set 0.9.6a-81
 * 'static const char rcsid[]' removed
 *
 * Revision 2.92  2003/08/04 12:23:42  gul
 * Auto increase patchlevel, set 0.9.6a-80
 * Add CVS tags
 *
 * Revision 2.91  2003/08/04 12:17:51  gul
 * Auto increase patchlevel, set 0.9.6a-79
 * Remove extra error message
 *
 * Revision 2.90  2003/08/04 12:12:28  gul
 * Auto increase patchlevel, set 0.9.6a-78
 * Add opterr and optopt vars
 *
 * Revision 2.89  2003/07/30 11:01:39  val
 * Auto increase patchlevel, set 0.9.6a-77
 * perl-dll keyword can be used even when PERLDL is not defined (does nothing)
 *
 * Revision 2.88  2003/07/28 10:24:07  val
 * Auto increase patchlevel, set 0.9.6a-76
 * Perl DLL dynamic load for Win32, config keyword perl-dll, nmake PERLDL=1
 *
 * Revision 2.87  2003/07/19 07:00:08  hbrew
 * Auto increase patchlevel, set 0.9.6a-75
 * Complex patch:
 * * nt/w32tools.c: Fix warnings
 * * nt/w32tools.c: Fix typo in #ifdef
 * * nt/win9x.c: Fix type in #include
 * * Config.h, sys.h, branch.c, nt/service.c,
 *     nt/win9x.c, : _beginthread()-->BEGINTHREAD()
 * * binkd.c, common.h, mkfls/nt95-msvc/Makefile.dep,
 *     nt/service.c, nt/w32tools.c,nt/win9x.c: cosmitic code cleanup
 *
 * Revision 2.86  2003/07/19 06:59:37  hbrew
 * Auto increase patchlevel, set 0.9.6a-74
 * Complex patch:
 * * nt/w32tools.c: Fix warnings
 * * nt/w32tools.c: Fix typo in #ifdef
 * * nt/win9x.c: Fix type in #include
 * * Config.h, sys.h, branch.c, nt/service.c,
 *     nt/win9x.c, : _beginthread()-->BEGINTHREAD()
 * * binkd.c, common.h, mkfls/nt95-msvc/Makefile.dep,
 *     nt/service.c, nt/w32tools.c,nt/win9x.c: cosmitic code cleanup
 *
 * Revision 2.85  2003/07/19 06:59:34  hbrew
 * Complex patch:
 * * nt/w32tools.c: Fix warnings
 * * nt/w32tools.c: Fix typo in #ifdef
 * * nt/win9x.c: Fix type in #include
 * * Config.h, sys.h, branch.c, nt/service.c,
 *     nt/win9x.c, : _beginthread()-->BEGINTHREAD()
 * * binkd.c, common.h, mkfls/nt95-msvc/Makefile.dep,
 *     nt/service.c, nt/w32tools.c,nt/win9x.c: cosmitic code cleanup
 *
 * Revision 2.84  2003/07/19 04:26:09  hbrew
 * Auto increase patchlevel, set 0.9.6a-73
 * '\r\n' --> '\n'
 *
 * Revision 2.83  2003/07/18 14:56:37  stas
 * Auto increase patchlevel, set 0.9.6a-72
 * Use description of win2000/XP services
 *
 * Revision 2.82  2003/07/18 13:44:34  stas
 * Auto increase patchlevel, set 0.9.6a-71
 * Difference NT service internal name and display name
 *
 * Revision 2.81  2003/07/18 12:36:01  stas
 * Auto increase patchlevel, set 0.9.6a-70
 * Remove old code; add some checks; use new option '--service' for win9x
 *
 * Revision 2.80  2003/07/18 10:31:06  stas
 * Auto increase patchlevel, set 0.9.6a-69
 * New functions: IsNT(), Is9x(); small code cleanup
 *
 * Revision 2.79  2003/07/18 10:30:36  stas
 * Auto increase patchlevel, set 0.9.6a-68
 * New functions: IsNT(), Is9x(); small code cleanup
 *
 * Revision 2.78  2003/07/18 07:48:59  hbrew
 * Auto increase patchlevel, set 0.9.6a-67
 * binkd9x: Store current dir in registry
 *
 * Revision 2.77  2003/07/18 04:15:08  hbrew
 * Auto increase patchlevel, set 0.9.6a-66
 * Fix 'tell_start_ntservice(): {120} ...' error on Win9x
 *
 * Revision 2.76  2003/07/17 04:32:18  hbrew
 * Auto increase patchlevel, set 0.9.6a-65
 * Fix "No prototype found for 'isdigit'" warning.
 *
 * Revision 2.75  2003/07/17 03:08:23  hbrew
 * Auto increase patchlevel, set 0.9.6a-64
 * Fix uninstall of binkd9x service
 *
 * Revision 2.74  2003/07/17 02:53:07  hbrew
 * Auto increase patchlevel, set 0.9.6a-63
 * Fix MSVC warnings & errors
 *
 * Revision 2.73  2003/07/17 02:42:20  hbrew
 * Auto increase patchlevel, set 0.9.6a-62
 * Compability with nt/service.c & nt/win9x.c.
 * Usage "--service" options as win9x "run-as-service" flag.
 *
 * Revision 2.72  2003/07/17 02:41:51  hbrew
 * Auto increase patchlevel, set 0.9.6a-61
 * Compability with nt/service.c & nt/win9x.c.
 * Usage "--service" options as win9x "run-as-service" flag.
 *
 * Revision 2.71  2003/07/16 15:51:17  stas
 * Auto increase patchlevel, set 0.9.6a-60
 * Fix: restore "Minimise to tray"
 *
 * Revision 2.70  2003/07/16 15:50:46  stas
 * Auto increase patchlevel, set 0.9.6a-59
 * Fix: restore "Minimise to tray"
 *
 * Revision 2.69  2003/07/16 15:43:25  stas
 * Auto increase patchlevel, set 0.9.6a-58
 * Fix: restore -T option
 *
 * Revision 2.68  2003/07/16 15:42:56  stas
 * Auto increase patchlevel, set 0.9.6a-57
 * Fix: restore -T option
 *
 * Revision 2.67  2003/07/16 15:09:22  stas
 * Auto increase patchlevel, set 0.9.6a-56
 * Fix NT services to use getopt(). Improve logging for service
 *
 * Revision 2.66  2003/07/16 15:08:51  stas
 * Auto increase patchlevel, set 0.9.6a-55
 * Fix NT services to use getopt(). Improve logging for service
 *
 * Revision 2.65  2003/07/13 09:37:53  gul
 * Auto increase patchlevel, set 0.9.6a-54
 * Fix daemonize with libc5
 *
 * Revision 2.64  2003/07/12 18:22:08  gul
 * Auto increase patchlevel, set 0.9.6a-53
 * Fix typo in comment
 *
 * Revision 2.63  2003/07/12 18:06:45  gul
 * Auto increase patchlevel, set 0.9.6a-52
 * Fixed node output on debugcfg
 *
 * Revision 2.62  2003/07/11 15:06:44  gul
 * Auto increase patchlevel, set 0.9.6a-51
 * Fix building with libc5
 *
 * Revision 2.61  2003/07/08 06:48:05  gul
 * Auto increase patchlevel, set 0.9.6a-50
 * cosmetics
 *
 * Revision 2.60  2003/07/07 18:38:58  hbrew
 * Auto increase patchlevel, set 0.9.6a-49
 * Fix gcc(mingw) warnings:
 *
 * getopt.c:   suggest explicit braces to avoid ambiguous `else'
 * nt/win9x.c: Avoid gcc warnings about non-handled enumeration values
 *
 * Revision 2.59  2003/07/07 18:38:27  hbrew
 * Auto increase patchlevel, set 0.9.6a-48
 * Fix gcc(mingw) warnings:
 *
 * getopt.c:   suggest explicit braces to avoid ambiguous `else'
 * nt/win9x.c: Avoid gcc warnings about non-handled enumeration values
 *
 * Revision 2.58  2003/07/07 10:39:27  gul
 * Auto increase patchlevel, set 0.9.6a-47
 * getopt() usage fix
 *
 * Revision 2.57  2003/07/07 10:14:22  gul
 * Auto increase patchlevel, set 0.9.6a-46
 * Use getopt() for commandline parse
 *
 * Revision 2.56  2003/07/07 10:13:56  gul
 * Auto increase patchlevel, set 0.9.6a-45
 * Use getopt() for commandline parse
 *
 * Revision 2.55  2003/07/07 08:42:06  val
 * Auto increase patchlevel, set 0.9.6a-44
 * check real length of SvPV() when importing queue element from perl
 *
 * Revision 2.54  2003/07/07 08:38:20  val
 * Auto increase patchlevel, set 0.9.6a-43
 * safe pkthdr-reading function (to byte order and struct alignment)
 *
 * Revision 2.53  2003/07/07 08:34:29  val
 * Auto increase patchlevel, set 0.9.6a-42
 * pmatch() replaced by define to xpmatch()
 *
 * Revision 2.52  2003/07/07 08:33:27  val
 * Auto increase patchlevel, set 0.9.6a-41
 * `perl-hooks' config keyword to specify perl script
 *
 * Revision 2.51  2003/07/06 10:34:29  gul
 * Auto increase patchlevel, set 0.9.6a-40
 * Migrate workaround of 100% CPU load with winsock from stable branch
 *
 * Revision 2.50  2003/07/06 10:18:59  gul
 * Auto increase patchlevel, set 0.9.6a-39
 * Increase loglevel for "Watinig for M_GOT" message
 *
 * Revision 2.49  2003/07/06 08:32:33  gul
 * Auto increase patchlevel, set 0.9.6a-38
 * Decrease logging about link status changes
 *
 * Revision 2.48  2003/07/06 06:49:45  gul
 * Auto increase patchlevel
 *
 * Revision 2.47  2003/07/06 06:48:28  gul
 * Auto increase patchlevel
 *
 * Revision 2.46  2003/07/04 08:13:20  val
 * Auto increase patchlevel
 *
 * Revision 2.45  2003/07/03 05:43:45  gul
 * Auto increase patchlevel
 *
 * Revision 2.44  2003/07/02 18:16:46  gul
 * Auto increase patchlevel
 *
 * Revision 2.43  2003/06/30 22:48:37  hbrew
 * Auto increase patchlevel
 *
 * Revision 2.42  2003/06/30 22:42:30  hbrew
 * Auto increase patchlevel
 *
 * Revision 2.41  2003/06/27 07:45:39  val
 * Auto increase patchlevel
 *
 * Revision 2.40  2003/06/26 13:22:26  gul
 * Auto increase patchlevel
 *
 * Revision 2.39  2003/06/26 13:21:33  gul
 * Auto increase patchlevel
 *
 * Revision 2.38  2003/06/26 12:53:35  gul
 * Auto increase patchlevel
 *
 * Revision 2.37  2003/06/26 10:34:05  val
 * Auto increase patchlevel
 *
 * Revision 2.36  2003/06/25 08:22:19  gul
 * Auto increase patchlevel
 *
 * Revision 2.35  2003/06/25 07:25:05  stas
 * Auto increase patchlevel
 *
 * Revision 2.34  2003/06/24 13:46:35  stas
 * Auto increase patchlevel
 *
 * Revision 2.33  2003/06/24 08:08:49  stas
 * Auto increase patchlevel
 *
 * Revision 2.32  2003/06/24 06:33:43  gul
 * Auto increase patchlevel
 *
 * Revision 2.31  2003/06/24 06:28:24  gul
 * Auto increase patchlevel
 *
 * Revision 2.30  2003/06/21 19:35:49  gul
 * Auto increase patchlevel
 *
 * Revision 2.29  2003/06/21 15:31:51  hbrew
 * Auto increase patchlevel
 *
 * Revision 2.28  2003/06/21 08:41:32  gul
 * Auto increase patchlevel
 *
 * Revision 2.27  2003/06/20 10:37:37  val
 * Auto increase patchlevel
 *
 * Revision 2.26  2003/06/13 03:10:09  hbrew
 * Auto increase patchlevel
 *
 * Revision 2.25  2003/06/12 12:04:14  gul
 * Auto increase patchlevel
 *
 * Revision 2.24  2003/06/12 08:31:00  val
 * Auto increase patchlevel
 *
 * Revision 2.23  2003/06/12 08:21:46  val
 * Auto increase patchlevel
 *
 * Revision 2.22  2003/06/12 08:21:43  val
 * 'skipmask' is replaced with 'skip', which allows more skipping features
 *
 * Revision 2.21  2003/06/11 13:10:37  gul
 * Auto increase patchlevel
 *
 * Revision 2.20  2003/06/11 09:01:16  stas
 * Auto increase patchlevel
 *
 * Revision 2.19  2003/06/11 07:44:26  gul
 * Auto increase patchlevel
 *
 * Revision 2.18  2003/06/10 19:15:28  gul
 * Auto increase patchlevel
 *
 * Revision 2.17  2003/06/10 12:29:16  stas
 * Auto increase patchlevel
 *
 * Revision 2.16  2003/06/10 07:43:37  gul
 * Auto increase patchlevel
 *
 * Revision 2.15  2003/06/10 07:28:28  gul
 * Auto increase patchlevel
 *
 * Revision 2.14  2003/06/09 13:27:31  stas
 * Auto increase patchlevel
 *
 * Revision 2.13  2003/06/08 13:41:07  cvs
 * Auto increase patchlevel
 *
 * Revision 2.12  2003/06/08 13:18:58  gul
 * Added patchlevel
 *
 * Revision 2.11  2003/06/06 16:16:34  gul
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
#define MYVER "0.9.6a-119"

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

#if defined(WIN32) && defined(_MSC_VER)
#define snprintf  _snprintf
#define vsnprintf _vsnprintf
#endif

#if defined(__WATCOMC__) /* expand list if necessary */
#define BEGINTHREAD(a, b, c)   _beginthread(a, NULL, b, c)
#else
#define BEGINTHREAD _beginthread
#endif

/* Pragmas */
#ifdef __WATCOMC__
  #pragma off (unreferenced);
#endif

#endif
