/*--------------------------------------------------------------------*/
/*       G e t f r e e . c                                            */
/*                                                                    */
/*       Part of BinkD project                                        */
/*       Get free space at selected path (UNC supported)              */
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/*       Copyright (c) 1997 by Fydodor Ustinov                        */
/*                             FIDONet 2:5020/79                      */
/*                                                                    */
/*  This program is  free software;  you can  redistribute it and/or  */
/*  modify it  under  the terms of the GNU General Public License as  */ 
/*  published  by the  Free Software Foundation; either version 2 of  */
/*  the License, or (at your option) any later version. See COPYING.  */
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/*                          RCS Information                           */
/*--------------------------------------------------------------------*/

/*
 * $Id: getfree.c,v 2.10 2004/10/29 13:05:05 stas Exp $
 *
 * Revision history:
 * $Log: getfree.c,v $
 * Revision 2.10  2004/10/29 13:05:05  stas
 * Add diagnostic about free space great 4Tb (win32 only)
 *
 * Revision 2.9  2004/01/02 15:31:30  stas
 * Fix the minfree token usage and fix getfree() on Win >w95
 *
 * Revision 2.8  2004/01/02 04:05:30  stas
 * Fix warning (type convertion)
 *
 * Revision 2.7  2003/12/31 10:06:05  stas
 * Fix getfree for very large disks and for mounted partitions
 *
 * Revision 2.6  2003/08/26 22:18:49  gul
 * Fix compilation under w32-mingw and os2-emx
 *
 * Revision 2.5  2003/08/05 05:36:14  hbrew
 * 'static const char rcsid[]' removed
 *
 * Revision 2.4  2003/02/28 20:39:08  gul
 * Code cleanup:
 * change "()" to "(void)" in function declarations;
 * change C++-style comments to C-style
 *
 * Revision 2.3  2001/09/24 10:31:39  gul
 * Build under mingw32
 *
 * Revision 2.2  2001/04/25 20:07:36  gul
 * bugfix
 *
 * Revision 2.1  2001/04/23 07:58:57  gul
 * getfree() on large drives fixed
 *
 * Revision 2.0  2001/01/10 12:12:40  gul
 * Binkd is under CVS again
 *
 * Revision 0.01  1997/01/08  09:00:25 ufm
 *      First revision
 *
 */

/*--------------------------------------------------------------------*/
/*                        System include files                        */
/*--------------------------------------------------------------------*/

#include <windows.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>

/*--------------------------------------------------------------------*/
/*                        Local include files                         */
/*--------------------------------------------------------------------*/

#include "../readcfg.h"
#include "../tools.h"
#include "w32tools.h"

/*--------------------------------------------------------------------*/
/*                         Global definitions                         */
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/*                          Global variables                          */
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/*                           Local variables                          */
/*--------------------------------------------------------------------*/

typedef  BOOL (WINAPI* PGFDE)( LPCTSTR, PULARGE_INTEGER,
                              PULARGE_INTEGER, PULARGE_INTEGER );


unsigned long getfree (char *path) {
 { /*  w95OSR2, wNT, ... */
  PGFDE pGetDiskFreeSpaceEx;
  ULARGE_INTEGER i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;

  pGetDiskFreeSpaceEx = (PGFDE)GetProcAddress( GetModuleHandle("kernel32.dll"),
                           "GetDiskFreeSpaceExA");

  if (pGetDiskFreeSpaceEx)
  {
    if( pGetDiskFreeSpaceEx (path,
                (PULARGE_INTEGER)&i64FreeBytesToCaller,
                (PULARGE_INTEGER)&i64TotalBytes,
                (PULARGE_INTEGER)&i64FreeBytes)
      ) {

      if( i64FreeBytesToCaller.u.HighPart > 0 ) {
        Log( 6, "GetDiskFreeSpaceEx() returns too big value (%lu*2^32) and getfree() is return ULONG_MAX (%lu)",i64FreeBytesToCaller.u.HighPart,ULONG_MAX);
        return ULONG_MAX;
      }
      return (unsigned long)(i64FreeBytesToCaller.QuadPart>>10 & ULONG_MAX);
    }
  }
 }

 { /* w95 4.0.950 */
  char RPN[MAXPATHLEN];	/* root path  */
  char *pRPN;             /* Pointer to Root path */
  DWORD SPC;				/* sectors per cluster */
  DWORD BPS;				/* bytes per sector    */
  DWORD FC;				/* number of free clusters  */
  DWORD TNC;				/* total number of clusters */
  BOOL rc;

  pRPN = RPN;
  if (isalpha(path[0]) && path[1] == ':' ) {
	  /* Drive letter */
	  RPN[0] = path[0];
	  RPN[1] = ':';
	  RPN[2] = '\\';
	  RPN[3] = '\0';
  } else if (path[0] == '\\' && path[1] == '\\') {
	  /* UNC path */
	  int i;
      RPN[0] = '\\';
	  RPN[1] = '\\';
	  i = 2;
	  /* copy server name.... */
      do {
		  RPN[i] = path[i];
	  } while (path[i++] != '\\');
      /* .... and share name */
      do {
		  RPN[i] = path[i];
	  } while (path[i++] != '\\');
      
      RPN[i] = '\0';

  } else {
	  /* Current Drive */
	  pRPN = NULL;
  }
  rc = GetDiskFreeSpace(pRPN,&SPC,&BPS,&FC,&TNC);
  if (rc != TRUE) {
    Log (1, "GetDiskFreeSpace error: return code = %lu", GetLastError());
    return ULONG_MAX;		    /* Assume enough disk space */
  } else {
    if (BPS * SPC >= 1024)
      return (unsigned long) ((BPS * SPC / 1024l) * FC);
    else
      return (unsigned long) (FC / (1024 / (BPS * SPC)));
  }
 }
}
