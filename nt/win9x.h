/*
 *  win9x.h -- Windows 95/98/ME support for binkd definition file
 *
 *  win9x.h is a part of binkd project
 *
 *  Copyright (C) 2002 Alexander Reznikov, homebrewer@yandex.ru (Fido 2:4600/220)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: win9x.h,v 2.2 2002/11/13 07:58:19 gul Exp $
 *
 * Revision history:
 * $Log: win9x.h,v $
 * Revision 2.2  2002/11/13 07:58:19  gul
 * Add CVS macros
 *
 *
 */

#ifndef _win9x_h
#define _win9x_h
#ifdef BINKDW9X
void CreateWin9xThread(PHANDLER_ROUTINE phandler);
/*
void DestroyWin9xThread();
*/

// TempConsole
void AllocTempConsole();
void FreeTempConsole();
#endif
#endif

