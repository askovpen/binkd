/*
 *  zlibdl.c -- zlib dynamic load interface
 *
 *  zlibdl.c is a part of binkd project
 *
 *  Copyright (C) 2003  val khokhlov, FIDONet 2:550/180
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */
/*
 * $Id: zlibdl.c,v 2.2 2003/09/12 09:09:38 val Exp $
 */

#include <windows.h>
#include "zlibdl.h"

zlib_compress_func *dl_compress = NULL, *dl_uncompress = NULL;

/* loading function */
int zlib_init(const char *dll_name) {
#ifdef WIN32
  HINSTANCE hl = LoadLibrary(dll_name);
  dl_compress = (void*)GetProcAddress(hl, "compress");
  dl_uncompress = (void*)GetProcAddress(hl, "uncompress");
#endif
  return dl_compress && dl_uncompress ? 1 : 0;
}
