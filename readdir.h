/*
 *  readdir.h -- The header to get POSIX directory interface out of
 *               misc compilers
 *
 *  ftnq.h is a part of binkd project
 *
 *  Copyright (C) 1996  Dima Maloff, 5047/13
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: readdir.h,v 1.1.1.1 2001/01/10 11:34:58 gul Exp $
 *
 * $Log: readdir.h,v $
 * Revision 1.1.1.1  2001/01/10 11:34:58  gul
 * BinkD sources are under CVS again
 *
 * Revision 1.1  1996/12/29  09:46:20  mff
 * Initial revision
 *
 */
#ifndef _readdir_h
#define _readdir_h

#if defined(__WATCOMC__) || defined(VISUALCPP)
#include <direct.h>
#include <sys/utime.h>
#else
#include <dirent.h>
#include <utime.h>
#endif

#if defined(VISUALCPP)
#include "NT/dirwin32.h"
#endif

#if defined(WATCOMC_CLOSEDIR_BUG)
#define INCL_DOS
#include <os2.h>
#define closedir(d) (DosFindClose(*(HDIR *)((d)->d_dta)-2), closedir(d))
#endif

#endif
