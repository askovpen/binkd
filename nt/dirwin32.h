/*
 *  dirwin32.h -- additional functions not found in Visual C++ RTL
 *
 *  dirwin32.h is a part of binkd project
 *
 *  Copyright (C) 1996-97 Mike Malakhov, ww@pobox.com (FiDO 2:5030/280)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */
/*
 * $Id: dirwin32.h,v 2.2 2003/02/28 20:39:08 gul Exp $
 *
 * $Log: dirwin32.h,v $
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

#ifdef VISUALCPP

#ifndef _DIRWIN32_H_
#define _DIRWIN32_H_

#include <io.h>
#include <stdlib.h>

typedef struct dirent {
   char        d_name[_MAX_PATH+1];  /* file's name */
#if 0
   char        d_dta[ 21 ];            /* disk transfer area */
   char        d_attr;                 /* file's attribute */
   unsigned short int d_time;          /* file's time */
   unsigned short int d_date;          /* file's date */
   long        d_size;                 /* file's size */
   unsigned short d_ino;               /* serial number (not used) */
   char        d_first;                /* flag for 1st time */
#endif

   struct _finddata_t _dt;
   char               _mask[_MAX_PATH+1];
   long               _handle;
   char               _first_time;
} DIR;

DIR* opendir(const char*);
DIR* readdir(DIR*);
int  closedir(DIR*);

#endif /* _DIRWIN32_H_ */

#endif /* VISUALCPP */
