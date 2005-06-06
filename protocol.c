/*
 *  protocol.c -- binkp implementation
 *
 *  protocol.c is a part of binkd project
 *
 *  Copyright (C) 1996-2004  Dima Maloff, 5047/13 and others
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: protocol.c,v 2.168 2005/06/06 16:55:05 stream Exp $
 *
 * $Log: protocol.c,v $
 * Revision 2.168  2005/06/06 16:55:05  stream
 * Fixed broken ND-mode status.
 *
 * Revision 2.167  2005/02/09 17:33:59  val
 * config docs and makefile changes for the bandwidth limiting code
 *
 * Revision 2.166  2004/11/21 12:18:05  val
 * bandwidth limiting code is now implemented for receiving too
 *
 * Revision 2.165  2004/11/05 12:24:58  gul
 * hide-aka & present-aka did not work on outgoing sessions
 *
 * Revision 2.164  2004/11/03 08:22:21  stas
 * Set 'unsigned char *' to prevent warnings
 *
 * Revision 2.163  2004/10/20 17:30:55  gul
 * Fixed segfault on transmission compressed files
 * when sizeof(off_t)!=sizeof(long) and loglevel>3.
 *
 * Revision 2.162  2004/10/19 16:28:19  gul
 * Do not remove complete received but not renamed partial files
 * for prevent data loss in ND-mode.
 * Remove all partial files for node after successfull session.
 *
 * Revision 2.161  2004/10/18 15:16:32  gul
 * Minor bugfix (patch from Victor Levenets <aq@takas.lt>)
 *
 * Revision 2.160  2004/10/01 09:55:06  gul
 * Fixed memory leak
 * (Reported by Victor Levenets <aq@takas.lt>)
 *
 * Revision 2.159  2004/09/21 08:32:11  val
 * bandwidth limiting logic changed from "max for akas" to "min for akas"
 *
 * Revision 2.158  2004/09/06 10:47:04  val
 * bandwidth limiting code advancements, `listed' session state fix
 *
 * Revision 2.157  2004/09/02 09:31:52  val
 * release CPU when limiting bandwidth on Win32
 *
 * Revision 2.156  2004/09/02 08:56:19  val
 * bandwidth limiting config parameter 'limit-rate'
 *
 * Revision 2.155  2004/08/30 08:05:14  val
 * bandwidth limiting code [experimental]
 *
 * Revision 2.154  2004/08/04 11:32:29  gul
 * Attemp to support large files (>4G)
 *
 * Revision 2.153  2004/01/23 18:09:31  gul
 * Fixed erroneous "Unknown option ... ignored" message
 *
 * Revision 2.152  2004/01/08 13:27:47  val
 * * extend struct dirent for dos and win32 in order to get file attribute
 * * ignore hidden files in boxes for dos/win32/os2
 * * if we can differ files from directories w/o stat(), don't call stat()
 *   when scanning boxes (unix: freebsd)
 * * if we can't unlink file, don't send it again in the same session
 * * for dos/win32/os2 try to clear read/only attribute if can't unlink file
 *
 * Revision 2.151  2004/01/08 13:03:51  val
 * * new functions for parsing and updating addresses in pkt header (raw, char*)
 * * use these functions in shared aka logic
 * * set password in pkt to the pkt password for the main aka of sharing node
 * * config file description updated
 *
 * Revision 2.150  2004/01/08 12:57:18  val
 * * parse up to 3 comma-separated passwords (in,pkt,out)
 * * use out password for outgoing sessions if it's set
 *
 * Revision 2.149  2004/01/08 11:36:06  gul
 * Fix typo in previous patch
 *
 * Revision 2.148  2004/01/07 13:12:29  gul
 * Update 2003->2004 in copyright notices
 *
 * Revision 2.147  2004/01/07 12:23:39  gul
 * Remove zaccept keyword, receiving compressed files possibility
 * is always on now if binkd was compiled with zlib/bzip2 support.
 *
 * Revision 2.146  2003/12/28 10:23:25  gul
 * Print file offset on "receiving interrupted" log message
 *
 * Revision 2.145  2003/12/26 21:12:06  gul
 * Change unixtime and file length/offset to unsigned in protocol messages
 *
 * Revision 2.144  2003/12/15 00:03:55  gul
 * NZ option for M_GET command - request uncompressed file
 *
 * Revision 2.143  2003/12/10 11:12:10  gul
 * Minor fix in decompression deinit
 *
 * Revision 2.142  2003/12/09 21:58:20  gul
 * Bugfix in resend file in compression mode,
 * new functions compress_abort() and decompress_abort().
 *
 * Revision 2.141  2003/11/20 16:21:17  gul
 * Bugfix in sending ND-status with compression
 *
 * Revision 2.140  2003/10/30 11:11:31  gul
 * Drop incoming session if secure remote AKA is busy
 *
 * Revision 2.139  2003/10/30 10:57:46  gul
 * Change inb_done arguments, optimize a bit
 *
 * Revision 2.138  2003/10/30 10:37:00  gul
 * Do not append file partially received from busy remote aka,
 * non-destructive skip it.
 *
 * Revision 2.137  2003/10/29 21:08:39  gul
 * Change include-files structure, relax dependences
 *
 * Revision 2.136  2003/10/24 06:38:41  val
 * fix warning
 *
 * Revision 2.135  2003/10/20 18:44:51  gul
 * Inhibit incorrect error message
 *
 * Revision 2.134  2003/10/20 18:24:07  gul
 * Compression bugfix
 *
 * Revision 2.133  2003/10/19 22:44:17  gul
 * Add xstrcat(), use dynamic strings for OPT
 *
 * Revision 2.132  2003/10/19 12:21:47  gul
 * Stream compression
 *
 * Revision 2.131  2003/10/14 11:37:47  gul
 * Fix typo
 *
 * Revision 2.130  2003/10/14 07:34:28  gul
 * Use getwordx() for parse optional M_FILE params
 *
 * Revision 2.129  2003/10/12 12:58:40  gul
 * No changes ;)
 *
 * Revision 2.128  2003/10/07 17:57:09  gul
 * Some small changes in close threads function.
 * Inhibit errors "socket operation on non-socket" on break.
 *
 * Revision 2.127  2003/09/24 07:32:16  val
 * bzlib2 compression support, new compression keyword: zlevel
 *
 * Revision 2.126  2003/09/22 11:38:47  val
 * new ip checking modes in VAL_STYLE: ipNoUnknown, ipNoError;
 * val's and gul's -ip modes can be used per node as ipRelaxed and ipResolved
 * (lacks readcfg support still)
 *
 * Revision 2.125  2003/09/22 09:54:41  gul
 * Screen output semaphoring, prevent mixing output from threads
 *
 * Revision 2.124  2003/09/19 13:54:30  gul
 * undef VAL_STYLE ip check by default
 *
 * Revision 2.123  2003/09/19 12:52:57  val
 * fix bug with not sending GZ parameter to M_FILE after M_GET
 *
 * Revision 2.122  2003/09/17 07:04:45  val
 * Cosmetics and comment on #define VAL_STYLE
 *
 * Revision 2.121  2003/09/16 06:38:44  val
 * correct IP checking algorithms (gul's one is buggy), correct get_defnode_info()
 *
 * Revision 2.120  2003/09/15 21:10:09  gul
 * Fix remote IP check logic
 *
 * Revision 2.119  2003/09/15 06:57:09  val
 * compression support via zlib: config keywords, improvements, OS/2 code
 *
 * Revision 2.118  2003/09/12 09:09:38  val
 * zlib compression support and configure for unix (my first try to write
 * autoconf script, i hope it works on your system ;-)
 *
 * Revision 2.116  2003/09/08 16:39:39  stream
 * Fixed race conditions when accessing array of nodes in threaded environment
 * ("jumpimg node structures")
 *
 * Revision 2.115  2003/09/05 10:17:21  gul
 * Send argus-compatible freqs.
 * Warning: works only with prescan!
 *
 * Revision 2.114  2003/09/05 09:57:16  gul
 * Process multiply M_NUL FREQ messages
 *
 * Revision 2.113  2003/09/05 06:49:06  val
 * Perl support restored after config reloading patch
 *
 * Revision 2.112  2003/09/05 06:44:05  val
 * Argus-style freq's (M_NUL FREQ) support, not tested yet
 *
 * Revision 2.111  2003/08/29 13:27:34  gul
 * Do not save zero-length .dt files
 *
 * Revision 2.110  2003/08/26 22:18:48  gul
 * Fix compilation under w32-mingw and os2-emx
 *
 * Revision 2.109  2003/08/26 21:01:10  gul
 * Fix compilation under unix
 *
 * Revision 2.108  2003/08/26 16:06:26  stream
 * Reload configuration on-the fly.
 *
 * Warning! Lot of code can be broken (Perl for sure).
 * Compilation checked only under OS/2-Watcom and NT-MSVC (without Perl)
 *
 * Revision 2.107  2003/08/25 19:09:29  gul
 * Flush file buffer after receive data frame,
 * drop session if extra bytes received.
 *
 * Revision 2.106  2003/08/24 19:42:08  gul
 * Get FTN-domain from matched zone in exp_ftnaddress()
 *
 * Revision 2.105  2003/08/24 18:54:30  gul
 * Bugfix in timeout check on win32
 *
 * Revision 2.104  2003/08/24 01:35:59  hbrew
 * Update for previous patch
 *
 * Revision 2.103  2003/08/24 00:45:44  hbrew
 * win9x-select-workaround fix, thanks to Pavel Gulchouck
 *
 * Revision 2.102  2003/08/23 15:51:51  stream
 * Implemented common list routines for all linked records in configuration
 *
 * Revision 2.101  2003/08/19 10:16:12  gul
 * Rename trunc() -> trunc_file() due to conflict under OS/2 EMX
 *
 * Revision 2.100  2003/08/18 07:35:08  val
 * multiple changes:
 * - hide-aka/present-aka logic
 * - address mask matching via pmatch
 * - delay_ADR in STATE (define DELAY_ADR removed)
 * - ftnaddress_to_str changed to xftnaddress_to_str (old version #define'd)
 * - parse_ftnaddress now sets zone to domain default if it's omitted
 *
 * Revision 2.99  2003/08/18 07:29:09  val
 * multiple changes:
 * - perl error handling made via fork/thread
 * - on_log() perl hook
 * - perl: msg_send(), on_send(), on_recv()
 * - unless using threads define log buffer via xalloc()
 *
 * Revision 2.98  2003/08/17 08:12:05  gul
 * Fix typo
 *
 * Revision 2.97  2003/08/16 09:47:25  gul
 * Autodetect tzoff if not specified
 *
 * Revision 2.96  2003/08/15 08:48:50  gul
 * Compilation error fixed
 *
 * Revision 2.95  2003/08/14 14:19:37  gul
 * Drop remote AKA with another password on outgoing sessions
 *
 * Revision 2.94  2003/08/14 08:29:22  gul
 * Use snprintf() from sprintf.c if no such libc function
 *
 * Revision 2.93  2003/08/13 11:59:21  gul
 * Undo my prev patch, sorry ;)
 *
 * Revision 2.92  2003/08/13 11:49:05  gul
 * correct previous fix
 *
 * Revision 2.91  2003/08/13 11:35:26  hbrew
 * Fix warning.
 *
 * Revision 2.90  2003/08/13 08:02:51  val
 * define DELAY_ADR ifdef WITH_PERL (todo: provide more flexible logic)
 *
 * Revision 2.89  2003/08/11 08:36:41  gul
 * workaround winsock bug
 *
 * Revision 2.88  2003/07/06 10:34:27  gul
 * Migrate workaround of 100% CPU load with winsock from stable branch
 *
 * Revision 2.87  2003/07/06 10:18:55  gul
 * Increase loglevel for "Watinig for M_GOT" message
 *
 * Revision 2.86  2003/07/06 08:32:31  gul
 * Decrease logging about link status changes
 *
 * Revision 2.85  2003/07/06 06:48:25  gul
 * Using state->out.fa bugfix
 *
 * Revision 2.84  2003/07/03 05:43:41  gul
 * Another fix for previous patch
 *
 * Revision 2.83  2003/07/02 18:16:43  gul
 * Bugfix for patch about send status without NR-mode
 *
 * Revision 2.82  2003/06/26 13:22:24  gul
 * *** empty log message ***
 *
 * Revision 2.81  2003/06/26 13:21:32  gul
 * More clean status process in no-NR mode
 *
 * Revision 2.80  2003/06/26 12:53:31  gul
 * Send status in no-NR mode to avoid file loosing
 *
 * Revision 2.79  2003/06/25 07:25:00  stas
 * Simple code, continue bugfix to responce negative timestamp
 *
 * Revision 2.78  2003/06/24 13:46:32  stas
 * Fix max value of type time_t
 *
 * Revision 2.77  2003/06/24 08:08:46  stas
 * Bugfix: do not transmit negative value of file time in binkp command-frames and check file time in received frames
 *
 * Revision 2.76  2003/06/24 06:33:42  gul
 * Fix for previous patch
 *
 * Revision 2.75  2003/06/24 06:28:21  gul
 * Check IP for all remote AKAs on outgoing calls
 *
 * Revision 2.74  2003/06/21 19:35:45  gul
 * Fixed remote ip check
 *
 * Revision 2.73  2003/06/21 15:31:48  hbrew
 * Fix warning
 *
 * Revision 2.72  2003/06/21 08:41:29  gul
 * "try" and "hold" did not work if connection closed by remote
 *
 * Revision 2.71  2003/06/20 10:37:02  val
 * Perl hooks for binkd - initial revision
 *
 * Revision 2.70  2003/06/12 08:21:43  val
 * 'skipmask' is replaced with 'skip', which allows more skipping features
 *
 * Revision 2.69  2003/06/08 13:40:07  gul
 * Avoid warning
 *
 * Revision 2.68  2003/06/07 08:46:25  gul
 * New feature added: shared aka
 *
 * Revision 2.67  2003/06/04 20:59:43  gul
 * bugfix: do not force NR-mode if remote uses binkp/1.0
 *
 * Revision 2.66  2003/06/02 17:56:03  gul
 * Workaround old binkd bug in asymmetric NR-mode
 *
 * Revision 2.65  2003/06/02 17:29:28  gul
 * Bugfix in asymmetric ND-mode
 *
 * Revision 2.64  2003/05/30 17:15:22  gul
 * Asymmetric ND-mode, new protocol option NDA
 *
 * Revision 2.63  2003/05/30 16:03:10  gul
 * Asymmetric NR-mode
 *
 * Revision 2.62  2003/05/22 06:39:41  gul
 * Send CRYPT option only in crypt-mode sessions on answer
 *
 * Revision 2.61  2003/05/17 15:37:48  gul
 * Improve logging
 *
 * Revision 2.60  2003/05/17 15:33:51  gul
 * Improve logging
 *
 * Revision 2.59  2003/05/15 06:08:46  gul
 * Crypt bug with asymmetric secure settings
 *
 * Revision 2.58  2003/05/04 10:29:54  gul
 * Say "OPT ND" on answer only if this option specified in config for this node
 *
 * Revision 2.57  2003/05/04 08:45:30  gul
 * Lock semaphores more safely for resolve and IP-addr print
 *
 * Revision 2.56  2003/05/03 20:36:45  gul
 * Print diagnostic message to log on failed session
 *
 * Revision 2.55  2003/05/03 11:04:58  gul
 * Fix typo
 *
 * Revision 2.54  2003/05/03 10:56:00  gul
 * Bugfix in protocol logic (when file already exists)
 *
 * Revision 2.53  2003/05/03 08:41:16  gul
 * bugfix in protocol, when file already exists
 *
 * Revision 2.52  2003/05/01 09:55:01  gul
 * Remove -crypt option, add global -r option (disable crypt).
 *
 * Revision 2.51  2003/04/30 13:38:17  gul
 * Avoid warnings
 *
 * Revision 2.50  2003/04/28 07:30:16  gul
 * Bugfix: Log() changes TCPERRNO
 *
 * Revision 2.49  2003/04/04 13:54:28  gul
 * Bugfix in localtime detection
 *
 * Revision 2.48  2003/04/02 13:12:57  gul
 * Try to use workaround for buggy windows time functions (timezone)
 *
 * Revision 2.47  2003/03/31 20:28:24  gul
 * safe_localtime() and safe_gmtime() functions
 *
 * Revision 2.46  2003/03/31 14:25:36  gul
 * Segfault under FreeBSD
 *
 * Revision 2.45  2003/03/25 14:08:30  gul
 * Do not save empty partial files
 *
 * Revision 2.44  2003/03/11 00:04:25  gul
 * Use patches for compile under MSDOS by MSC 6.0 with IBMTCPIP
 *
 * Revision 2.43  2003/03/10 17:32:37  gul
 * Use socklen_t
 *
 * Revision 2.42  2003/03/10 10:39:23  gul
 * New include file common.h
 *
 * Revision 2.41  2003/03/05 13:21:51  gul
 * Fix warnings
 *
 * Revision 2.40  2003/03/04 13:46:27  gul
 * Small bugfix in binkp protocol logic
 *
 * Revision 2.39  2003/03/04 13:10:39  gul
 * Do not report errors when threads exits by exitfunc
 *
 * Revision 2.38  2003/03/04 09:50:58  gul
 * Cosmetics changes
 *
 * Revision 2.37  2003/03/03 20:16:32  gul
 * Fixed bug in previous patch
 *
 * Revision 2.36  2003/03/02 18:08:56  gul
 * Do not scan outbound twice: on prescan (for TRF report) and at complete_login
 *
 * Revision 2.35  2003/03/02 17:51:37  gul
 * Close received file before send M_GOT
 *
 * Revision 2.34  2003/03/02 14:30:02  gul
 * Drop unsecure AKA with bad source IP address, no drop session
 *
 * Revision 2.33  2003/03/01 20:49:21  gul
 * Fix spelling
 *
 * Revision 2.32  2003/03/01 18:29:52  gul
 * Change size_t to off_t for file sizes and offsets
 *
 * Revision 2.31  2003/03/01 18:16:04  gul
 * Use HAVE_SYS_TIME_H macro
 *
 * Revision 2.30  2003/03/01 15:55:02  gul
 * Current outgoing address is now attibute of session, but not node
 *
 * Revision 2.29  2003/03/01 15:00:16  gul
 * Join skipmask and overwrite into common maskchain
 *
 * Revision 2.28  2003/02/28 19:52:24  gul
 * Small optimize
 *
 * Revision 2.27  2003/02/23 16:47:07  gul
 * change restrictIP logic
 *
 * Revision 2.26  2003/02/23 16:31:21  gul
 * Add "-sip" option in node string.
 * Change "-ip" check logic.
 *
 * Revision 2.25  2003/02/22 20:19:54  gul
 * Update copyrightes, 2002->2003
 *
 * Revision 2.24  2003/02/22 15:53:46  gul
 * Bugfix with locking array of nodes in multithread version
 *
 * Revision 2.23  2003/02/22 12:56:00  gul
 * Do not give unsecure mail to secure link when send-if-pwd
 *
 * Revision 2.22  2003/02/22 12:12:34  gul
 * Cleanup sources
 *
 * Revision 2.21  2003/02/22 11:45:41  gul
 * Do not resolve hosts if proxy or socks5 using
 *
 * Revision 2.20  2003/02/13 19:31:56  gul
 * Ignore non-MD5 challanges
 *
 * Revision 2.19  2003/01/29 20:53:34  gul
 * Assume default domain for remote 4D address
 *
 * Revision 2.18  2003/01/28 16:14:05  gul
 * Bugfix: binkd did not remove lo-files with empty lines
 *
 * Revision 2.17  2003/01/16 13:35:26  gul
 * Fixed crash on bad incoming packets
 *
 * Revision 2.16  2002/11/22 14:40:42  gul
 * Check free space on inbox if defined
 *
 * Revision 2.15  2002/10/22 20:29:46  gul
 * Do not send zero-length data packet as EOF
 * Prevent incorrect "remote already has ..." message
 *
 * Revision 2.14  2002/05/11 10:28:11  gul
 * fix spelling
 *
 * Revision 2.13  2002/05/11 10:27:22  gul
 * Do not send empty (60-bytes) pkt-files
 *
 * Revision 2.12  2002/02/22 08:57:23  gul
 * Pring warning if remote says "OK non-secure" and we have password
 * for the session
 *
 * Revision 2.11  2002/02/22 00:18:34  gul
 * Run by-file events with the same command-line once after session
 *
 * Revision 2.10  2001/07/28 17:26:26  gul
 * Avoid compiler warnings
 *
 * Revision 2.9  2001/07/28 09:56:39  gul
 * NR-mode bugfix
 *
 * Revision 2.8  2001/07/28 09:10:04  gul
 * minor fix in log messages
 *
 * Revision 2.7  2001/07/28 08:53:07  gul
 * set ND-mode bugfix
 *
 * Revision 2.6  2001/05/23 16:48:03  gul
 * msvc warnings fixed
 *
 * Revision 2.5  2001/04/13 20:16:10  gul
 * "OPT CRYPT" was send only in NR-mode
 *
 * Revision 2.4  2001/02/20 12:01:50  gul
 * rename encrypt to encrypt_buf to avoid conflict with unistd.h
 *
 * Revision 2.3  2001/02/16 09:13:25  gul
 * Disable crypt with plaintext password
 *
 * Revision 2.2  2001/02/15 16:05:59  gul
 * crypt bugfix
 *
 * Revision 2.1  2001/02/15 11:03:18  gul
 * Added crypt traffic possibility
 *
 * Revision 2.0  2001/01/10 12:12:38  gul
 * Binkd is under CVS again
 *
 * Revision 1.35  1997/11/04  23:37:11  mff
 * send_block() changed to send as many msgs as possible with one send()
 *
 * Revision 1.34  1997/10/23  03:56:21  mff
 * authentication fixes, new binary log, more?
 *
 * 1997/07/11  11:56:55  maxb
 * Added more informative percents (I think mff won't kill me for this :)
 *
 * Revision 1.33  1997/06/27  01:05:09  mff
 * Now we close link after M_ERR or M_BSY
 *
 * Revision 1.32  1997/06/16  05:45:21  mff
 * Binkd could not correctly ACK receiving of files with some names.
 * Binary log in T-Mail format. Binkd didn't strip disk labels.
 * Session would never end if remote skips files being sent
 * from our outbound filebox. New keyword: `send-if-pwd'.
 *
 * Revision 1.31  1997/05/17  08:42:49  mff
 * Binkd could not ACK some filenames
 *
 * Revision 1.30  1997/05/08  05:30:29  mff
 * End-of-session is now logged verbosely
 *
 * Revision 1.29  1997/03/28  06:47:39  mff
 * SRIF support, prothlp.*, etc?
 *
 * Revision 1.28  1997/03/15  05:06:44  mff
 * Binkp/1.1 finished(?): NR mode, multiple batches. *.bsy touching.
 *
 * Revision 1.26  1997/02/13  07:08:39  mff
 * Support for fileboxes
 *
 * Revision 1.24  1997/01/09  05:31:29  mff
 * minfree and minfree_nonsecure
 *
 * Revision 1.23  1997/01/08  03:59:54  mff
 * Support for mail events flags
 *
 * Revision 1.22  1996/12/29  09:45:05  mff
 * Fixed NONBIO bug
 *
 * Revision 1.18  1996/12/07  12:14:04  mff
 * max_servers limits the number of server processes/threads running
 *
 * Revision 1.12  1996/12/03  11:27:33  mff
 * NT port by ufm
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#else
#include <time.h>
#endif

#include "readcfg.h"
#include "common.h"
#include "protocol.h"
#include "ftnaddr.h"
#include "ftnnode.h"
#include "ftndom.h"
#include "ftnq.h"
#include "iptools.h"
#include "tools.h"
#include "bsy.h"
#include "inbound.h"
#include "srif.h"
#include "readflo.h"
#include "protoco2.h"
#include "prothlp.h"
#include "assert.h"
#include "binlog.h"
#include "setpttl.h"
#include "sem.h"
#include "md5b.h"
#include "crypt.h"
#include "compress.h"

#ifdef WITH_PERL
#include "perlhooks.h"
#endif

/* define to enable val's code for -ip checks (default is gul's code) */
#undef VAL_STYLE
#ifdef VAL_STYLE
enum { ipNoCheck=0, ipResolved=1, ipStrict=2, ipRelaxed, ipNoUnknown, ipNoError };
#endif

static char *scommand[] = {"NUL", "ADR", "PWD", "FILE", "OK", "EOB",
                           "GOT", "ERR", "BSY", "GET", "SKIP"};

/*
 * Fills <<state>> with initial values, allocates buffers, etc.
 */
static int init_protocol (STATE *state, SOCKET socket, FTN_NODE *to, BINKD_CONFIG *config)
{
  memset (state, 0, sizeof (STATE));

  state->major = 1;
  state->minor = 0;
  state->msgs_in_batch = 0;
  state->off_req_sent = 0;
  state->waiting_for_GOT = 0;
  state->send_eof = 0;
  state->inbound = config->inbound_nonsecure;
  state->io_error = 0;
  state->ibuf = xalloc (MAX_BLKSIZE + BLK_HDR_SIZE + 1);
  state->isize = -1;
  state->obuf = xalloc (MAX_BLKSIZE + BLK_HDR_SIZE + 1);
  state->optr = 0;
  state->oleft = 0;
  state->bytes_sent = state->bytes_rcvd = 0;
  state->files_sent = state->files_rcvd = 0;
  state->to = to;
  state->NR_flag = (to && (to->NR_flag == NR_ON || to->ND_flag == ND_ON)) ? WANT_NR : NO_NR;
  state->ND_flag = (to && to->ND_flag == ND_ON) ? THEY_ND : NO_ND;
  state->MD_flag = 0;
  state->MD_challenge = NULL;
  state->crypt_flag = no_crypt ? NO_CRYPT : WE_CRYPT;
  strcpy (state->expected_pwd, "-");
  state->skip_all_flag = state->r_skipped_flag = 0;
  state->maxflvr = 'h';
  state->listed_flag = 0;
  state->fa = NULL;
  state->nfa = state->nallfa = 0;
  state->nAddr = 0; state->pAddr = NULL;
#ifdef WITH_PERL
  state->perl_set_lvl = 0;
#endif
  state->delay_ADR = (config->akamask.first != NULL) ? 1 : 0;
#ifdef WITH_PERL
  state->delay_ADR |= (perl_ok & (1<<4)) != 0;
#endif
  state->delay_EOB = 0;
  state->state_ext = P_NA;
#if defined(WITH_ZLIB) || defined(WITH_BZLIB2)
  state->z_canrecv = state->z_cansend = state->z_oleft = 0;
  state->z_obuf = xalloc (ZBLKSIZE);
#endif
#ifdef WITH_ZLIB
# ifdef ZLIBDL
  if (zlib_loaded)
# endif
  state->z_canrecv |= 1;
#endif
#ifdef WITH_BZLIB2
# ifdef ZLIBDL
  if (bzlib2_loaded)
# endif
  state->z_canrecv |= 2;
#endif
  setsockopts (state->s = socket);
  TF_ZERO (&state->in);
  TF_ZERO (&state->out);
  TF_ZERO (&state->flo);
  TF_ZERO (&state->in_complete);
  state->ND_addr.z = -1;
  state->start_time = safe_time();
  state->evt_queue = NULL;
  Log (6, "binkp init done, socket # is %i", state->s);
  return 1;
}

/* 
 * Close file currently receiving,
 * remove .hr and .dt if it's partial pkt or zero-length
 */
static int close_partial (STATE *state, BINKD_CONFIG *config)
{
  off_t s;

  if (state->in.f)
  {
    s = ftello (state->in.f);
    Log (1, "receiving of %s interrupted at %" PRIuMAX, state->in.netname,
	 (uintmax_t) s);
    if (ispkt (state->in.netname))
    {
      Log (2, "%s: partial .pkt", state->in.netname);
      s = 0;
    }
    else if (s == 0)
    {
      Log (4, "%s: empty partial", state->in.netname);
    }
    fclose (state->in.f);
    if (s == 0)
      inb_reject (state, config);
  }
  TF_ZERO (&state->in);
  return 0;
}

/*
 * Clears protocol buffers and queues, closes files, etc.
 */
static int deinit_protocol (STATE *state, BINKD_CONFIG *config)
{
  int i;

  close_partial(state, config);
  if (state->out.f)
    fclose (state->out.f);
  if (state->flo.f)
    fclose (state->flo.f);
  if (state->killlist)
    free_killlist (&state->killlist, &state->n_killlist);
  if (state->rcvdlist)
    free_rcvdlist (&state->rcvdlist, &state->n_rcvdlist);
  for (i = 0; i < state->n_nosendlist; i++)
    xfree(state->nosendlist[i]);
#if defined(WITH_ZLIB) || defined(WITH_BZLIB2)
  xfree (state->z_obuf);
  if (state->z_recv && state->z_idata)
    decompress_deinit(state->z_recv, state->z_idata);
  if (state->z_send && state->z_odata)
    compress_abort(state->z_send, state->z_odata);
#endif
  xfree (state->ibuf);
  xfree (state->obuf);
  xfree (state->msgs);
  xfree (state->sent_fls);
  if (state->q)
    q_free (state->q, config);
  for (i = 0; i < state->nfa; ++i)
    bsy_remove (state->fa + i, F_BSY, config);
  xfree (state->fa);
  xfree (state->pAddr);
  xfree (state->MD_challenge);
  rel_grow_handles(-state->nfa);
  Log (6, "binkp deinit done...");
  return 0;
}

/* Process rcvdlist */
static FTNQ *process_rcvdlist (STATE *state, FTNQ *q, BINKD_CONFIG *config)
{
  int i;

  Log (6, "processing rcvd list");
  for (i = 0; i < state->n_rcvdlist; ++i)
  {
    q = evt_run(&(state->evt_queue), q, state->rcvdlist[i].name, state->fa,
		state->nfa, state->state == P_SECURE, state->listed_flag,
		state->peer_name, NULL, config);
  }
  return q;
}

/* Fills s[0] and s[1] with binkp frame header using value of u */
static void mkhdr (char *s, unsigned u)
{
  s[0] = (char) (u >> 8);
  s[1] = (char) u;
}

/*
 * Puts a message to the output msg. queue. These msgs will be send
 * right after the current data block.
 */
void msg_send2 (STATE *state, t_msg m, char *s1, char *s2)
{
  if (!s1)
    s1 = "";
  if (!s2)
    s2 = "";
#ifdef WITH_PERL
  if (!perl_on_send(state, &m, &s1, &s2)) return;
#endif
  state->msgs = xrealloc (state->msgs, sizeof (BMSG) * (state->n_msgs + 1));
  state->msgs[state->n_msgs].t = m;
  /* We will check for sz correctness (sz <= 0x7fff) later, when sending
   * messages from the queue. */
  state->msgs[state->n_msgs].sz = strlen (s1) + strlen (s2) + 1;
  state->msgs[state->n_msgs].s =
    xalloc (state->msgs[state->n_msgs].sz + 3);

  mkhdr (state->msgs[state->n_msgs].s,
	 (unsigned) (state->msgs[state->n_msgs].sz | 0x8000));
  state->msgs[state->n_msgs].s[2] = m;

  strcpy (state->msgs[state->n_msgs].s + 3, s1);
  strcat (state->msgs[state->n_msgs].s + 3, s2);
  state->msgs[state->n_msgs].sz += 2;
  if (state->crypt_flag == YES_CRYPT)
    encrypt_buf(state->msgs[state->n_msgs].s, state->msgs[state->n_msgs].sz,
            state->keys_out);

  ++state->n_msgs;
  ++state->msgs_in_batch;

  Log (5, "send message %s %s%s", scommand[m], s1, s2);
}

/*
 * Sends a message using format string
 */
static void msg_sendf (STATE *state, t_msg m, char *s,...)
{
  char msg_text[max (MAXPATHLEN, MAX_NETNAME) + 80];
  va_list ap;

  va_start (ap, s);
  vsnprintf (msg_text, sizeof (msg_text), s, ap);
  va_end (ap);
  msg_send2 (state, m, msg_text, 0);
}

static void current_file_was_sent (STATE *state)
{
  fclose (state->out.f);
  state->sent_fls = xrealloc (state->sent_fls,
			      ++(state->n_sent_fls) * sizeof (TFILE));
  memcpy (state->sent_fls + state->n_sent_fls - 1,
	  &state->out,
	  sizeof (TFILE));
  TF_ZERO (&state->out);
  if (state->ND_flag & WE_ND)
  {
    state->waiting_for_GOT = 1;
    Log(5, "Waiting for M_GOT");
  }
}

/*
 * Sends next msg from the msg queue or next data block
 */
static int send_block (STATE *state, BINKD_CONFIG *config)
{
  int i, n, save_errno;
  const char *save_err;

  /* Have something to send in buffers */
  if (state->optr && state->oleft)
  {
#ifdef BW_LIM
    time_t ctime = time(NULL);
    if (!state->bw_send_utime) {
      state->bw_send_utime = ctime;
      state->bw_send_cps = 0; state->bw_send_cpsN = 0;
    }
    if (ctime > state->bw_send_utime) {
      int cps = state->bw_send_bytes / (ctime - state->bw_send_utime);
      state->bw_send_bytes = 0;
      state->bw_send_utime = ctime;
      if (state->bw_send_cpsN < 10) {
        state->bw_send_cps = (state->bw_send_cpsN*state->bw_send_cps + cps) / (state->bw_send_cpsN + 1);
        state->bw_send_cpsN++;
      }
      else state->bw_send_cps = (9*state->bw_send_cps + cps) / 10;
      Log (9, "send: current cps is %u, avg. cps is %u", cps, state->bw_send_cps);
    }
    else if (state->bw_send && state->bw_send_bytes > state->bw_send) 
      return 2; /* val: return 2 not release cpu on win32 */
    if (state->bw_send && state->bw_send_cps > state->bw_send) 
      return 2; /* val: return 2 not release cpu on win32 */
#endif
    Log (7, "sending %i byte(s)", state->oleft);
    n = send (state->s, state->optr, state->oleft, 0);
#ifdef BW_LIM
    state->bw_send_bytes += n;
#endif
    save_errno = TCPERRNO;
    save_err = TCPERR ();
    Log (7, "send() done, rc=%i", n);
    if (n == state->oleft)
    {
      state->optr = 0;
      state->oleft = 0;
      Log (7, "data sent");
    }
    else if (n == SOCKET_ERROR)
    {
      if (save_errno != TCPERR_WOULDBLOCK && save_errno != TCPERR_AGAIN)
      {
	state->io_error = 1;
	if (!binkd_exit)
	{
	  Log (1, "send: %s", save_err);
	  if (state->to)
	    bad_try (&state->to->fa, save_err, BAD_IO, config);
	}
	return 0;
      }
      Log (7, "data transfer would block");
      return 2;
    }
    else
    {
      state->optr += n;
      state->oleft -= n;
      Log (7, "partially sent, %i byte(s) left", state->oleft);
    }
  }
  else
  {
    /* There is no data partially sent */

    if (state->msgs)
    {
      /* There are unsent msgs */
      state->optr = state->obuf;
      state->oleft = 0;
      for (i = 0; i < state->n_msgs; ++i)
      {
	if (state->msgs[i].s)
	{
	  /* Check for possible internal error */
	  if (state->msgs[i].sz - 2 > MAX_BLKSIZE)
	  {
	    Log (1, "size of msg we want to send is too big (%i)",
		 state->msgs[i].sz - 2);
	    return 0;
	  }

	  /* Is there some space for the new msg? */
	  if (state->oleft + state->msgs[i].sz > MAX_BLKSIZE)
	    break;

	  Log (7, "put next msg to obuf, %i", state->msgs[i].sz);
	  memcpy (state->optr, state->msgs[i].s, state->msgs[i].sz);
	  state->oleft += state->msgs[i].sz;
	  state->optr += state->msgs[i].sz;
	  free (state->msgs[i].s);
	  state->msgs[i].s = 0;
	}
      }

      /* Optr should be non-NULL if there are some data to send */
      if (state->oleft == 0)
	state->optr = 0;
      else
	state->optr = state->obuf;

      /* If the message queue is empty, free it */
      if (i >= state->n_msgs)
      {
	free (state->msgs);
	state->msgs = 0;
	state->n_msgs = 0;
      }
      return 1;
    }
    else if ((state->out.f && !state->off_req_sent && !state->waiting_for_GOT) ||
	     state->send_eof)
    {
      /* There is a file in transfer and we don't wait for an answer for * *
       * "FILE ... -1" */
      int sz;
      unsigned char *buf = (unsigned char *)state->obuf + BLK_HDR_SIZE;

      if (state->out.f)
      {
#if defined(WITH_ZLIB) || defined(WITH_BZLIB2)
	if (state->z_send)
	{ sz = ZBLKSIZE - state->z_oleft;
	  buf = state->z_obuf + state->z_oleft;
	} else
	  sz = config->oblksize;
	sz = min ((off_t) sz, state->out.size - ftello (state->out.f));
#else
	sz = min ((off_t) config->oblksize, state->out.size - ftello (state->out.f));
#endif
      }
      else
      {
	state->send_eof = 0;
	sz = 0;
      }
      Log (10, "next block to send: %u byte(s)", sz);
      mkhdr (state->obuf, sz);
      if (sz != 0)
      {
        Log (10, "freading %u byte(s)", sz);
        if ((n = fread (buf, 1, sz, state->out.f)) < (int) sz)
        {
          Log (1, "error reading %s: expected %u, read %i",
               state->out.path, sz, n);
          return 0;
        }

        /* Dirty hack :-) - if
         *  1. this is the first block of the file, and
         *  2. this is pkt-header, and
         *  3. pkt destination is shared address
         *  change destination address to main aka.
         */
        if ((ftello(state->out.f)==(off_t)sz) && (sz >= 60) /* size of pkt header + 2 bytes */
            && ispkt(state->out.netname))
        {
          short cz, cnet, cnode, cp;
          SHARED_CHAIN *chn;
          if (pkt_getaddr(buf, NULL, NULL, NULL, NULL, &cz, &cnet, &cnode, &cp)) {
            Log(9, "First block of %s", state->out.path);
            Log(7, "PKT dest: %d:%d/%d.%d", cz, cnet, cnode, cp);
            /* Scan all shared addresses */
            for (chn = config->shares.first; chn; chn = chn->next)
            {
              if ((chn->sha.z    == cz) &&
                  (chn->sha.net  == cnet)  &&
                  (chn->sha.node == cnode) &&
                  (chn->sha.p    == cp))
              { /* Found */
                FTN_ADDR *fa = NULL;
                if (state->to) fa = &state->to->fa;
                  else if (state->fa) fa = state->fa;
                if (fa)
                { /* Change to main address and check */
                  pkt_setaddr(buf, -1, -1, -1, -1, (short)fa->z, (short)fa->net, (short)fa->node, (short)fa->p);
                  pkt_getaddr(buf, NULL, NULL, NULL, NULL, &cz, &cnet, &cnode, &cp);
                  Log(7, "Change dest to: %d:%d/%d.%d", cz, cnet, cnode, cp);
                  /* Set corresponding pkt password */
                  {
                    FTN_NODE *fn = state->to ? state->to : get_node_info(fa, config);
                    memset(buf+26, 0, 8);
                    if (fn->pkt_pwd) memmove(buf+26, fn->pkt_pwd, 8);
                  }
                }
                break;
              }
            }
          }
        }
      }
#if defined(WITH_ZLIB) || defined(WITH_BZLIB2)
      if (state->z_send && state->out.f)
      {
        int nput = 0;  /* number of compressed bytes */
        int nget = 0;  /* number of read uncompressed bytes from buffer */
        int ocnt;      /* number of bytes compressed by one call */
        int rc;
        off_t fleft;

        sz += state->z_oleft;
        while (1)
        {
          ocnt = config->oblksize - nput;
          nget = sz;
          fleft = state->out.size - ftello(state->out.f);
          rc = do_compress(state->z_send,
                           state->obuf + BLK_HDR_SIZE + nput, &ocnt,
                           state->z_obuf, &nget,
                           fleft ? 0 : 1,
                           state->z_odata);
          if (rc == -1) {
            Log (1, "error compression %s, rc=%d", state->out.path, rc);
            return 0;
          }
          state->z_osize += nget;
          state->z_cosize += ocnt;
          nput += ocnt;
          if (!fleft && rc == 1) break;
          if (nput == config->oblksize) break;
          sz = min(fleft, ZBLKSIZE);
          if (sz == 0) continue;
          Log (10, "freading %u byte(s)", sz);
          if ((n = fread (state->z_obuf, 1, sz, state->out.f)) < (int) sz)
          {
            Log (1, "error reading %s: expected %u, read %i",
                 state->out.path, sz, n);
            return 0;
          }
        }
        /* left rest of incoming (uncompressed) buffer */
        if (nget < sz) {
          memmove(state->z_obuf, state->z_obuf + nget, sz - nget);
          state->z_oleft = sz - nget;
        } else
          state->z_oleft = 0;
        sz = nput;
        mkhdr(state->obuf, sz);
        if (!fleft && rc == 1)
        {
          Log(4, "Compressed %" PRIuMAX " bytes to %" PRIuMAX " for %s, ratio %.1f%%",
              (uintmax_t)state->z_osize, (uintmax_t)state->z_cosize,
              state->out.netname, 100.0 * state->z_cosize / state->z_osize);
          compress_deinit(state->z_send, state->z_odata);
          state->z_odata = NULL;
          state->z_send = 0;
        }
      }
#endif

      if (config->percents && state->out.f && state->out.size > 0)
      {
        LockSem(&lsem);
        printf ("%-20.20s %3.0f%%\r", state->out.netname,
                100.0 * ftello (state->out.f) / (float) state->out.size);
        fflush (stdout);
        ReleaseSem(&lsem);
      }

      if (state->out.f && (sz == 0 || state->out.size == ftello(state->out.f))
#if defined(WITH_ZLIB) || defined(WITH_BZLIB2)
          && !state->z_send
#endif
         )
        /* The current file have been sent */
        current_file_was_sent (state);
      state->optr = state->obuf;
      state->oleft = sz + BLK_HDR_SIZE;
      if (state->crypt_flag == YES_CRYPT)
        encrypt_buf(state->optr, state->oleft, state->keys_out);
    }
  }
  return 1;
}

/*
 * Extends parse_args() by sending error message to the remote
 */
static char *parse_msg_args (int ac, char **av, char *s, char *ID, STATE *state)
{
  char *rc = parse_args (ac, av, s, ID);

  if (!rc)
    msg_send2 (state, M_ERR, ID, ": cannot parse args");
  return rc;
}

/*
 * Truncates the file if action == 't'
 * Removes the file if action == 'd'
 * Removes on successful session if action == 's'
 * Otherwise lefts the file unchanged
 */
static int perform_action (STATE *state, char *path, char action)
{
  if (action == 'd')
  {
    if (delete(path) != 0) {
#if defined(WIN32) || defined(OS2) || defined(DOS)
      /* clear r/o attribute and try again */
      if (chmod(path, S_IREAD | S_IWRITE) == 0 && delete(path) != 0) {
#endif
      /* add to list not to send it again */
      Log (5, "adding file `%s' to not-to-send list", path);
      state->nosendlist = xrealloc(state->nosendlist, (state->n_nosendlist+1)*sizeof(state->nosendlist[0]));
      state->nosendlist[state->n_nosendlist++] = xstrdup(path);
#if defined(WIN32) || defined(OS2) || defined(DOS)
      }
#endif
    }
  }
  else if (action == 't')
  {
    trunc_file (path);
  }
  else if (action == 's')
  {
    add_to_killlist (&state->killlist, &state->n_killlist, path, 's');
  }
  return 1;
}

/*
 * Marks the file in flopath as sent. (Empty .?lo will be removed)
 * If file == 0 just tryes to unlink flopath.
 * If flopath == 0 performs action on file.
 */
static int remove_from_spool (STATE *state, char *flopath,
                              char *file, char action, BINKD_CONFIG *config)
{
  char buf[MAXPATHLEN + 1], *w = 0;
  FILE *flo = 0;
  off_t offset = 0, curr_offset;
  int i;
  int seek_flag = 0;		       /* Seek _state->flo.f_ to */

  /* _offset_ after processing */
  int empty_flo_flag = 1;

  if (file)
    Log (5, "removing from spool: %s", file);
  else if (flopath)
    Log (5, "removing flo: %s", flopath);
  else
    Log (1, "internal error in remove_from_spool!");

  if (flopath && *flopath)	       /* A file attached via .?lo */
  {
    if (state->flo.f && !strcmp (state->flo.path, flopath))
    {
      flo = state->flo.f;
      offset = ftello (flo);
      fseek (flo, 0, SEEK_SET);
      seek_flag = 1;
    }
    else
    {
      if ((flo = fopen (flopath, "r+b")) == 0)
      {
	Log (5, "remove_from_spool: %s: %s", flopath, strerror (errno));
	return 0;
      }
    }

    while (!feof (flo))
    {
      curr_offset = ftello (flo);
      if (!fgets (buf, MAXPATHLEN, flo))
	break;
      for (i = strlen (buf) - 1; i >= 0 && isspace (buf[i]); --i)
	buf[i] = 0;
      if (buf[0] == '\0') continue;

      if (file && (!strcmp (file, buf) ||
		 ((*buf == '^' || *buf == '#') && !strcmp (file, buf + 1))))
      {
	clearerr (flo);
	if (fseeko (flo, curr_offset, SEEK_SET) == EOF)
	  Log (1, "remove_from_spool: fseek(%s): %s", flopath,
	       strerror (errno));
	else if (putc ('~', flo) == EOF)
	  Log (1, "remove_from_spool: fputc(%s): %s", flopath,
	       strerror (errno));
	fflush (flo);
	/* The line was marked, now skip it */
	fgets (buf, MAXPATHLEN, flo);
	/* We've found the file in flo, so try to translate it's name before
	 * the action */
	if (w == 0 && (w = trans_flo_line (file, config->rf_rules.first)) != 0)
	{
	  Log (5, "%s mapped to %s", file, w);
	}
      }
      else if (*buf && *buf != '~')
      {
	empty_flo_flag = 0;
      }
    }
    if (seek_flag)
    {
      fseeko (flo, offset, SEEK_SET);
      fflush (flo);
    }
    else
    {
      fclose (flo);
      if (empty_flo_flag)
	delete (flopath);
    }
  }
  if (w)
  {
    perform_action (state, w, action);
    free (w);
  }
  else if (file)
    perform_action (state, file, action);
  return 1;
}

/*
 * Removes n-th element from the sent files queue,
 * free()'s the queue if it's empty
 */
static void remove_from_sent_files_queue (STATE *state, int n)
{
  state->sent_fls[n].netname[0] = 0;

  for (n = 0; n < state->n_sent_fls; ++n)
    if (state->sent_fls[n].netname[0])
      return;

  if (n >= state->n_sent_fls)
  {
    free (state->sent_fls);
    state->sent_fls = 0;
    state->n_sent_fls = 0;
  }
}

static void do_prescan(STATE *state, BINKD_CONFIG *config)
{
  char s[64];
  uintmax_t netsize, filessize;
  int i;

  if (OK_SEND_FILES (state, config) && config->prescan)
  {
    state->q = q_scan_addrs (0, state->fa, state->nfa, state->to ? 1 : 0, config);
    q_get_sizes (state->q, &netsize, &filessize);
    sprintf(s, "%" PRIuMAX " %" PRIuMAX, netsize, filessize);
    msg_send2 (state, M_NUL, "TRF ", s);
    if (state->major * 100 + state->minor <= 100)
      for (i = q_freq_num (state->q); i>0; i--)
        msg_send2 (state, M_NUL, "FREQ", "");
  }
}

/*
 * These functions down to recv_block() handle binkp msgs
 *
 * They should return 0 on fatal error, otherwise 1
 */

/*
 * Parses if needed and logs down the M_NUL message data
 */
static int NUL (STATE *state, char *buf, int sz, BINKD_CONFIG *config)
{
  char *s, *a, *b;

  UNUSED_ARG(sz);
  UNUSED_ARG(config);

  Log (3, "%s", s = strquote (buf, SQ_CNTRL));
  if (!memcmp (s, "VER ", 4) &&
      (a = strstr (s, PRTCLNAME "/")) != 0 &&
      (b = strstr (a, ".")) != 0)
  {
    state->major = atoi (a + 6);
    state->minor = atoi (b + 1);
    Log (6, "remote uses " PRTCLNAME " v.%i.%i", state->major, state->minor);
  }
  else if (!memcmp (s, "OPT ", 4))
  {
    char *w;
    int i;

    for (i = 1; (w = getwordx (s + 4, i, 0)) != 0; ++i)
    {
      if (!strcmp (w, "NR"))
      {
	state->NR_flag |= WE_NR;      /* They want NR mode - turn it on */
	Log(2, "Remote requests NR mode");
      }
      if (!strcmp (w, "ND"))
      {
	state->ND_flag |= WE_ND;      /* They want ND mode - turn it on */
	Log(2, "Remote requests ND mode");
      }
      if (!strcmp (w, "NDA"))
      {
	state->ND_flag |= CAN_NDA;     /* They supports asymmetric ND */
	Log(2, "Remote supports asymmetric ND mode");
      }
      if (!strcmp (w, "CRYPT"))
      {
	state->crypt_flag |= THEY_CRYPT;  /* They want crypt mode */
	Log(2, "Remote requests CRYPT mode");
      }
      if (!strncmp(w, "CRAM-MD5-", 9) && !no_MD5 &&
          state->to && (state->to->MD_flag>=0))
      {
	Log(2, "Remote requests MD mode");
	xfree(state->MD_challenge);
	state->MD_challenge=MD_getChallenge(w, NULL);
      }
#ifdef WITH_ZLIB
      if (!strcmp (w, "GZ"))
      {
        Log(2, "Remote supports GZ mode");
#ifdef ZLIBDL
        if (zlib_loaded)
#endif
        state->z_cansend |= 1;
      }
#endif
#ifdef WITH_BZLIB2
      if (!strcmp (w, "BZ2"))
      {
        Log(2, "Remote supports BZ2 mode");
#ifdef ZLIBDL
        if (bzlib2_loaded)
#endif
        state->z_cansend |= 2;
      }
#endif
      if (!strcmp (w, "EXTCMD"))
      {
	state->extcmd = 1;  /* They can accept extra params for commands */
	Log(2, "Remote supports EXTCMD mode");
      }
      free (w);
    }
  }
  else if (!memcmp (s, "SYS ", 4))
    strnzcpy (state->sysname, s + 4, sizeof (state->sysname));
  else if (!memcmp (s, "ZYZ ", 4))
    strnzcpy (state->sysop, s + 4, sizeof (state->sysop));
  else if (!memcmp (s, "LOC ", 4))
    strnzcpy (state->location, s + 4, sizeof (state->location));
  else if (!memcmp (s, "FREQ", 4)) {
    state->delay_EOB++;
    Log(2, "Remote claims to have a FREQ for us");
  }
  free (s);
  return 1;
}

/*
 * Handles M_ERR msg from the remote
 */
static int RError (STATE *state, char *buf, int sz, BINKD_CONFIG *config)
{
  char *s;

  UNUSED_ARG(sz);

  Log (1, "rerror: %s", s = strquote (buf, SQ_CNTRL));
  if (state->to)
    bad_try (&state->to->fa, s, BAD_MERR, config);
  free (s);
  return 0;
}

static int BSY (STATE *state, char *buf, int sz, BINKD_CONFIG *config)
{
  char *s;

  UNUSED_ARG(sz);

  Log (1, "got M_BSY: %s", s = strquote (buf, SQ_CNTRL));
  if (state->to)
    bad_try (&state->to->fa, s, BAD_MBSY, config);
  free (s);
  return 0;
}

static char * add_shared_akas(char * s, BINKD_CONFIG *config)
{
  int i;
  char * w, *c;
  SHARED_CHAIN   * chn;
  FTN_ADDR_CHAIN * fta;
  FTN_ADDR fa;
  int count = 0;
  char * ad = 0;
  char szFTNAddr[FTN_ADDR_SZ + 1];

  for (i = 1; (w = getwordx (s, i, 0)) != 0; ++i)
  {
    if (parse_ftnaddress (w, &fa, config->pDomains.first) && is5D (&fa))
    {
      for(chn = config->shares.first;chn;chn = chn->next)
      {
        if (ftnaddress_cmp(&fa,&chn->sha) == 0)
        {
          /* I think, that if shared address was exposed
           * by remote node, it should be deleted...
           */
          ftnaddress_to_str (szFTNAddr,&fa);
          Log(1,"shared aka `%s' used by node %s",szFTNAddr,s);
          /* fill this aka by spaces */
          c = strstr(s,w);
          if (c)
          {
            memset(c,' ', strlen(w));
            i--;
          }
          break;
        }
        else
        {
          for (fta = chn->sfa.first;fta;fta = fta->next)
          {
          if (ftnaddress_cmp(&fta->fa,&fa) == 0)
          {
            if (ad == 0)
            {
              ad = xalloc(FTN_ADDR_SZ+1);
              ad[0] = 0;
              count = 1;
              } else {
                ad = xrealloc(ad,(++count)*(FTN_ADDR_SZ+1));
              }
              ftnaddress_to_str (szFTNAddr,&chn->sha);
              strcat(ad, " ");
              strcat(ad, szFTNAddr);
              Log(2,"shared aka %s is added",szFTNAddr);
              break;
            }
          }
        }
      }
    }
    free (w);
  }
  return ad;
}

static int ADR (STATE *state, char *s, int sz, BINKD_CONFIG *config)
{
  int i, j, main_AKA_ok = 0;
#ifndef VAL_STYLE
  int ip_verified = 0;
#else
  enum { CHECK_OFF, CHECK_NA, CHECK_OK, CHECK_WRONG } ip_check;
  enum { FOUND_NONE=0, FOUND_ALL=1, FOUND_UNKNOWN=2, FOUND_ERROR=4 } ip_found;
# define anyAddress(x) ((x) & FOUND_ALL)
# define anyUnknown(x) ((x) & FOUND_UNKNOWN)
# define anyError(x)   ((x) & FOUND_ERROR)
#endif
  char *w;
  FTN_ADDR fa;
  FTN_NODE *pn;
  char szFTNAddr[FTN_ADDR_SZ + 1];
  int secure_NR, unsecure_NR;
  int secure_ND, unsecure_ND;
#ifdef BW_LIM
  int bw_send_unlim = 0, bw_recv_unlim = 0;
#endif

  s[sz] = 0;
  secure_NR = unsecure_NR = NO_NR;
  secure_ND = unsecure_ND = NO_ND;

  /* My hack is in using string with shared addresses
   * instead s
   */
  {
    char *ss, *ad = NULL;
    if (config->shares.first)
    {
      ad = add_shared_akas(s, config);
      if (ad)
      {
        ss = xalloc(strlen(s) + strlen(ad) + 1);
        strcpy(ss, s);
        strcat(ss, ad);
        s = ss;
        s[sz = sz + strlen(ad)] = 0;
      }
    }
    w = getwordx (s, 1, 0);
    if (w == 0)
    {
      if (ad)
      {
        free (s); free (ad);
      }
      Log (1, "all akas was removed as shared");
      return 0;
    }
    free (w);
  }

  /* set expected password on outgoing session
   * for drop remote AKAs with another passwords */
  if (state->to)
    memcpy(state->expected_pwd, 
           state->to->out_pwd ? state->to->out_pwd : "-", 
           sizeof(state->expected_pwd));

  for (i = 1; (w = getwordx (s, i, 0)) != 0; ++i)
  {
    if (!parse_ftnaddress (w, &fa, config->pDomains.first) || !is4D (&fa))
    {
      char *q = strquote (s, SQ_CNTRL);

      msg_send2 (state, M_ERR, "Bad address", 0);
      Log (1, "remote passed bad address: `%s'", q);
      free (w);
      free (q);
      return 0;
    }

    free (w);

#ifdef VAL_STYLE
    ip_check = CHECK_OFF;
#endif

    if (!fa.domain[0])
      strcpy (fa.domain, get_matched_domain(fa.z, config->pAddr, config->nAddr, config->pDomains.first));

    ftnaddress_to_str (szFTNAddr, &fa);
    pn = get_node_info(&fa, config);

    if (pn && pn->restrictIP
#ifdef HTTPS
        && (state->to == 0 || (!config->proxy[0] && !config->socks[0]))
#endif
        )
    { int i, rc;
#ifndef VAL_STYLE
      int ipok = 0;
#endif
      struct hostent *hp;
      struct in_addr defaddr;
      char **cp;
      char host[MAXHOSTNAMELEN + 1];       /* current host/port */
      unsigned short port;
      struct sockaddr_in sin;
      socklen_t si;

#ifdef VAL_STYLE
      ip_found = FOUND_NONE; ip_check = CHECK_NA;
#endif

      si = sizeof (struct sockaddr_in);
      if (getpeername (state->s, (struct sockaddr *) &sin, &si) == -1)
      {
        if (binkd_exit) return 0;
        Log (1, "Can't getpeername(): %s", TCPERR());
#ifndef VAL_STYLE
        ipok = 2;
#endif
      }

      for (i = 1; pn->hosts &&
           (rc = get_host_and_port(i, host, &port, pn->hosts, &pn->fa, config)) != -1; ++i)
      {
	if (rc == 0)
	{
	  Log (1, "%s: %i: error parsing host list", pn->hosts, i);
	  continue;
	}
	if (strcmp(host, "-") == 0)
	  continue;
	if (!isdigit (host[0]) ||
	    (defaddr.s_addr = inet_addr (host)) == INADDR_NONE)
	{
	  /* If not a raw ip address, try nameserver */
	  Log (5, "resolving `%s'...", host);
	  lockresolvsem();
          hp = gethostbyname (host);
	  if (hp == NULL || !hp->h_addr_list)
	  {
	    releaseresolvsem();
            if (h_errno == HOST_NOT_FOUND)
            {
	      Log (3, "%s: unknown host", host);
#ifdef VAL_STYLE
              ip_found |= FOUND_UNKNOWN;
#endif
            } else {
	      Log (3, "%s: DNS error", host);
#ifdef VAL_STYLE
              ip_found |= FOUND_ERROR;
#endif
            }
	    continue;
	  }
	  for (cp = hp->h_addr_list; cp && *cp; cp++)
#ifndef VAL_STYLE
	    if (((struct in_addr *) * cp)->s_addr == sin.sin_addr.s_addr)
	    {
	      ipok = 1;
	      break;
	    } else if (ipok == 0)
	      ipok = -1; /* resolved and not match */
#else
          {
            ip_found |= FOUND_ALL;
            if (((struct in_addr *) * cp)->s_addr == sin.sin_addr.s_addr) {
              ip_check = CHECK_OK; break;
            }
          }
#endif
	  releaseresolvsem();
	}
	else
	{
#ifndef VAL_STYLE
	  if (defaddr.s_addr == sin.sin_addr.s_addr)
	    ipok = 1;
	  else if (ipok == 0)
	    ipok = -1;  /* resolved and not match */
#else
          ip_found |= FOUND_ALL;
          if (defaddr.s_addr == sin.sin_addr.s_addr) ip_check = CHECK_OK;
#endif
	}
#ifndef VAL_STYLE
	if (ipok == 1)
#else
        if (ip_check == CHECK_OK)
#endif
	  break;
      }
#ifndef VAL_STYLE
      if (ipok == 1)
      { /* matched */
	ip_verified = 2;
      } else if (ipok<0 || pn->restrictIP == 2)
      { /* not matched or unresolvable with strict check */
	if (pn->pwd && strcmp(pn->pwd, "-") && state->to == 0)
	{
	  if (ipok == 0)
	    Log (1, "addr: %s (unresolvable)", szFTNAddr);
	  else
	    Log (1, "addr: %s (not from allowed remote address)", szFTNAddr);
	  msg_send2 (state, M_ERR, "Bad source IP", 0);
	  return 0;
	} else
	{ /* drop unsecure AKA with bad IP-addr */
	  if (ip_verified == 0)
	    ip_verified = -1;
	  if (ipok == 0)
	    Log(2, "Addr %s dropped - unresolvable IP", szFTNAddr);
	  else
	    Log(2, "Addr %s dropped - not from allowed IP", szFTNAddr);
	  continue;
	}
      }
#else
      if (ip_check != CHECK_OFF && ip_check != CHECK_OK) {
        if (
          /* val's -ip */
          (pn->restrictIP == ipRelaxed && ip_found == FOUND_ALL) ||
          /* gul's -ip */
          (pn->restrictIP == ipResolved && anyAddress(ip_found)) ||
          /* -ip=nounknown */
          (pn->restrictIP == ipNoUnknown && anyUnknown(ip_found)) ||
          /* -ip=noerror */
          (pn->restrictIP == ipNoError && anyError(ip_found)) ||
          /* -ip=strict */
          pn->restrictIP == ipStrict
        ) ip_check = CHECK_WRONG;
      }
      if (ip_check == CHECK_WRONG && !state->to && pn->pwd && strcmp(pn->pwd, "-")) {
        Log (1, "addr: %s (not from allowed remote IP, aborted)", szFTNAddr);
        msg_send2 (state, M_ERR, "Bad source IP", 0);
        return 0;
      }
      else if (ip_check == CHECK_WRONG) {
        Log (2, "addr: %s (not from allowed remote IP, disabled)", szFTNAddr);
        continue;
      }
#endif
    }
#ifndef VAL_STYLE
    else if (pn)
    { /* no check ip -> reset restrict */
      ip_verified = 1;
    }
#endif

    if (pn) state->listed_flag |= pn->listed;
    if (state->expected_pwd[0] && pn)
    {
      char *pwd = state->to ? pn->out_pwd : pn->pwd;
      if (!strcmp (state->expected_pwd, "-"))
      {
	memcpy(state->expected_pwd, pwd, sizeof (state->expected_pwd));
	state->MD_flag=pn->MD_flag;
      }
      else if (pwd && strcmp(pwd, "-") &&
               strcmp(state->expected_pwd, pwd))
      {
	if (state->to)
	  Log (2, "inconsistent pwd settings for this node, aka %s dropped", szFTNAddr);
	else
	{ /* drop incoming session with M_ERR "Bad password" */
	  Log (1, "inconsistent pwd settings for this node");
	  state->expected_pwd[0] = 0;
	}
	continue;
      }
    }

    if (bsy_add (&fa, F_BSY, config))
    {
#ifndef VAL_STYLE
      Log (2, "addr: %s", szFTNAddr);
#else
      char *s;
      if (ip_check == CHECK_OK) s = "remote IP ok";
      else if (ip_check == CHECK_OFF) s = "remote IP unchecked";
      else s = "remote IP can't be verified";
      Log (2, "addr: %s (%s)", szFTNAddr, s);
#endif
      if (state->nfa == 0)
	setproctitle ("%c %s [%s]",
		      state->to ? 'o' : 'i',
		      szFTNAddr,
		      state->peer_name);
      state->fa = xrealloc (state->fa, sizeof (FTN_ADDR) * ++state->nallfa);
      ++state->nfa;
      rel_grow_handles(1);
      for (j = state->nallfa - 1; j >= state->nfa; j--)
	memcpy (state->fa + j, state->fa + j - 1, sizeof (FTN_ADDR));
      memcpy (state->fa + state->nfa - 1, &fa, sizeof (FTN_ADDR));
      if (state->to &&
	  !ftnaddress_cmp (state->fa + state->nfa - 1, &state->to->fa))
      {
	main_AKA_ok = 1;
      }
#ifdef BW_LIM
      if (pn && pn->listed) {
        if (pn->bw_send == 0) bw_send_unlim = 1;
        else if (pn->bw_send < 0 
                 && (!state->bw_send_rel 
                 || (unsigned long)(-pn->bw_send) < state->bw_send_rel)) 
          state->bw_send_rel = -pn->bw_send;
        else if (pn->bw_send > 0
                 && (!state->bw_send_abs
                 || (unsigned long)pn->bw_send < state->bw_send_abs))
          state->bw_send_abs = pn->bw_send;

        if (pn->bw_recv == 0) bw_recv_unlim = 1;
        else if (pn->bw_recv < 0 
                 && (!state->bw_recv_rel 
                 || (unsigned long)(-pn->bw_recv) < state->bw_recv_rel)) 
          state->bw_recv_rel = -pn->bw_recv;
        else if (pn->bw_recv > 0
                 && (!state->bw_recv_abs
                 || (unsigned long)pn->bw_recv < state->bw_recv_abs))
          state->bw_recv_abs = pn->bw_recv;
      }
#endif
    }
    else
    {
      Log (2, "addr: %s (n/a or busy)", szFTNAddr);
#if 1
      if (pn && pn->pwd && strcmp(pn->pwd, "-") && state->to == 0)
      {
	Log (1, "Secure AKA %s busy, drop the session", szFTNAddr);
	msg_sendf (state, M_BSY, "Secure AKA %s busy", szFTNAddr);
	return 0;
      }
#endif
      state->fa = xrealloc (state->fa, sizeof (FTN_ADDR) * ++state->nallfa);
      memcpy (state->fa + state->nallfa - 1, &fa, sizeof (FTN_ADDR));
    }

    if (!state->to && pn)
    { if (pn->ND_flag)
      {
	if (pn->pwd && strcmp(pn->pwd, "-"))
	{
	  secure_ND = THEY_ND;
	  secure_NR = WANT_NR;
	}
	else
	{
	  unsecure_ND = THEY_ND;
	  unsecure_NR = WANT_NR;
	}
      }
      else if (pn->NR_flag)
      {
	if (pn->pwd && strcmp(pn->pwd, "-"))
	  secure_NR = WANT_NR;
	else
	  unsecure_NR = WANT_NR;
      }
    }
  }
  if (state->nfa == 0)
  {
    Log (1, "no AKAs in common domains or all AKAs are busy");
    msg_send2 (state, M_BSY, "No AKAs in common domains or all AKAs are busy", 0);
    return 0;
  }
  if (state->to != 0 && main_AKA_ok == 0)
  {
    ftnaddress_to_str (szFTNAddr, &state->to->fa);
    Log (1, "called %s, but remote has no such AKA", szFTNAddr);
    bad_try (&state->to->fa, "Remote has no needed AKA", BAD_AKA, config);
    return 0;
  }
#ifndef VAL_STYLE
  if (ip_verified < 0)
  { /* strict IP check and no address resolved */
    Log (1, "Remote IP check failed");
    msg_send2 (state, M_ERR, "Bad remote IP", 0);
    return 0;
  }
  else if (ip_verified == 2)
    Log (4, "Remote IP matched");
  else if (state->to == 0)
    Log (5, "Remote IP not checked");
#endif

  if (!state->to)
  {
    if (state->expected_pwd[0] && strcmp(state->expected_pwd, "-"))
    {
      state->ND_flag |= secure_ND;
      state->NR_flag |= secure_NR;
    }
    else
    {
      state->ND_flag |= unsecure_ND;
      state->NR_flag |= unsecure_NR;
    }
  }

#ifdef BW_LIM
  pn = NULL;
  {
    FTN_ADDR dfa = {"defnode", 0, 0, 0, 0};
    pn = get_node_info(&dfa, config);
  }
  if (bw_send_unlim) state->bw_send_abs = state->bw_send_rel = 0;
  /* use defnode's -bw settings if no explicit */
  else if (!state->bw_send_abs && !state->bw_send_rel && pn) {
    if (pn->bw_send >= 0) state->bw_send_abs = pn->bw_send;
    else state->bw_send_rel = -pn->bw_send;
  }
  if (state->bw_send_abs || state->bw_send_rel)
    Log (7, "Session send rate limit is %s cps or %d%%", 
            describe_rate(state->bw_send_abs), state->bw_send_rel);

  if (bw_recv_unlim) state->bw_recv_abs = state->bw_recv_rel = 0;
  /* use defnode's -bw settings if no explicit */
  else if (!state->bw_recv_abs && !state->bw_recv_rel && pn) {
    if (pn->bw_recv >= 0) state->bw_recv_abs = pn->bw_recv;
    else state->bw_recv_rel = -pn->bw_recv;
  }
  if (state->bw_recv_abs || state->bw_recv_rel)
    Log (7, "Session recv rate limit is %s cps or %d%%", 
            describe_rate(state->bw_recv_abs), state->bw_recv_rel);
#endif

  if (state->to)
  {
    do_prescan (state, config);
    if(state->MD_challenge)
    {
      char *tp=MD_buildDigest(state->to->out_pwd ? state->to->out_pwd : "-", state->MD_challenge);
      if(!tp)
      {
        Log(2, "Unable to build MD5 digest");
        bad_try (&state->to->fa, "Unable to build MD5 digest", BAD_AUTH, config);
        return 0;
      }
      msg_send2 (state, M_PWD, tp, 0);
      state->MD_flag=1;
      free(tp);
    }
    else if ((state->to->MD_flag == 1) && !no_MD5) /* We do not want to talk without MD5 */
    {
      Log(2, "CRAM-MD5 is not supported by remote");
      bad_try (&state->to->fa, "CRAM-MD5 is not supported by remote", BAD_AUTH, config);
      return 0;
    }
    else
      msg_send2 (state, M_PWD, state->to->out_pwd ? state->to->out_pwd : "-", 0);
  }
  return 1;
}

static char *select_inbound (FTN_ADDR *fa, int secure_flag, BINKD_CONFIG *config)
{
  FTN_NODE *node;
  char *p;

  node = get_node_info(fa, config);
  p = ((node && node->ibox) ? node->ibox :
	  (secure_flag == P_SECURE ? config->inbound : config->inbound_nonsecure));
  return p;
}

static int complete_login (STATE *state, BINKD_CONFIG *config)
{
  state->inbound = select_inbound (state->fa, state->state, config);
  if (OK_SEND_FILES (state, config) && state->q == NULL)
    state->q = q_scan_addrs (0, state->fa, state->nfa, state->to ? 1 : 0, config);
  state->msgs_in_batch = 0;	       /* Forget about login msgs */
  if (state->state == P_SECURE)
    Log (2, "pwd protected session (%s)",
         (state->MD_flag == 1) ? "MD5" : "plain text");
  if (state->ND_flag & WE_ND)
  { state->NR_flag |= WE_NR;
    Log (3, "we are in ND mode");
  }
  if (state->ND_flag & THEY_ND)
    Log (3, "remote is in ND mode");
  else if (state->NR_flag == WE_NR)
    Log (3, "we are in NR mode");
  if (state->state != P_SECURE)
    state->crypt_flag = NO_CRYPT;
  else if (state->crypt_flag == (WE_CRYPT|THEY_CRYPT) && !state->MD_flag)
  { state->crypt_flag = NO_CRYPT;
    Log (3, "Crypt allowed only with MD5 authorization");
  }
  else if (state->crypt_flag == (WE_CRYPT|THEY_CRYPT))
  { char *p;
    state->crypt_flag = YES_CRYPT;
    Log (3, "session in CRYPT mode");
    if (state->to)
    { init_keys(state->keys_out, state->to->out_pwd ? state->to->out_pwd : "-");
      init_keys(state->keys_in,  "-");
      for (p=state->to->out_pwd ? state->to->out_pwd : "-"; *p; p++)
        update_keys(state->keys_in, (int)*p);
    } else
    { init_keys(state->keys_in, state->expected_pwd);
      init_keys(state->keys_out,  "-");
      for (p=state->expected_pwd; *p; p++)
        update_keys(state->keys_out, (int)*p);
    }
  }
  if (state->crypt_flag!=YES_CRYPT) state->crypt_flag=NO_CRYPT;
#if defined(WITH_ZLIB) || defined(WITH_BZLIB2)
  if (state->z_cansend && !state->extcmd)
  {
    Log(2, "Remote does not support EXTCMD, turn compression off");
    state->z_cansend = 0;
  }
#endif
#ifdef WITH_PERL
  {
    char *s = perl_after_handshake(state);
    if (s && *s) {
      Log (1, "aborted by Perl after_handshake(): %s", s);
      msg_send2 (state, M_ERR, s, 0);
      return 0;
    }
  }
#endif
  return 1;
}

static int PWD (STATE *state, char *pwd, int sz, BINKD_CONFIG *config)
{
  int bad_pwd=STRNICMP(pwd, "CRAM-", 5);
  int no_password=!strcmp (state->expected_pwd, "-");
  char *szOpt;

  UNUSED_ARG(sz);

  if (state->to)
  { Log (1, "unexpected password from the remote on outgoing call: `%s'", pwd);
    return 1;
  }
  if ((no_password)&&(bad_pwd))
  {
    do_prescan (state, config);
    state->state = P_NONSECURE;
    if (strcmp (pwd, "-"))
      Log (1, "unexpected password from the remote: `%s'", pwd);
  }
  else
  {
    if((state->MD_flag == 1) || ((!bad_pwd) && (state->MD_challenge)))
    {
      char *sp;
      if((bad_pwd)&&(state->MD_flag))
      {
        msg_send2(state, M_ERR, "You must support MD5", 0);
        Log(1, "Caller does not support MD5");
        return 0;
      }
      if((sp=MD_buildDigest(state->expected_pwd, state->MD_challenge))!=NULL)
      {
        if((bad_pwd=STRICMP(sp, pwd))==0) state->MD_flag=1;
	free(sp);
        sp=NULL;
      }
      else {
        Log(2, "Unable to build Digest");
        bad_pwd=1;
      }
    }
    else bad_pwd=(state->expected_pwd[0] == 0 || strcmp (state->expected_pwd, pwd));

    if ((bad_pwd)&&(!no_password)) /* I don't check password if we do not need one */
    {
      msg_send2 (state, M_ERR, "Bad password", 0);
      Log (1, "`%s': incorrect password", pwd);
      return 0;
    }
    else
    {
      if(no_password)
      {
        state->state = P_NONSECURE;
        do_prescan (state, config);
        if(bad_pwd) {
          Log (1, "unexpected password digest from the remote");
          state->state_ext = P_WE_NONSECURE;
        }
      }
      else
      {
	state->state = P_SECURE;
        do_prescan (state, config);
      }
    }
  }

  if (state->state != P_SECURE)
    state->crypt_flag = NO_CRYPT;
  else if (state->crypt_flag == (THEY_CRYPT | WE_CRYPT) && !state->MD_flag)
  { state->crypt_flag = NO_CRYPT;
    Log (4, "Crypt allowed only with MD5 authorization");
  }

  if ((state->ND_flag & WE_ND) && (state->ND_flag & CAN_NDA) == 0)
    state->ND_flag |= THEY_ND;
  if ((state->ND_flag & WE_ND) == 0 && (state->ND_flag & CAN_NDA) == 0)
    state->ND_flag &= ~THEY_ND;

  if ((state->NR_flag & WANT_NR) &&
      !(state->ND_flag & CAN_NDA) && !(state->ND_flag & WE_ND))
  { /* workaround bug of old binkd */
    /* force symmetric NR-mode with it */
#if 1
    if (state->major * 100 + state->minor > 100)
      state->NR_flag |= WE_NR;
    else
#endif
      state->NR_flag &= ~WANT_NR;
  }

  szOpt = xstrdup(" EXTCMD");
  if (state->NR_flag & WANT_NR) xstrcat(&szOpt, " NR");
  if (state->ND_flag & THEY_ND) xstrcat(&szOpt, " ND");
  if ((!(state->ND_flag & WE_ND)) != (!(state->ND_flag & THEY_ND))) xstrcat(&szOpt, " NDA");
  if (state->crypt_flag == (WE_CRYPT | THEY_CRYPT)) xstrcat(&szOpt, " CRYPT");
#ifdef WITH_ZLIB
  if (state->z_canrecv & 1) xstrcat(&szOpt, " GZ");
#endif
#ifdef WITH_BZLIB2
  if (state->z_canrecv & 2) xstrcat(&szOpt, " BZ2");
#endif
  msg_send2(state, M_NUL, "OPT", szOpt);
  xfree(szOpt);
  msg_send2 (state, M_OK, state->state==P_SECURE ? "secure" : "non-secure", 0);
  return complete_login (state, config);
}

static int OK (STATE *state, char *buf, int sz, BINKD_CONFIG *config)
{
  char *w;
  int i;
  UNUSED_ARG(sz);

  if (!state->to) return 0;
  state->state = state->to->out_pwd && strcmp(state->to->out_pwd, "-") != 0 ? P_SECURE : P_NONSECURE;
  for (i = 1; (w = getwordx (buf, i, 0)) != 0; ++i)
  {
    if (state->state == P_SECURE && strcmp(w, "non-secure") == 0)
    {
      state->crypt_flag=NO_CRYPT; /* some development binkd versions send OPT CRYPT with unsecure session */
      Log (1, "Warning: remote set UNSECURE session");
      state->state_ext = P_REMOTE_NONSECURE;
    }
    free(w);
  }
  if (state->ND_flag == WE_ND || state->ND_flag == THEY_ND)
    state->ND_flag = 0; /* remote does not support asymmetric ND-mode */
  return complete_login (state, config);
}

/* val: checks file against skip rules */
struct skipchain *skip_test(STATE *state, BINKD_CONFIG *config)
{
  struct skipchain *ps;
  addrtype amask = 0;

  amask |= (state->listed_flag) ? A_LST : A_UNLST;
  amask |= (state->state == P_SECURE) ? A_PROT : A_UNPROT;
  for (ps = config->skipmask.first; ps; ps = ps->next)
  {
    if ( (ps->atype & amask) && pmatch_ncase(ps->mask, state->in.netname) )
    {
      if (ps->size >=0 && state->in.size >= ps->size)
        return ps;
      return NULL;
    }
  }
  return NULL;
}

#ifdef BW_LIM
static void setup_send_rate_limit (STATE *state, BINKD_CONFIG *config)
{
  struct ratechain *ps;
  addrtype amask = 0;
  int rlim = -100;

  amask |= (state->listed_flag) ? A_LST : A_UNLST;
  amask |= (state->state == P_SECURE) ? A_PROT : A_UNPROT;
  for (ps = config->rates.first; ps; ps = ps->next)
  {
    if ( (ps->atype & amask) && pmatch_ncase(ps->mask, state->out.netname) )
    {
      Log (7, "%s matches rate limit mask %s", state->out.netname, ps->mask);
      rlim = ps->rate;
      break;
    }
  }
  /* if mask is set to unlim rate, set to unlim */
  if (rlim == 0) state->bw_send = 0;
  else {
    /* if mask set to specific rate, adjust to remote percent rate */
    if (rlim > 0) 
      state->bw_send = state->bw_send_rel ? rlim * state->bw_send_rel / 100 : rlim;
    /* if mask set to relative rate, adjust node absolute rate by it */
    else 
      state->bw_send = state->bw_send_abs ? state->bw_send_abs * (-rlim) / 100 : 0;
  }
  if (state->bw_send)
    Log (3, "rate limit for %s is %d cps", state->out.netname, state->bw_send);
  else
    Log (5, "rate for %s is unlimited", state->out.netname);
}

static void setup_recv_rate_limit (STATE *state, BINKD_CONFIG *config)
{
  struct ratechain *ps;
  addrtype amask = 0;
  int rlim = -100;

  amask |= (state->listed_flag) ? A_LST : A_UNLST;
  amask |= (state->state == P_SECURE) ? A_PROT : A_UNPROT;
  for (ps = config->rates.first; ps; ps = ps->next)
  {
    if ( (ps->atype & amask) && pmatch_ncase(ps->mask, state->in.netname) )
    {
      Log (7, "%s matches rate limit mask %s", state->in.netname, ps->mask);
      rlim = ps->rate;
      break;
    }
  }
  /* if mask is set to unlim rate, set to unlim */
  if (rlim == 0) state->bw_recv = 0;
  else {
    /* if mask set to specific rate, adjust to remote percent rate */
    if (rlim > 0) 
      state->bw_recv = state->bw_recv_rel ? rlim * state->bw_recv_rel / 100 : rlim;
    /* if mask set to relative rate, adjust node absolute rate by it */
    else 
      state->bw_recv = state->bw_recv_abs ? state->bw_recv_abs * (-rlim) / 100 : 0;
  }
  if (state->bw_recv)
    Log (3, "rate limit for %s is %d cps", state->in.netname, state->bw_recv);
  else
    Log (5, "rate for %s is unlimited", state->in.netname);
}
#endif

/*
 * Handles M_FILE msg from the remote
 * M_FILE args: "%s %lu %lu %lu", filename, size, time, offset
 * M_FILE ext.: "%s %lu %lu %lu %s...", space-separated params
 *     currently, only GZ and BZ2 parameters supported
 */
static int start_file_recv (STATE *state, char *args, int sz, BINKD_CONFIG *config)
{
  int argc = 4;
  char *argv[4], *w;
  off_t offset;
  UNUSED_ARG(sz);

  if ((args = parse_msg_args (argc, argv, args, "M_FILE", state)) != NULL)
  {
    /* They request us for offset (M_FILE "name size time -1") */
    int off_req = 0;

#if defined(WITH_ZLIB) || defined(WITH_BZLIB2)
    if (state->z_recv && state->z_idata)
    {
      decompress_deinit(state->z_recv, state->z_idata);
      state->z_idata = NULL;
    }
    state->z_recv = 0;
    state->z_isize = state->z_cisize = 0;
#endif
    if (state->in.f &&		       /* Already receiving smthing */
	strcmp (argv[0], state->in.netname))	/* ...a file with another *
						 * name! */
    {
      close_partial (state, config);
    }
    if ((state->ND_flag & THEY_ND) && state->in_complete.netname[0])
    { /* rename complete received file to its true form */
      char realname[MAXPATHLEN + 1];
      char szAddr[FTN_ADDR_SZ + 1];

      if (inb_done (&(state->in_complete), realname, state, config) == 0)
        return 0; /* error, drop session */
      /* val: check for *.req if got M_NUL FREQ */
      if (state->delay_EOB && isreq(state->in_complete.netname))
        state->delay_EOB--;
      /* val: /check */
      if (*realname)
      {
        /* Set flags */
        if(evt_test(&(state->evt_queue), realname, config->evt_flags.first))
          state->q = evt_run(&(state->evt_queue), state->q, realname, state->fa,
	         state->nfa, state->state == P_SECURE, state->listed_flag,
                 state->peer_name, state, config);
        /* We will run external programs using this list */
        add_to_rcvdlist (&state->rcvdlist, &state->n_rcvdlist, realname);
      }
      ftnaddress_to_str (szAddr, state->fa);
      state->bytes_rcvd += state->in_complete.size;
      ++state->files_rcvd;
      Log (2, "rcvd: %s (%" PRIuMAX ", %.2f CPS, %s)",
	   state->in_complete.netname,
	   (uintmax_t) state->in_complete.size,
	   (double) (state->in_complete.size) /
	   (safe_time() == state->in_complete.start ?
	                1 : (safe_time() - state->in_complete.start)), szAddr);
      TF_ZERO (&state->in_complete);
    }
    if (state->in.f == 0)
    { char *errmesg=NULL;

      state->in.start = safe_time();
      strnzcpy (state->in.netname, argv[0], MAX_NETNAME);
      state->in.size = atol (argv[1]);
      errno=0;
      state->in.time = safe_atol (argv[2], &errmesg);
      if(errmesg){
          Log ( 1, "File time parsing error: %s! (M_FILE \"%s %s %s %s\")", errmesg, argv[0], argv[1], argv[0], argv[2], argv[3] );
      }
    }
    offset = (off_t) strtoumax (argv[3], NULL, 10);
    if (!strcmp (argv[3], "-1"))
    {
      off_req = 1;
      Log (6, "got offset request for %s", state->in.netname);
      if ((state->NR_flag & THEY_NR) == 0)
      {
	state->NR_flag |= THEY_NR;
	if ((state->ND_flag & THEY_ND) == 0)
	  Log (3, "remote is in NR mode");
      }
    }

    if (state->in.f == 0)
    {
      char realname[MAXPATHLEN + 1];
      struct skipchain *mask;
#ifdef WITH_PERL
      int rc;

      if ((rc = perl_before_recv(state, offset)) > 0) {
	Log (1, "skipping %s (%sdestructive, %" PRIuMAX " byte(s), by Perl before_recv)",
	     state->in.netname, rc == SKIP_D ? "" : "non-",
	     (uintmax_t) state->in.size);
	msg_sendf (state, (t_msg)(rc == SKIP_D ? M_GOT : M_SKIP),
		   "%s %" PRIuMAX " %" PRIuMAX,
		   state->in.netname,
		   (uintmax_t) state->in.size,
		   (uintmax_t) state->in.time);
	return 1;
      }
#endif
      /* val: skip check */
      if ((mask = skip_test(state, config)) != NULL) {
	Log (1, "skipping %s (%sdestructive, %" PRIuMAX " byte(s), mask %s)",
	     state->in.netname, mask->destr ? "" : "non-",
	     (uintmax_t) state->in.size, mask->mask);
	msg_sendf (state, (t_msg)(mask->destr ? M_GOT : M_SKIP),
		   "%s %" PRIuMAX " %" PRIuMAX,
		   state->in.netname,
		   (uintmax_t) state->in.size,
		   (uintmax_t) state->in.time);
	return 1;
      }
      /* val: /skip check */

      if (inb_test (state->in.netname, state->in.size,
		    state->in.time, state->inbound, realname))
      {
	Log (2, "already have %s (%s, %" PRIuMAX " byte(s))",
	     state->in.netname, realname, (uintmax_t) state->in.size);
	msg_sendf (state, M_GOT, "%s %" PRIuMAX " %" PRIuMAX,
		   state->in.netname,
		   (uintmax_t) state->in.size,
		   (uintmax_t) state->in.time);
	return 1;
      }
      else if (!state->skip_all_flag)
      {
	if ((state->in.f = inb_fopen (state, config)) == 0)
	{
	  state->skip_all_flag = 1;
	}
      }

#if defined(DOS) && defined(__MSC__)
      if (!state->skip_all_flag &&
          (state->n_rcvdlist+1ul) * sizeof(RCVDLIST) > 64535ul)
      {
        Log (1, "ReceivedList has reached max size 64K");
        state->skip_all_flag = 1;
      }
#endif

      if (state->skip_all_flag)
      {
	Log (2, "skipping %s (non-destructive)", state->in.netname);
	msg_sendf (state, M_SKIP, "%s %" PRIuMAX " %" PRIuMAX,
		   state->in.netname,
		   (uintmax_t) state->in.size,
		   (uintmax_t) state->in.time);
	if (state->in.f)
	  fclose (state->in.f);
	TF_ZERO (&state->in);
	return 1;
      }
    }

    if (off_req || offset != ftello (state->in.f))
    {
      Log (2, "have %" PRIuMAX " byte(s) of %s",
	   (uintmax_t) ftello (state->in.f), state->in.netname);
      msg_sendf (state, M_GET, "%s %" PRIuMAX " %" PRIuMAX " %" PRIuMAX,
		 state->in.netname,
		 (uintmax_t) state->in.size, (uintmax_t) state->in.time,
		 (uintmax_t) ftello (state->in.f));
      ++state->GET_FILE_balance;
      fclose (state->in.f);
      TF_ZERO (&state->in);
      return 1;
    }
    else if (offset != 0 || (state->NR_flag & THEY_NR))
    {
      --state->GET_FILE_balance;
    }

    Log (3, "receiving %s (%" PRIuMAX " byte(s), off %" PRIuMAX ")",
	 state->in.netname, (uintmax_t) (state->in.size), (uintmax_t) offset);
#ifdef BW_LIM
    setup_recv_rate_limit(state, config);
#endif

    for (argc = 1; (w = getwordx (args, argc, 0)) != 0; ++argc)
    {
      if (w[0] == '\0') ;
#ifdef WITH_ZLIB
      else if (strcmp(w, "GZ") == 0)
      {
	if (state->z_recv == 0)
          Log (4, "gzip mode is on for %s", state->in.netname);
        state->z_recv |= 1;
      }
#endif
#ifdef WITH_BZLIB2
      else if (strcmp(w, "BZ2") == 0)
      {
	if (state->z_recv == 0)
          Log (4, "bzip2 mode is on for %s", state->in.netname);
        state->z_recv |= 2;
      }
#endif
      else
        Log (4, "Unknown option %s for %s ignored", w, state->in.netname);
      free(w);
    }

#if defined(WITH_ZLIB) && defined(WITH_BZLIB2)
    if (state->z_recv == 3) {
      Log (1, "Both GZ and BZ2 extras are specified for %s", state->in.netname);
      msg_send2 (state, M_ERR, "Can't handle GZ and BZ2 at the same time for ", state->in.netname);
      return 0;
    }
#endif

    if (fseeko (state->in.f, offset, SEEK_SET) == -1)
    {
      Log (1, "fseek: %s", strerror (errno));
      return 0;
    }
    else
      return 1;
  }
  else
    return 0;
}

static int ND_set_status(char *status, FTN_ADDR *fa, STATE *state, BINKD_CONFIG *config)
{
  char buf[MAXPATHLEN+1];
  FILE *f;
  int  rc;

  UNUSED_ARG(state);

  if (fa->z==-1)
  { Log(8, "ND_set_status: unknown address for '%s'", status);
    return 0;
  }
  ftnaddress_to_filename (buf, fa, config);
  if (*buf=='\0') return 0;
  strnzcat(buf, ".stc", sizeof(buf));
  if (!status || !*status)
  {
    if (unlink(buf) == 0)
    { Log(5, "Clean link status for %u:%u/%u.%u",
          fa->z, fa->net, fa->node, fa->p);
      return 1;
    }
    rc = errno;
    if (access(buf, F_OK) == 0)
    { Log(1, "Can't unlink %s: %s!\n", buf, strerror(rc));
      return 0;
    }
    return 1;
  }
  else
  {
    Log(5, "Set link status for %u:%u/%u.%u to '%s'",
        fa->z, fa->net, fa->node, fa->p, status);
    f=fopen(buf, "w");
    if (f==NULL)
    { Log(1, "Can't write to %s: %s", buf, strerror(errno));
      return 0;
    }
    rc=1;
    if (fputs(status, f)==EOF)
      rc=0;
    if (fclose(f)==EOF)
      rc=0;
    return rc;
  }
}

#if defined(WITH_ZLIB) || defined(WITH_BZLIB2)
static void z_send_init(STATE *state, BINKD_CONFIG *config, char **extra)
{
  int rc;

  *extra = "";
  if (state->z_cansend && state->out.size >= config->zminsize
      && zrule_test(ZRULE_ALLOW, state->out.netname, config->zrules.first)) {
#ifdef WITH_BZLIB2
    if (!state->z_send && (state->z_cansend & 2)) {
      *extra = " BZ2"; state->z_send = 2;
      Log (4, "bzip2 mode is on for %s", state->out.netname);
    }
#endif
#ifdef WITH_ZLIB
    if (!state->z_send && (state->z_cansend & 1)) {
      *extra = " GZ"; state->z_send = 1;
      Log (4, "gzip mode is on for %s", state->out.netname);
    }
#endif
    if (state->z_send)
      if ((rc = compress_init(state->z_send, config->zlevel, &state->z_odata)))
      {
        Log (1, "compress_init failed (rc=%d), send uncompressed file %s",
             rc, state->out.netname);
        *extra = "";
        state->z_send = 0;
      }
  }
}

static void z_send_stop(STATE *state)
{
  if (state->z_send && state->z_odata)
  { compress_abort(state->z_send, state->z_odata);
    state->z_odata = NULL;
    state->z_oleft = 0;
  }
  state->z_send = 0;
  state->z_osize = state->z_cosize = 0;
}
#else
#define z_send_init(state, config, extra)	(*(extra) = "")
#define z_send_stop(state)
#endif

/*
 * M_GET message from the remote: Resend file from offset
 * M_GET args: "%s %lu %lu %lu", filename, size, time, offset
 */
static int GET (STATE *state, char *args, int sz, BINKD_CONFIG *config)
{
  int argc = 4;
  char *argv[4];
  char *extra;
  int i, rc = 0, nz = 0;
  off_t offset, fsize=0;
  time_t ftime=0;

  UNUSED_ARG(sz);

  if ((args = parse_msg_args (argc, argv, args, "M_GET", state)) != NULL)
  { {char *errmesg = NULL;
      fsize = atol (argv[1]);
      ftime = safe_atol (argv[2], &errmesg);
      if(errmesg){
        Log ( 1, "File time parsing error: %s! (M_GET \"%s %s %s %s\")", errmesg, argv[0], argv[1], argv[0], argv[2], argv[3] );
      }
    }
    /* Check if the file was already sent */
    for (i = 0; i < state->n_sent_fls; ++i)
    {
      if (!tfile_cmp (state->sent_fls + i, argv[0], fsize, ftime))
      {
	if (state->out.f)
	{
	  TFILE tfile_buf;
	  fclose (state->out.f);
	  state->out.f = NULL;
	  memcpy (&tfile_buf, &state->out, sizeof (TFILE));
	  memcpy (&state->out, state->sent_fls + i, sizeof (TFILE));
	  memcpy (state->sent_fls + i, &tfile_buf, sizeof (TFILE));
	}
	else
	{
	  memcpy (&state->out, state->sent_fls + i, sizeof (TFILE));
	  remove_from_sent_files_queue (state, i);
	}
	if ((state->out.f = fopen (state->out.path, "rb")) == 0)
	{
	  Log (1, "GET: %s: %s", state->out.path, strerror (errno));
	  TF_ZERO (&state->out);
	}
	break;
      }
    }

    if ((state->out.f || state->off_req_sent) &&
         !tfile_cmp (&state->out, argv[0], fsize, ftime))
    {all_flag &&
       e, ftWITH_BZLIB2)  TF_ZTsecuor (iatus fo
	strc 1;
	}
  T speic sfremote", T_FILE_balance;
o
	stg_sendf (state, M_GELE_b"%s %" PRIuMAX " %" PRIuMAX " %" PRIuMAX,
		 st tate->out.netname, cointmax_t) state->int.size >		   (uintmax_t) state->int.sime, statoumalrgv[3], NULL, 10);

	if (statoumax (rgv[3], NULL, 10);
= (WEntmax_t) state->int.size >&
	  !f  tate->ND_flag & WE_ND))
  
	  state->skid_stf (T1;
	  elate->skwaings _r (OT : 1;
	  elg(5, "SeWaings or (iGOT, ;
	  state->exf_req_sent)  0;
	}
return rc;
  
	else
	{
/* resoest form offset
  0 -ile agaeady receme, d/
	  Lo_set_status(ch""&state->out, ., state->config);
  F_ZERO (state->out);
	}    }
      else if (!s(fset = (off_t) srtoumax (argv[3], NULL, 10);
> 64ate->int.size >&
          /*   fsizko (state->int, .,offset, SEEK_SET) == -1)
    {
{
	Log (1, "SeT: %sror (ezko g %s (% %s:PRIuMAX " %:s",
	   (u rgv[0], fsintmax_t) offset);strerror (errno));
	    T sh AKe file wad BZop session */
  	lose(f)ate->out.f);
	  ate->out.f);ULL;

 	 sh Atate->out.path, "rme();LL)
 
	retc 0;
      }
  }
  else
      {
	stg (2, "skidif
 %s (%rm of PRIuMAX,
	rgv[0], fsintmax_t) offset);
	rer (argc = 1; (w tra = ""twordx (args, argc, 0)) != 0; ++argc)
  
	  if (iprcmp(w,tra ="GZ") == 0)
| strcmp (,tra ="GZ2") == 0)
  	  else if (iprcmp (,tra ="GZN) == 0)
 z = 0;
	  else if (iptra =])
  	  Log (4, "Unknown option %s for %s ignored", w,tra ="Ggv[0], 
	  stee(w)tra) =  
	elsend_stop(state)
#	if (!isnz)_send_init(state, config, ex&tra) =  
g_sendf (state, M_GELE_b"%s %" PRIuMAX " %" PRIuMAX " %" PRIuMAX,
%s %"		 st tate->out.netname, c	   (uintmax_t) state->int.size >		   (uintmax_t) state->int.sime, s	   (uintmax_t) stfset);sttra) =  
rc 1;
	}    }
    }
    else b     Log (1, "unexpected paGET \"r %s", stgv[0], 
	   Lo_set_status(ch""&state->ou_sear, state->config);
    state->st_sear, .z=-1    if (state->to_flag & WE_ND)
  { {
      state->crwaings _r (OT : 1;0      Log ((9"unD't chwaings or (iGOT, ;
	   }
    state->z_f_req_sent)  0;
	}   return rc;
  }
}
else
    return 0;
}

st
 * M_GEIP, Resete addskusinT spep chfile w. Oy GZfile wirrently, nt * M_a) nsferill rubepep cped!* M* M_GEIP, rgs: "%s %lu %lu % filename, size, time, */
static int GEIP, rTATE *state, char *args, int sz, BINKD_CONFIG *config)
{
  innsistnt argc = 4;3  char *argv[4]3]  int no_  time_t ftime=0;

 off_t ofsize=0;
   UNUSED_ARG(sz);

  if ((arse_msg_args (argc, argv, args, "M_GEIP,  state)) ! {
    Lo      char *sprmesg=NULL;

     fsize = atff_t) srtoumax (argv[3]1 NULL, 10);
    ifftime = safe_atol (argv[2], &errmesg);
      if(e rrmesg){
     {
	stg (2,, "File time parsing error: %s! (M_GEIP, r%s %s %s %)", errmesg, argv[0], argv[1], argv[0], argv[2], ;
      }
    }
    /*r (arn 0; i n state->n_sent_fls; ++i)n    {
      if (!tfile_cmp (state->sent_fls + i,nargv[0], fsize, ftime))
      {
	ifate->rcv_ep cpedlag = 1;
	}
g (2, "sk %sep cpedy remote", BAate->sent_fls +[n]etname);
	msgcpy (&state->ou_sear, st&ate->sent_fls +[n]e, sizeof (TN_ADDR));
  	move_from_sent_files_queue (state, i)n
      }
    }
    /* (!tfile_cmp (sttate->out, argv[0], fsize, ftime))
    {all_flag ate->rcv_ep cpedlag = 1;
	}    if (state->skt.f)
	{
lose (state->out.f);
	 }
  else
      {
	stg (2, "Can'tt supp chND-atus, f)ssion */opped", =  
g_sendf 2tate, M_ERR, "Can'tt supp chND-atus,  0);
	  turn 0;
      }
      ifg (2, "sk %sep cpedy remote", BAate->set.netname);
        _ZERO (&state->out);
	}  }
      _set_status(ch""&state->ou_sear, state->config);
    state->st_sear, .z=-1    if (sttate->ND_flag & WE_ND) == (state->NR_flag & TH_NR)
   { {
      state->crwaings _r (OT : 1;ate->z_f_req_sent)  0;
	}    Log ((9"unD't chwaings or (iGOT, ;
	   }
    stturn 1;
  }
  else
    return 0;
}

st
 * M_GETOTrgs: "%s %lu %lu % filename, size, time, */
static int GETOTrTATE *state, char *args, int sz, BINKD_CONFIG *config)
{
  innsistnt argc = 4;3  char *argv[4]3]  int no_,c=1;
    ar *status,  NULL;
    me_t ftime=0;

 off_t ofsize=0;
  char *sprmesg=N NULL;
    ar *staavedlgs,    UNUSED_ARG(sz);

  ifaavedlgs,  xstrdup(" gs, 

  if ((arse_msg_args (argc, argv, args, "M_GET, ;state)) ! {
    Lo ((state->NR_flag & WANER) &&
 (state->ND_flag & WE_ND))
  {     _set_status(ch""&state->ou_sear, state->config);
    stse
      {
atus,  NUaavedlgs,     fsize = atff_t) s rtoumax (argv[3]1 NULL, 10);
    ifrno)) 0;
	}    ime = safe_atol (argv[2], &errmesg);
      (e rrmesg){
           Log (1,, "File time parsing error: %s! (M_GETOTr%s %s %s %)", errmesg, argv[0], argv[1], argv[0], argv[2], ;
          /* (!tfile_cmp (sttate->out, argv[0], fsize, ftime))
    {all_flag g (2, "rcvete addeady havess", state->out.netname);
    }
if (state->skt.f)
	{    {
	stlose (state->out.f);
	  ate->out.f = NULL;
	     }
      msgcpy(sttate->ou_sear, st&ate->set, ., staeof (Tate->set, ., ;
      if (state->to_flag & WE_ND)
  { {
  Log (7, "SessND_sear, % %s:%u/%u.%u",
          fa state->st_sear, .z,tate->st_sear, .net,tate->st_sear, .ne, faate->st_sear, .p
      if (state-)
  {
  {
	if (state->out_req_sent) &}
ret= 4;_set_status(ch""&state->ou_sear, state->config);
  lse
	{
/*t= 4;_set_status(chatus, f)tate->ou_sear, state->config);
    st}
      msate->crwaings _r (OT : 1;ate->z_f_req_sent)  0;
	}    Log ((9"unD't chwaings or (iGOT, ;
	   }
remove_from_senpoo(state, coate->set, .,los	  	tate->out.path, stree->out.paacon %config);
    st}
_ZERO (&state->out);
	}  }
      se
    {
      ifr (arn 0; i n state->n_sent_fls; ++i)n    {
{
	if (stfile_cmp (state->sent_fls + i,nargv[0], fsize, ftime))
  
	  ifar szAddr[FTN_ADDR_SZ + 1];

  	ftnaddress_to_str (szAddr, st&ate->sent_fls +[n]e, 
	  state->extes_rcnt)   state->innt_fls +[n]eze;
  	++state->files_rcnt_f	  memcpy (&state->ou_sear, st&ate->sent_fls +[n]e, sizeof (TN_ADDR));
       fa st (state->to_flag & WE_ND)
  { {
  Lo
  Log (7, "SessND_sear, % %s:%u/%u.%u",
          fa stfa state->st_sear, .z,tate->st_sear, .net,tate->st_sear, .ne, faate->st_sear, .p
   Log (2, "innt_f%s (%" PRIuMAX ", %.2f CPS, %s)",
	   st  state->skit_fls +[n]eth, s   st  stintmax_t) state->innt_fls +[n]eze;
s   st  stiuble) (state->innt_fls +[n]eze;
/
	   (s  (safe_time() == state->innt_fls +[n]ezrt ?
	  	: (safe_time() - state->innt_fls +[n]ezrt ?, szAddr);
  	if (state-)
  	{
	if}
if (state->skt_req_sent)   !*state->ND_flag & WE_ND))
  
    rc,  4;_set_status(ch""&state->ou_sear, state->config);
  l    se
  
    rc,  4;_set_status(chatus, f)tate->ou_sear, state->config);
  	}
  	state->crwaings _r (OT : 1;0  	Log ((9"unD't chwaings or (iGOT, ;
	 fdef WITH_PERL
      in  pn l_after_hant) tate, i)n
  ndif

/	remove_from_senpoo(state, coate->sent_fls +[n]e,los	  	ate->skit_fls +[n]eth, soate->sent_fls +[n]eacon %config);
   remove_from_sent_files_queue (state, i)n
   reeak;
        /* Alweave %sACKor (i_ONE_ile wi
  	}     }
    }
  }
  ifse
    retc 0;
	}   ee(szOavedlgs, 
  return co;
  
static int NDB &&TATE *state, char *buf, int sz, BINKD_CONFIG *config)
{
  chUSED_ARG(szf) =  UNUSED_ARG(sz);

  ifate->rcvete aOB &&1;
	}  ate->delay_EOB &&0; /* rel: /swean (sdits  anyway now :)/
  if (state->st.f)
	 {
    chase_partial (tate, config);
    }
if ((state->ND_flag & THEY_ND) && state->in_complete.netname[0])
    /* rename complete received file to its true form */
      ar realname[MAXPATHLEN + 1];
      ar szAddr[FTN_ADDR_SZ + 1];

       (inb_done (&(state->in_complete), realname, state, config) == 0)
        turn 0;
       (*realname)
      {
    /* Set flags */
        (e rr_test(&(state->evt_queue), realname, config->evt_flags.first))
          ate->q = evt_run(&(state->evt_queue), state->q, realname, state->fa,
	         ate->nfa, state->state == P_SECURE, state->listed_flag,
                 ate->peer_name, state, config);
         We will run external programs using this list */
        d_to_rcvdlist (&state->rcvdlist, &state->n_rcvdlist, realname);
      }
  ftnaddress_to_str (szAddr, state->fa);
      ate->bytes_rcvd += state->in_complete.size;
      state->files_rcvd;
      g (2, "rcvd: %s (%" PRIuMAX ", %.2f CPS, %s)",
	tate->in_complete.netname,
	        (stntmax_t) state->in_complete.size,
	        (stuble) (state->in_complete.size) /
	        (stae_time() == state->in_complete.start ?
	                       : (safe_time() - state->in_complete.start)), szAddr);
      _ZERO (&state->in_complete);
      return 1;
}

stpe &f WIt complmd BZTATE *state, char *buf, int sz, BINKD_CONFIG *config)
{;tatic chaplmd BZ*aplmd Bs[] =
  chL, "OADR, D, state_file_recv (, , stB &, T, "%REor, drY, "NT, "%IP, 
};/* vaRv (s xt)
 block,rogrss(bessgs */ (iite tssdiwnKe fita = om the remote on
static int GEcv_rablockSTATE *state, BINKD_CONFIG *config)
{
  stt no_p
  if  sz,  1;ate->z_ize = 0-1)
 ? BLK_H_SZ IZ: P_ate->z_ize =;#ifdef BW_LIM
  pn (state->bw_recv)
  {
    me_t ftcme = same();LL)
 ;   if (!state->z__recv_unlme))

      state->cr_recv_unlme)) comme));     state->cr_recv_unc = ps0;tate->cr_recv_unc =N 0;
	}        /* (!tcme = > ate->z__recv_unlme))

      stt comp= state->bw_recv_retes_r /!tcme = - ate->z__recv_unlme))
;     state->cr_recv_untes_r 0;
	}    Loate->cr_recv_unlme)) comme));     st (state->bw_recv_abc =N <0);
=        state->st_recv_unc = pstate->bw_recv_abc =N*ate->st_recv_unc = +omp=/ 10tate->bw_recv_abc =N 1];
        state->z__recv_abc =N++	}    }
      else ifate->st_recv_unc = pst9*ate->st_recv_unc = +omp=/ 1010      Log (4,9"receiv:irrentlyomp=  %d uargvg.omp=  %d u
	tmp=,fate->st_recv_unc =
    }
    else if ((sate->bw_recv =  state->in_recv_untes_r > ate->z__recv_u
      stturn 1;
}* rel: /sturn 1;e same tiaif noTCRL
R_WOULDBLOCKo
    if (rlate->bw_recv =  state->in_recv_unmp= > ate->z__recv_u
      stturn 1;
}* rel: /sturn 1;e same tiaif noTCRL
R_WOULDBLOCKo
    #endif
     (rlaz= 0)
      )) 0;
	}  se if (!s()) 0;cv (STate->sta	tate->in_f,  state->miiady 		    st staz state->in_ady 	)) != SKIOCKETRR, OR! {
    Lo ((sTCRL
RNO= THECRL
R_WOULDBLOCKo !*TCRL
RNO= THECRL
R_AGAIN      {
    /*turn 1;
    }
    else i   Lo      chasistnar *staave_err THECRL
R(
      state->in.o_ror (e1;
	}    if (st!nkd v_exit    {
{
	Log (1, "Seceiv:i", staave_err
	if (state->in)
  	bad_try (&state->to->fa, "Caave_errBAD_AUIOconfig);
    st}
      msturn 0;
    }
  }
#endef BW_LIM
  pnate->in_recv_untes_r  st_p
 ndif
     (rlate->crypt_flag == (WS_CRYPT) s
  decompt_flf, (ate->in_f,  state->miiady 	t_p	tate->inys_in, 
  state->msiady   st_p
    Wea(ber(state->in.ady  <sta;

/
  if (state->st.ady  =sta;
 {
    if (state->stize = 0-1)
)      /* Alady g thblockShdy  *
	/ { {
      state->crim=N NUate->in_f, ] ==>> 7      state->in.ze = atffffunsign fiar *st)Uate->in_f, )] ==& ~0x8;
=<< 8) +
	ffunsign fiar *st)Uate->in_f, )];
      stg (7, "Secv_ud hd %s!i%s)",
 tate->in.ze =,tate->crim=N ? "m=N: "nota ="
      if (state->toize = 0-1
	{
go itDoNotEvenTryToRv (ZeroLengthBlock    }
    else i   Lo    DoNotEvenTryToRv (ZeroLengthBlock:     stg (7, "Set ofblock%s!i%s)",
 tate->in.ze =,tate->crim=N ? "m=N: "nota ="
      if (state->toim){
     {
	stt rc;
e1;
	}
	state->figs_in_batch =;#ifdef BWTH_PERL
      in   l_afonecv(state, ofate->in_f,  tate->in.ze =
  ndif

/	 (state->toize = 0-1
	{
Log (1, "unzero lengthhaplmd BZom thmote on(st subet thlea su1)"
  lse
	f (!s(unsign f(state->in_f, ] => 64M_X "	{
Log (1, "unknown adm=N pe & om thmote o:d u
	tate->in_f, ] =>;else
	{
	  meate->in_f, ]ate->toize =] 0;
	}    Lo  Log (5, "rat_ud m=N %ss", staaplmd B[funsign fiar *)tate->in_f, ] =>]	tate->in_f, +1
   rem= comprmd Bs[(unsign f(state->in_f, ] =>]  !f  tate->	tate->in_f,  st1 tate->in.ze = st1config);
   
st	 (st == SK
	{
	  state->sk.ady  =;
	}
return rc0; 	}     }
    }
else if ((sate->bw.f)
	 {
  {
	sf defined(WITH_ZLIB) || defined(WITH_BZLIB2)
    if  if (state->z_recv =    if  if          Lot rc;
e1; nz g = (oate->in.ze =,tzavailnz put	}    Lo  Loar *szf, ]ZBLK IZ:]	}    Lo  Loar *suf,  NUate->in_f, 
      if  if (state->z_reata = NNULL)
    stif  if          Loif (stcompress_deit(state->z_recv, st&ate->z_idata);
  { {
  Lo
  L{               g (2, "Can't'tnit_kecompress_d;
          st  return 0;
      }
    }
 lse
        Lo      g (2, "NDcompress_deit(s suess(b;
          st}         stwhe to( g =    stif  if          Loifzavail NUZBLK IZ:      }
    }
 put NU g =      }
    }
;
e1;do_compress_dtate->z_recv, stzf, &stzavailnzf, &st put,                              state->z_seata);
      st  Loif (st;
e<)
          Lo L{               g (2, "CaDompress_d %ssror (e%d state->in.netname, strc
          st  return 0;
      }
    }
      }
    }
se
        Lo      g (2,10"sk d tes_r ofita = compress_d fi %s:d st put,fzavail
      st  Loif (stzavail !0 && (sfite to(zf, &szavailnz1state->in.nef) <0)          Lo L{               g (2, "Caite toror: %s! "strerror(errno));
      re      do_empress_abort(state->z_secv, state->z_idata);
      st      state->z_seata); NULL;
	     }
  st  return 0;
      }
    }
      }
    }
f,  s=z put	}    Lo  Lo z g = -=z put	}    Lo  Lo zate->z_isize = s=zzavail	}    Lo  Lo zate->z_iscize = s=z put	}    Lo  Lo}
  st  Loif (st;
e 1) |   stif  if f ((rc = cocompress_deinit(state->z_recv, state->z_idata);
)e<)
          Lo L  g (2, "Cacompress_deinit(seturce is:d strc
          st  ate->z_seata); NULL;
	     }
  st}
  st  Loif (stfflushtate->in.f))
    {
  Lo L{             g (2, "Caite toror: %s! "strerror(errno));
      re      turn 0;
      }
    }
  }
    }
  }
    se
#endif
      stif (state->toize = !0 && (     re      (fite to(ate->in_f,  tate->in.ze =nz1state->in.nef) <0)&
          /*  fflushstate->in.f));
    if  if          Log (2, "Caite toror: %s! "strerror(errno));
      re    turn 0;
      }
  }     stif (stnfig->evrcent rs& state->in.size >= )
                    Log ckSem(&e
#m
      re    prt r(st"%-20.20d %3.0f%%\r state->in.netname, s                   100.0 *tello (state->in.f)); 10tfloa state->in.size);
	m      /*  fflushstatdt);
	}    }




Relea eSem(&e
#m
      re  }     stif (stello (state->in.f));  state->in_c.ze)
        re{}    Lo  Loar *sAddr[FTN_ADDR_SZ + 1];

     Lo  Loar *salname[MAXPATHLEN + 1];
  
  st  Loif (stfose (state->in.f);
    {
  Lo L{             g (2, "Can'tt sulose(f))",%s! ("                 state->pe.netname, statrror (errno));
      re    state->pe.nef NULL;
	     }
  st  turn 0;
      }
    }
  }
    state->pe.nef NULL;
	 f defined(WITH_ZLIB) || defined(WITH_BZLIB2)
    if  ifif (state->z_recv =    if  if L{             g (2,4"File ti%ssmpress_d fize >= PRIuMAX " byte(ss,smpress_date i%s:.1f%%"                 state->pe.netname, sttntmax_t) state->iniscize =                 st100.0 *tate->z_iscize = /zate->z_isize =
      st  Loif (state->z_idata)
    {
    Lo L{               g (2, "Carning: retra = mpress_d fita); nored", 
      re      do_empress_abinit(state->z_recv, state->z_idata);
      st      state->z_seata); NULL;
	     }
  st  }     }
    }
ndif

/	re (state->ND_flag & THEY_ND) x 	{
	if}
ifg (5, "rale ti%ssmprete received f,hwaings or (iname gs "	         state->nf.netname);
	ms  msgcpy(sttate->ou_complete);st&ate->z_instaeof (Tate->se_complete);

  	}
  	stse
  
  	if}
if (stb_done (&(state->in_c realname, state, config) == 0)
        re  st  turn 0;
  	     (*realname)
  	  {
	st    /* Set flags */
        if      (e rr_test(&(state->evt_queue), realname, config->evt_flags.first))
                  ate->q = evt_run(&(state->evt_queue), state->q, realname, s	    st state->fa,
	 ate->nfa, state->state == P_SECURE, s	    st state->fasted_flag,
  ate->peer_name, state, config);
  	       We will run external programs using this list */
  	      d_to_rcvdlist (&state->rcvdlist, &state->n_rcvdlist, realname);
  	    }
	  ftnaddress_to_str (szAddr, state->fa);
  	    ate->bytes_rcvd += state->in_ceze;
  	++  state->files_rcvd;
  	    g (2, "rcvd: %s (%" PRIuMAX ", %.2f CPS, %s)",
	tate->in_cetname,
	   (u    (uintmax_t) state->in.size, m   (u    (uiuble) (state->in_ceze;
/
	   (s  (s(stae_time() == state->in_cezrt ?
	  	  : (safe_time() - state->in_cezrt ?, szAddr);
  	if}
	  g_sendf (state, M_GOT, "%s %" PRIuMAX " %" PRIuMAX,
		   ststate->in.netname,
		   (u(uintmax_t) state->in.size,
		   (u(uintmax_t) state->in.time);
	ifTF_ZERO (&state->in);
  
	else
	f (stello (state->in.f)); >tate->in_c.ze)
  
	  Log (1, "GEvd += PRIuMAX " %"tra = tes_r!"s   st  stintmax_t) sttello (state->in.f)); -tate->in_c.ze)
 )	}
return rc0; 	}     }
    }
else if ((sate->bw.ze >= )
        	Log (1, "Senoredg thta); blockST PRIuMAX " byte(s))",
	     stintmax_t) state->in.ze =
      st}     state->in.ze = at-1	   }
    state->z_.ady  =;
	}  }
if ((s)) 00 && (ssz= )
    {
  state->in.o_ror (e1;
	}     (st!nkd v_exit    {
      char *sps_err TH"nfinecon %hase_pdy rere_rnor host";     Log (1, "unceiv:i", sta_err
	i  Loif (state->z_)
  	d_try (&state->to->fa, "Ca_errBAD_AUIOconfig);
    st}   return 0;
  }
  ftse
    return 0;1}

static void setundDDRRSTATE *state, BINKD_CONFIG *config)
{   char buszN_Adr[FTN_ADDR_SZ + 1];

   ar *spszAkas  int i, rcN; struct raakaain *ps;
  
Log ((7"skidifDDRR(,%st of%dhmote ondress_te, state->oun);
   if (!state->topdr);
 {
  state->inndr); config->randr);      ate->bypdr); coxao (c(ate->inndr); *izeof (TN_ADDR));
      gcpy(state->bypdr);config->evpdr, state->fandr);*zeof (TN_ADDR));
    
    N NUate->inndr);    r (ps = config->raakask.first; ps; ps = ps->next)
  {
    if  i,= (of->nepe & am0x7;
	 }
  t rc;

       (state->z_)
      }
;
e1;naddsk.fmp (ms->mask, st "u&(ate->to->fa,  != SKf->nepe & am0x8? P_-: (s0
    stse
      {
;
e1;naddsk.fmp (ms->mask, state->nfa, state->stfa!= SKf->nepe & am0x8? P_-: (s0
    st Wehi abskao
    if (rlt= SKACT_HID&& strc

      stt 0;
	}    Lowhe to(< state->n_sdr);
     stif (stelddress_top(state->topdr, + &tff->ne,  != SK;
=        stchar buf[MAN_ADDR_SZ +

     Lo  Lonaddress_to_str (uf, "wff->ne,  !	}    Lo  Log (, "rehi g thskao", buf, 
       fa st (st< state->n_sdr);-)          Lo Lgcpve_ftate->topdr, + &tate->topdr, + + "u(ate->n_sdr);-)-i)*zeof (TN_ADDR));
       fa state->n_sdr);--;
  }
    }
  }
    se
# i++	}        /* Chess_tlyoskao
    ifse if ((st= SKACT_PRESENT& strc

      str (i = 0; i < state->n_sdr, +1; i++
     stif (sti= state->inndr);  deelddress_top(state->topdr, + &tff->ne,  != SK;
=eak;
      }
 (sti= state->inndr);
=        star buf[MAN_ADDR_SZ +

     Lo  naddress_to_str (uf, "wff->ne,  !	}    Lo  g (, "reess_tlyg thskao", buf, 
       fa ate->n_sdr, ++;     stif (state->tondr); > N
=        stchate->bypdr); coxalna (c(ate->inpdr, state->fandr); *izeof (TN_ADDR));
      {     _++;     stif}
  }
    gcpy(state->bypdr);+ate->n_sdr);-)"wff->ne,  sizeof (TN_ADDR));
       f    }
  }
   strzAkas coxao (c (ate->inndr); *i(N_ADDR_SZ + 1];;
    *rzAkas co0    r (ps= 0; i < state->n_sdr, ++i)
    {
  ftnaddress_to_str (szAdN_Adr[F&tate->topdr,  i, 
      atrcatszAddkas"re "
      atrcatszAddkas"rAdN_Adr[F
      reg_send2 (state, M_ERADR, Addkas"r0
    ee(sszAddkas
}

static void sebainerSTATE *state, BINKD_CONFIG *config)
{
  stt notz; char buszLocalTe);[60

   ar *spszOpt    me_t ftt; struct ratmatm
   ar *spdayweek[] = {"Su, bu"Mo, bu"Tu, BA"W", w,"Thu
	t"Fri
	t"Sat"}
   ar *spmonth[] = {"Ja, bu"Feb bu"Mar st"Apr bu"May bu"Ju, b                    "Jul st"Aug
	t"Sep
	t"Oct
	t"Nov""CaDom"}
 
if ((st!no_MD5&& ststate->to)
 & (     restate->NDMD_ar llenge=MD_getCr llenge(LL, 10ate)) !!ULL)
     /** Alrnswedg thsi abMUSTend unCRAMessage fr alr ve (&rst; _NUL FR
      ar res[MD_CHALLENGE_LEN*2+15]}* rex_t. lengthhofptiotrucg */
	s    atrc(sta	t"OPT "
      MD_toSucg *(s+4&tate->toMD_ar llenge], state->inMD_ar llenge+1
      ate->byMflag &;
    ifg_send2 (state, M_ERL, "Oa	t"")  }
  ftse
    reate->byMflag &;
	}   g_send2 (state, M_ERL, "O"SYS, %.nfig->rasysme);
    g_send2 (state, M_ERL, "O"ZYZ, %.nfig->rasysop
    g_send2 (state, M_ERL, "O"LOC, %.nfig->ra (ce i%n
    g_send2 (state, M_ERL, "O"NDL, %.nfig->rane, info
   if= safe_time();
    t  1;tz_off(t%.nfig->ratzoff
  stae_ti (celme)) (& &sttm
   f de0 staprt r(stszLocalTe);"%s %, %2d %ss"d %02d:%02d:%02d %c%02d%02d s)",
             dayweek[tmratm_wday sttmratm_mday, month[tmratm_mon]             tmratm_yea +1900sttmratm_hoursttmratm_minsttmratm_sec             (tz>=0? A_'+' (s'-',bsol(tz)/60,bsol(tz)%60,            tzme[MAtmratm_isdst>? P_: (s0]
  nde
    snprt r(stszLocalTe);"%aeof (TazLocalTe);)b             s %, %2d %ss"d %02d:%02d:%02d %c%02d%02d b             dayweek[tm.tm_wday sttm.tm_mday, month[tm.tm_mon]             ttm.tm_yea +1900sttm.tm_hoursttm.tm_minsttm.tm_sec              (tz>=0? A_'+' (s'-',bsol(tz)/60,bsol(tz)%60
#endif

    g_send2 (state, M_ERL, "O"TIME, stazLocalTe);)	}   g_send2 fstate, M_ERL, "     "VERre MYME); "/e MYVERre%ssPRIuTCLME); "/e IuTCLVER,"two_os_rucg */()
   if (!sate->to)
  !*sate->delay_EOADR)etundDDRRSTate, config);
   if (!sate->to)

 {
  stazOpt xstrdup(" " NDA EXTCMD;
    if (f=ate->NR_flag & WANANTR) &&xatrcat(&azOpt"re NR;
    if (f=ate->NR_flag & THEY_ND) &&xatrcat(&azOpt"re ND;
    if (f=ate->NRypt_flag ==WE_NDYPT) s&xatrcat(&azOpt"re YPT) ;
	 fdef WITH_PEIB
    if (!sate->z_cansecv =  ];;&xatrcat(&azOpt"re ") =;endif
#ifdef WITH_BZLIB2
       (!sate->z_cansecv =  ]2;&xatrcat(&azOpt"re 2") =#endif
    ifg_sendf 2tate, M_ERL, "O"OPT stazOpt
    ifxee(szOzOpt
    } 
static int NDate_file_rea) nsferiTATE *state, BIN_AQ *le_rBINKD_CONFIG *config)
{
  struct skite, sb  FILE *f;
 NULL;
	   t argcon %hat-1, i  char *extra;
  
if (state->skt.f)
	{    lose (state->out.f);
	 }
_ZERO (&state->out);
	      /* AlNoile toin_a) nsferi

     (state->skflo == 0)
       /* AlTheris onno en (s.?lo/
	s  {
  state->inx_tflv; coMAXFLVRstate->skx_tflv;filenaskflvr
    st WeT (&to en (se samuggeed_file wi
  stif (steenaskpe &  '\0s'  { {
      stab.st_ze = e1;nenaskze;
      ++ab.st_cme = saab.st_mme = saeenaskpe));     stf NULL;
    }
    stse i   Lo      ch Weloofor *.e file wain_not-to-nd unst */
        r (i = 0; i < state->n_senond ust *; i++
     stif (strcmp (,eenaskth, soate->senond ust *[i]!= SK;
=turn 0;
       if ((rc= fopen (steenaskth, soteenaskpe &  '\0l'? A_"r+b: "no")) == 0)
&
  	ftnite, teenano (, st&sb== -1)
    {
{
	L        g (2, "Ca: %sc'tt suen (:i", steenaskth, soatrror (errno));
      re  turn 0;
      }
      if We w'veuen (_fias.?lo/
	s  stif (steenaskpe &  '\0l'    {
{
	L        ate->skflo gcon %hateenaskgcon %       fa atry (state->seflo th, soeenaskth, 
      re  mcpy (&state->ouflo =ast&lenaskf sizeof (TN_ADDR));
       fa ate->skflo ==  f      }
    }
    /*mcpy (&state->out,  =ast&lenaskf sizeof (TN_ADDR));
       (sttate->ND_flag & WE_ND) == 0)
        gcpy(sttate->ou_sear, st&lenaskf sizeof (Tate->ou_sear, ;
      g (2, "NDcurhmote ondres  %d uu/%u.%u",
          flenaskf .z,tlenaskf .t, fa-enaskf .te, fa-enaskf .p
    }
if ((sate->skflo ==!=)
    {
  statry (state->set, .,los ate->seflo th, 
      whe to(1    {
      char *spw       if ((r!ady lago_le z_tate->out.path, "r&acon %coate->skflo =)	{    {
	stlose (state->ouflo =)	  ate->ouflo ==  0	    T.?lo/ase_pd,emove_from_senpoo(()ill runow link %si*/
  	move_from_senpoo(state, coate->seflo th, so0so0sonfig);
  F_ZERO (&state->ouflo
	  turn 0;
      }
       if ((rc= gea) nslago_le z_tate->out.path, "rnfig->rarf_les.first)) {
!=)
  	g (5, "ra%ssmacpedy %s:  state->out.path, stw)       if Weloofor *.e file wain_not-to-nd unst */
        r (i = 0; i < state->n_senond ust *; i++
     stif (strcmp (,w A_w "neenaskth, soate->senond ust *[i]!= SK;
=    	ifxee(s );
    	remove_from_senpoo(state, coate->set, .,los	  	   ststate->int.path, stree->out.paacon %config);
    st}
  }
fak;
      }
}
      if (st< state->n_senond ust *)onfitinue       if ((rc= fopen (stw A_w "nate->out.path, "rb")) == 0)
&
  	ftnite, teenano (, st&sb== -1)
&
  	ft(ab.st_me is& S_IFDIR)=!=)
    {
{
	Log (1, "Seate_file_rea) nsfer%s: %s", s     stw A_w "nate->out.path, "ratrror (errno));
      re   (ste) lose(f)==	  xee(s );
  	move_from_senpoo(state, coate->set, .,los	  	tstate->int.path, stree->out.paacon %config);
    st}
  }
  else
      {
	stxee(s );
  	eak;
      }
    }

   /*mcpy (&state->out,  =ast&ate->ouflo =astzeof (TN_ADDR));
    
     (acceon %ha-1)
    {
  statry (state->set, .th, soeenaskth, 
      ate->set, .,lo] == ;
      ree->out.paacon %hateenaskgcon %      ate->int.sime &   eenaskpe &  }
  else
  {
    Loree->out.paacon %hatgcon %      ate->int.sime &   
  }
  state->z_t.f = fop; state->z_t.f ze = stab.st_ze =; state->z_t.f me = saab.st_mme =; state->z_waings _r (OT : 1;0    g ((9"unD'tchwaings or (iGOT, ;
	   ate->z_t.f zrt ?
safe_time();
    tname,
state->set, .tname, sttate->out, arnfig);
  if (*bispkttate->set, .tname, )& state->out.size >=<= 6
    {
  stg (3, "repp chempty pkt , %" PRIuMAX " byte(s  state->out.path, s
	uintmax_t) state->int.size >
    if (f=ate->NRt.f);
 lose(f)ate->out.f);
	 }
remove_from_senpoo(state, coate->set, .,los	                     state->z_t.path, stree->out.paacon %config);
    st_ZERO (&state->out);
	}  }
turn 0;
  }
  fdef BWTH_PERL
     ((arl_afbere_rendf tate)
#= )
 
    Log(5,3"skidif
 %s (%ort(spdy rePl_a bere_rendf t) state->out.path, 
    if (f=ate->NRt.f);
 lose(f)ate->out.f);
	 }
remove_from_senpoo(state, coate->set, .,los	                     state->z_t.path, stree->out.paacon %config);
    st_ZERO (&state->out);
	}  }
turn 0;
  }
  fdif
    g (2, "skidif
 %s (%ess",ST PRIuMAX " b,
         ate->z_t.path, stree->out.patname, cointmax_t) state->int.size >
#ifdef BW_LIM
    tup_retundDte_limit(state, config);
#endif

    send_init(state, config, ex&tra) =  
if (f=ate->NR_flag & WANER) &   {
  stg_sendf (state, M_GELE_b"%s %" PRIuMAX " %" PRIuMAX " %"-1", s     st tate->out.netname, cointmax_t) state->int.size >		 u    (uintmax_t) state->int.sime, sttra) =    state->z_f_req_sent)  0;
  }
  else
 f (f=ate->NRt.f); NNULL)
    st/*
atus,  withnno NR-me is
      g_sendf (state, M_GELE_b"%s %" PRIuMAX " %" PRIuMAX " %" PRIuMAX,
%s %"		    st tate->out.netname, cointmax_t) state->int.size >		 u    (uintmax_t) state->int.sime, s	 u    (uintmax_t) state->int.size =nztra) =    se
      g_sendf (state, M_GELE_b"%s %" PRIuMAX " %" PRIuMAX " %"0", s     st tate->out.netname, cointmax_t) state->int.size >		 u    (uintmax_t) state->int.sime, sttra) =  
return 0;1}

static void selog_d_inof_ssion */har *status, FTATE *state, BINKD_CONFIG *config)
{
  char buszN_Adr[FTN_ADDR_SZ + 1];

  chBing (Ste, tatus, f)ste, config);
#endef BWTH_PERL
     l_after_hantion *tate, coate-);
  ndif

     (state->z_)
      naddress_to_str (szAdN_Adr[F&ttate->to->fa, ); else
 f (f=ate->NRfa)
  ftnaddress_to_str (szAdN_Adr[F&tate->tof =    se
      atry (stadN_Adr[F&t"?")  
Log (2, "skne (&(%s, %"  FTA/R%s!i/!i%s)PRIuMAX " %/ PRIuMAX " byte(s ),
         ate->z_ %s? " %s" (safte->tof s? "om th: "no")"rAdN_Adr[F         ate-, f        ate->z_les_rcnt_f, ate->files_rcvd;
f        ate->z_tes_rcnt) , ate->bytes_rcvd +
}

stid seprotoco(stIOCKET sock, faN_ADNOD*sttochar *burrentlyear, stNKD_CONFIG *config)
{
  chATE *sate->; struct rate, val tv    edet_s  stw  int no_ochrd#endef BWTHN3    unsign filo thi_ou  0;
	}  unsign filo thu_tnate, ou  0;nfig->rannate, ou *1000000l#endif
    ruct skiockar, nit er_name, ; strocknan_t er_name, _nan
safeof (TFer_name, )  char *ehostAXPAHOSTME);N + 1];
    asistnar *staave_err THLL;
	   t arA_SZnt)  0;
	}fdef BWTH_PERL
     )  ofo1; (wwwwwwwwwwwwwwwwwwwwwwwww/*
op se %s0e %sort(session */
     )   l_afonendleshakeone (&0;
	}fdif

     (st!it(s_protoco(st&ate, coaock, fatochafig)
{)}  }
turn 0  
if (f=geter_nme,
staock, fa(ruct skiockar, st)U& er_name, st&er_name, _nan)ha-1)
    {
  st (st!nkd v_exit    {
{
g (1, "Segeter_nme,
:i", stECRL
R/()
    /*mcpt_s(&er_name, st0,afeof (TFer_name, )
    
     (ac %s strrentlyear, )   state->.er_name,  0;nrentlyear, ; else
  {
    Lotwo_hostme, (&er_name, sthoststzeof (Thost)"rnfig->rabackss_olv=    state->.er_name,  0;host  }
  staeterocont to("%c [%s]"fato A_'o' (s'i',tate->.er_name, =    lockhostsem;
    g (2, "skidion */withn",ST s,
         ate->.er_name,          inna_ntoaTFer_name, izenear, ;
    relea ehostsem;
  
if (f=getiockme,
staock, fa(ruct skiockar, st)U& er_name, st&er_name, _nan)ha-1)
    {
  st (st!nkd v_exit    {
{
g (1, "Segetiockme,
:i", stECRL
R/()
    /*mcpt_s(&er_name, st0,afeof (TFer_name, )
    
 ftse
    reate->.ou nip=er_name, izenear, .sear, ;  fdef BWTH_PERL
     ((aate->.)

 {
  star *sta ps-l_afonendleshaket&ate, config);
    st l_afonendleshakeone (&0;1    if (stas st*s)
      Log (1, "fsort(spdy rePl_a onendleshaket):i", sta
    st}
g_send2 (st&ate, M_ERR, "Cs"r0
        ofo1;
    }
  }
#eif (stok)endif
    bainerST&ste, config);
#endef BWTH_PERL
     (st!ok) ; else
  ndif
     (rlsentrver= > nfig->rax_t)ntrver= 
 (s)
    {
  stg (3, "fstoo mansentrver=;
    ifg_send2 (st&ate, M_ERY, "N"Too mansentrver=;"r0
      else
  {
    Lowhe to(1    {
      ch/*
Ithe fieue (s onnothempty d BZtheris onno le toin_a) naf *
	/ { {
if (!state->. (celOB && state->.q& state->.t.f); NNU&& (     re    tate->.waings _r (OT : 
 (sate->.t_req_sent)   state->.ate->!=P_LL)
    stif{
	N_AQ *q	}
	whe to(1  	{	       /* AlNt)
 .pk fa.,lo/ (iaile wi
  	  q =;
	}
re ((aate->.flo ==
  	ft  (uiq =;seleca_nt)
ile_r(aate->.q,tate->., state->.n,  !=!-1
	{
Lo	if}
if (state_file_rea) nsferiT&ate, M_qchafig)
{)}	}
  }
fak;
  	}
  	stse
  
  	if}
ifq_ee(sszAte->.q,tnfig);
  	    ate->.q&=;
  	    fak;
  	}
  	}     }
       if AlNoimorfile wnT sped unin_as litch =coaoped unB &&	/ { {
if (!state->.q 
 (sate->. (celOB && state->.ate ==!P_SELL)
& state->.at_fls + ==)
    {
{
	Lwwwwwwww/*
l: /sd't ched unB &&r (inkd p/1.0  defiy_EOB && lit_s 
  	 (!state->.fiy_EOB && (state->.majo; *i100 state->.mino; > 100 {
   state->. (celOB &&0;
	  elg_send2 (st&ate, M_ERR &, 0"r0
        }
  }
  el       ifFDERO (&str
	i  LoifFDERO (&stw
	i  LoifFDES (STaock, fa&r
	i  Loif (state->.gs */
          /*(ate->.t.f); 
 (sate->.t_req_sent)   sttate->.waings _r (OT :)/
          /*ate->.tft =  state->.id_stf ()}	FDES (STaock, fa&w)       if (state->.vete aOB && state->.at_fls + ==)
& state->. (celOB && s  state->.T_FILE_balance;
o==)
& state->..nef N=)
& state->.t.f); NNU&    stif{
	/*
E unothe firrentlyotch = 
  	 (!sate->.vdlist, 	{
	  state->.q&=;ogrss(bcvdlist (&state->state->.q,tnfig);
  	  qo_stkillst (&state->.killst (&ttate->.n_killst (&tate->.q
	  stee(wcvdlist (&state->.vdlist, &state->.rcvdlist, 
  
	elg (3,6"fstherisweris!i%gs */in_as litch = state->.gs_in_batch =
	if (state->.gs_in_batch ==<= 2& (state->.majo; *i100 state->.mino; <= 100 {{
	     {     _set_status(ch""&state->._sear, st&ate->config);
    st}
  }
ate->._sear, .z=-1  	  fak;
  		else
	{
	  me Setrt ?
e fixt)
 bch = 
  	 tate->.gs_in_batch =&=;
  	  ate->.vete aOB &&=tate->. (celOB &&0;
	}
re ((aOSET)_seLE_bSST&ste, config);
) 	    ate->.q&=;sencabatoxwnTaate->.q,tate->., state->.n, ,tnfig);
  	  nfitinue  	}     }
   f defined(WITHN3 )* Alworkarou unwinaock bugo
    if (rlt_ou  <hu_tnate, ou     {
  ndif
      sttv.tv_sec 0;nfig->rannate, ou 	      /* Alt flup te, ou  r (iaeleca()&	/ { {
iftv.tv_usec 0;0      Log (4, "NDtv.tv_sec=%lu,ftv.tv_usec=u % f
  (uinnsign filo t)ttv.tv_sec,uinnsign filo t)ttv.tv_usec
    st}
)) 0;aelecaSTaock,  st1 t& st&w, 0"r&tv
	i  Loif (st)) <)
          aave_err THECRL
R (
      stg (4, "NDaeleca fi!i%sr=%i, w=%i) st_ochFDEISS (STaock, fa&r
chFDEISS (STaock, fa&w)); f defined(WITHN3 )* Alworkarou unwinaock bugo
    if    stse i   Lo      chg (4, "NDwin9xnwinaock workarou u: te, ou  deteca fi(nnate, ou =%u sec,ut_ou =u % sec) %.nfig->rannate, ou ,ut_ou /1000000
    st}
)) 0;
    }
  ndif
      stbsy_ sh AK(nfig);
        /* Al sh AK*.bsy'*/
        (e r)) 00 &      {
	ifate->..o_ror (e1;
	}og (1, "Sete, ou !"
	if (st)
  	bad_try (&st->fa, "C"Te, ou !"BAD_AUIOconfig);
  	eak;
      }
    }
else
 f (f=)) <)
        	ifate->..o_ror (e1;
	}o (st!nkd v_exit  
	  Log (1, "GEaeleca%s (%"gs: "%!i%%i) staave_errBAaock, fatv.tv_sec
  	if (st)
  	babad_try (&st->fa, "Caave_errBAD_AUIOconfig);
  
	break;
      }
    }
  r  =;FDEISS (STaock, fa&r
	i  Loif (strd)     /* AlHe %ssomeas  thiolady /
        	if (stfcv_rablockST&ste, config);
) 	  eak;
      }
  fdef BWTH_PERL
      in (state->.n,   stt l_afonendleshakeone (
=        star buta ps-l_afonendleshaket&ate, config);
    st  st l_afonendleshakeone (&0;1    if  if (stas st*s)
      Lo  Log (1, "fsort(spdy rePl_a onendleshaket):i", sta
    st}
st}
g_send2 (st&ate, M_ERR, "Cs"r0
          }
fak;
      }
}
      if  ndif
      st (!state->. %s state->.fiy_EODRRS state->.n,   sttA_SZnt) )
 etundDDRRST&ate, config);
 rA_SZnt)  0;1;
      if (stFDEISS (STaock, fa&w))     /* AlClearT sped un
        	if)) 0;aendDblockST&ste, config);
; f defined(WITHN3 )* Alworkarou unwinaock bugo- gi %sup CPU/
        if (stfcd  st)) 00 2        re{}	ifFDERO (&str
	i	ifFDES (STaock, fa&r
	i	sttv.tv_sec 0;0	i	sttv.tv_usec 0;w9x_workarou u_sleep}* res(ssiph, .= 
  	 t (!staelecaSTaock,  st1 t& st0, 0"r&tv
	{
Lo	if}
ift_ou  +0;w9x_workarou u_sleep} 	}
 lse
 f{hi_ou  0;
	 }
  }
    }
  }
    se
#f{hi_ou  0;
	 }
ndif

/	 (st!no) 	  eak;
      }
  fdeefined(WITHN3 )* Alworkarou unwinaock bugo- gi %sup CPU/
        se
#f{hi_ou  0;
	 }
ndif

/  }
  }
   st AlFlushsi put eue (s
    whe to(!ate->..o_ror (! {
    Lo ((st)) 0;cv (Taock, faate->..f, "wBLK_H_SZ IZ: +oMAX_BLK IZ:	)) != SK
        eak;
       (f=)) <)
            if (!tTCRL
RNO=!THECRL
R_WOULDBLOCKo stTCRL
RNO=!THECRL
R_AGAIN  fate->..o_ror (e1;
	}      eak;
          else b     Log (1,9"unPurg fi!d tes_r om thi put eue ( st_o
    
     Setrl ruhe %ssomeas  thioled un
    whe to(!ate->..o_ror (& (     re  tate->.gs */
 *(ate->.tptr& state->.tft =))& staendDblockST&ste, config);
=  
if (f=ate->. (celOB && state->.vete aOB && state->.at_fls + ==)
& s     state->.T_FILE_balance;
o==)
& state->..nef N=)
& state->.t.f); NNU&    {   st/*
Suess(bfulession */
     elog_d_inof_ssion */h"OK"st&ate->config);
    stogrss(bckillst (&sate->.killst (&tate->.n_killst (&t0s' 	 }
  t b_move_frrtial ( t&ate, config);
    st (st)
      stgootry (&st->fa, "C"CONNECT/BND"config);
    }
ifse
  {
    Lo/*
Unsuess(bfulession */
     elog_d_inof_ssion */h"fae td"st&ate->config);
    stogrss(bckillst (&sate->.killst (&tate->.n_killst (&t0
    st (st)
      {        We wic lled d BZtheriswerissrl rule wnTin_a) nsferi--;cvstorfipo ru
        (e rtoloweriTate->.matflv;!=!-1'h'    {
{
	Log (1,4"uncestor  thpo ruwithn`%c'lagsvour state->.gatflv;!} 	cak; aOpo rustate->.->fa, "Cate->.gatflv;config);
    st}
  }
  }   
     (ac %s state->.v_ep cpedlag =  strfig->rahold_ep cped= )
    {
  stg (2, "skholdg thsp cped=mail r (iu % sec"s
	uinnsign filo t)trfig->rahold_ep cped
    sthold_te, &st->fa, "Caa_time() - +trfig->rahold_ep cpedconfig);
    }

  g (2,4"Fission */ase_pd,equitngs ...;
    init(s_protoco(st&ate, config);
    t_qut_s Tate->.t_queue), 	   ate->.t_queue), THLL;
	 