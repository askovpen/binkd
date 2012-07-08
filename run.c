/*
 *  run.c -- Run external programs
 *
 *  run.c is a part of binkd project
 *
 *  Copyright (C) 1996-1997  Dima Maloff, 5047/13
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: run.c,v 2.6 2003/10/29 21:08:39 gul Exp $
 *
 * $Log: run.c,v $
 * Revision 2.6  2003/10/29 21:08:39  gul
 * Change include-files structure, relax dependences
 *
 * Revision 2.5  2003/08/26 21:01:10  gul
 * Fix compilation under unix
 *
 * Revision 2.4  2003/04/07 18:22:16  gul
 * Wait for external process under win32 bugfix
 *
 * Revision 2.3  2003/04/06 08:01:32  gul
 * Close handles after CreateProcess()
 *
 * Revision 2.2  2003/04/06 07:54:41  gul
 * Change wait for child process function for win32
 *
 * Revision 2.1  2001/10/27 08:07:17  gul
 * run and run_args returns exit code of calling process
 *
 * Revision 2.0  2001/01/10 12:12:39  gul
 * Binkd is under CVS again
 *
 * Revision 1.1  1997/03/28  06:16:56  mff
 * Initial revision
 *
 */

#include <stdlib.h>
#include <string.h>
#include <signal.h>
#if defined WIN32
#include <windows.h>
#endif

#include "run.h"
#include "tools.h"

int run (char *cmd)
{
  int rc=-1;
#if !defined(WIN32) && !defined(EMX)
  Log (LL_WARN, "executing `%s'", cmd);
  Log (LL_WARN, "rc=%i", (rc=system (cmd)));
#elif defined(EMX)
  sigset_t s;
    
  sigemptyset(&s);
  sigaddset(&s, SIGCHLD);
  sigprocmask(SIG_BLOCK, &s, NULL);
  Log (LL_WARN, "executing `%s'", cmd);
  Log (LL_WARN, "rc=%i", (rc=system (cmd)));
  sigprocmask(SIG_UNBLOCK, &s, NULL);
#else /* WIN32 */
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  DWORD dw;
  char *cs, *sp=getenv("COMSPEC");

  Log (LL_WARN, "executing `%s'", cmd);
  memset(&si, 0, sizeof(si));
  si.cb=sizeof(si);
  if(!sp) sp="command";
  cs=(char*)malloc(strlen(sp)+strlen(cmd)+6);
  dw=CREATE_DEFAULT_ERROR_MODE;
  strcpy(cs, sp);
  strcat(cs, " /C ");
  sp=cmd;
  if (sp[0]=='@')
  {
    dw|=CREATE_NEW_CONSOLE|CREATE_NEW_PROCESS_GROUP;
    sp++;
    if (sp[0]=='@')
    {
      si.dwFlags=STARTF_USESHOWWINDOW;
      si.wShowWindow=SW_HIDE;
      sp++;
    }
    else 
      si.lpTitle=sp;
  }
  strcat(cs, sp);
  if (!CreateProcess(NULL, cs, NULL, NULL, 0, dw, NULL, NULL, &si, &pi))
    Log (LL_CRIT, "Error in CreateProcess()=%ld", (long)GetLastError());
  else if (sp==cmd)
  {
    if (WaitForSingleObject(pi.hProcess, INFINITE) != WAIT_OBJECT_0)
      Log (LL_CRIT, "Error in WaitForSingleObject()=%ld", (long)GetLastError());
    else if (!GetExitCodeProcess(pi.hProcess, &dw))
      Log (LL_CRIT, "Error in GetExitCodeProcess()=%ld", (long)GetLastError());
    else
      Log (LL_WARN, "rc=%i", rc = (int)dw);
  }
  free(cs);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
#endif
  return rc;
}
