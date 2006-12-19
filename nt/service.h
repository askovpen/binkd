/*
 *  service.h -- Windows NT services support for binkd definition file
 *
 *  service.h is a part of binkd project
 *
 *  Copyright (C) 2000 Dima Afanasiev, da@4u.net (Fido 2:5020/463)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */
/*
 * $Id: service.h,v 2.15 2006/12/19 14:11:02 stas Exp $
 *
 * $Log: service.h,v $
 * Revision 2.15  2006/12/19 14:11:02  stas
 * Minimize required access rights to operate with Windows NT/2000/XP/2003 services
 *
 * Revision 2.14  2003/10/29 06:41:24  stas
 * Remove unused types; small optimizes code
 *
 * Revision 2.13  2003/10/28 20:20:10  stas
 * Rewrite NT service code, remove obsoleted code and add some checks. Found a thread-not-safety problem.
 *
 * Revision 2.12  2003/10/18 18:50:48  stas
 * Move to new 'tray.c' file several functions when is related with 'minimize to tray' feature
 *
 * Revision 2.11  2003/10/18 06:45:23  stas
 * Fix a semaphore usage in exitfunc()
 *
 * Revision 2.10  2003/10/09 09:41:07  stas
 * Change service stop sequence
 *
 * Revision 2.9  2003/10/07 14:41:04  stas
 * Fix NT service shutdown
 *
 * Revision 2.8  2003/10/06 16:50:22  stas
 * Drop excessive numeric values of enumeration in parameter and return values of service_main()
 *
 * Revision 2.7  2003/10/06 16:47:28  stas
 * Use enumeration in parameter and return values of service_main()
 *
 * Revision 2.6  2003/10/05 09:37:43  stas
 * Optimize binkd/nt start: use hack to determine if we're running as a service without waiting for the service control manager to fail
 *
 * Revision 2.5  2003/07/18 10:30:34  stas
 * New functions: IsNT(), Is9x(); small code cleanup
 *
 * Revision 2.4  2003/07/16 15:50:44  stas
 * Fix: restore "Minimise to tray"
 *
 * Revision 2.3  2003/07/16 15:08:49  stas
 * Fix NT services to use getopt(). Improve logging for service
 *
 * Revision 2.2  2003/02/28 20:39:08  gul
 * Code cleanup:
 * change "()" to "(void)" in function declarations;
 * change C++-style comments to C-style
 *
 * Revision 2.1  2003/02/13 19:44:45  gul
 * Change \r\n -> \n
 *
 * Revision 2.0  2001/01/10 12:12:40  gul
 * Binkd is under CVS again
 *
 *
 */

#include "../sem.h"


extern char *service_name;
extern MUTEXSEM exitsem;

/* checkservice() return values */
#define CHKSRV_CANT_INSTALL  -1
#define CHKSRV_ERROR          0
#define CHKSRV_NOT_INSTALLED  1
#define CHKSRV_INSTALLED      2

/* Check service status
 * Return:
 * -1 : can't install service
 *  1 : Service not installed
 *  2 : Service installed
 */
int checkservice(void);


/* main service code
 */
int service(int argc, char **argv, char **envp);

/* Try connect to NT service controller
 * Return 1 if program running standalone or system error
 */
int tell_start_ntservice(void);

/* Minimise to tray
 */
void do_tray_flag(void);


/*  wrapper for win32API function SetServiceStatus() */
BOOL ReportStatusToSCMgr(DWORD dwCurrentState,
                         DWORD dwWin32ExitCode,
                         DWORD dwWaitHint);

/* Service-specific cleanup procedure. Not an thread-safe!
 * Must be set in first call of atexit().
 */
void atServiceExit(void);

/* Start service-specific cleanup procedure.
 * Must be set in last call of atexit().
 * (Report to SCM about service stop pending)
 */
void atServiceExitBegins(void);
