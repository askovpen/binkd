/*
 *  dirent.h -- additional functions not found in IBM VisualAge C / CSet RTL
 *
 *  dirent.h is a part of binkd project
 *
 *  Copyright (C) 1997 Victor Pashkevich, 2:451/30@FidoNet
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: dirent.h,v 2.1 2003/03/01 20:26:36 gul Exp $
 *
 * Revision history:
 * $Log: dirent.h,v $
 * Revision 2.1  2003/03/01 20:26:36  gul
 * *** empty log message ***
 *
 *
 */

#ifndef __DIRENT_H__
#define __DIRENT_H__

#ifdef __cplusplus
extern "C" {
#endif

struct dirent {
   char d_name[256];
};

typedef struct {
   unsigned long hdir;
   char *        dirname;
   unsigned      nfiles;
   char *        bufp;
   char          buf[512];
} DIR;

DIR            * _Optlink   opendir(const char * __dirname);
struct dirent  * _Optlink   readdir(DIR * __dir);
int              _Optlink  closedir(DIR * __dir);
void             _Optlink rewinddir(DIR * __dir);

#ifdef __cplusplus
}
#endif


#endif
