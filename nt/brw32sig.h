/*****************************************************************************
$Id: brw32sig.h,v 2.5 2003/10/07 14:41:04 stas Exp $
Part of BinkD project
Handle Ctrl-C & Ctrl-Break signals on Win32 declarations


Copyright (C) 2003 Stas Degteff g@grumbler.org 2:5080/102@fidonet

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version. See COPYING for details.

******************************************************************************/
#include <windows.h>

/*--------------------------------------------------------------------*/
/*    BOOL SigHandlerExit(DWORD SigType)                              */
/*                                                                    */
/*    Signal handler, exit(0) after (SigHandler()==FALSE) call        */
/*    For "manual" call only, not for OS signal handlers              */
/*--------------------------------------------------------------------*/
BOOL SigHandlerExit(DWORD SigType);

/* Set signal handler */
int set_break_handlers(void);
