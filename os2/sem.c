/*--------------------------------------------------------------------*/
/*       S e m . c                                                    */
/*                                                                    */
/*       Part of BinkD project                                        */
/*       Semaphore support (OS/2) for bsy.c module                    */
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/*       Copyright (c) 1996 by Fydodor Ustinov                        */
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
 * $Id: sem.c,v 2.3 2003/03/31 19:56:12 gul Exp $
 *
 * Revision history:
 * $Log: sem.c,v $
 * Revision 2.3  2003/03/31 19:56:12  gul
 * minor fix in close semaphores functions
 *
 * Revision 2.2  2003/03/31 19:35:17  gul
 * Clean semaphores usage
 *
 * Revision 2.1  2003/03/11 11:42:23  gul
 * Use event semaphores for exit threads
 *
 * Revision 2.0  2001/01/10 12:12:40  gul
 * Binkd is under CVS again
 *
 * Revision 1.2  1996/11/05 04:06:06  mff
 *      Added support for multiple semaphores
 *
 * Revision 0.01  1996/12/04  14:52:58  ufm
 *      First revision
 *
 */

#include "../sys.h"
#include "../tools.h"

#define INCL_DOS
#include <os2.h>

#define hmtx (*(HMTX*)vpSem)

#define hevt (*(HEV*)vpSem)

/*--------------------------------------------------------------------*/
/*    int InitSem(void *)                                             */
/*                                                                    */
/*    Initialise Mutex Semaphore.                                     */
/*--------------------------------------------------------------------*/

int _InitSem(void *vpSem) {

  if (DosCreateMutexSem (0, &hmtx, 0, FALSE)) {
     Log (0, "DosCreateMutexSem: error");
     return(-1);
   }
   return(0);
}

/*--------------------------------------------------------------------*/
/*    int InitEventSem(void *)                                        */
/*                                                                    */
/*    Initialise Event Semaphore.                                     */
/*--------------------------------------------------------------------*/

int _InitEventSem(void *vpSem) {

  if (DosCreateEventSem (NULL, &hevt, 0, FALSE)) {
     Log (0, "DosCreateEventSem: error");
     return(-1);
   }
   return(0);
}

/*--------------------------------------------------------------------*/
/*    int CleanSem(void *)                                            */
/*                                                                    */
/*    Clean Mutex Semaphore.                                          */
/*--------------------------------------------------------------------*/

int _CleanSem(void *vpSem) {
  if (hmtx)
  { DosCloseMutexSem (hmtx);
    hmtx = 0;
  }
  return (0);
}

/*--------------------------------------------------------------------*/
/*    int LockSem(void *)                                             */
/*                                                                    */
/*    Wait & lock semaphore                                           */
/*--------------------------------------------------------------------*/

int _LockSem(void *vpSem) {
  DosRequestMutexSem (hmtx, SEM_INDEFINITE_WAIT);
  return (0);
}

/*--------------------------------------------------------------------*/
/*    int ReleaseSem(void *)                                          */
/*                                                                    */
/*    Release Semaphore.                                              */
/*--------------------------------------------------------------------*/

int _ReleaseSem(void *vpSem) {
  DosReleaseMutexSem (hmtx);
  return (0);
}

/*--------------------------------------------------------------------*/
/*    int PostSem(void *)                                             */
/*                                                                    */
/*    Post Event Semaphore.                                           */
/*--------------------------------------------------------------------*/

int _PostSem(void *vpSem) {
  DosPostEventSem (hevt);
  return (0);
}

/*--------------------------------------------------------------------*/
/*    int WaitSem(void *, int)                                        */
/*                                                                    */
/*    Wait Event Semaphore.                                           */
/*--------------------------------------------------------------------*/

int _WaitSem(void *vpSem, int timeout) {
  ULONG semcount;
  if (DosWaitEventSem (hevt, timeout * 1000ul))
    return -1;
  DosResetEventSem (hevt, &semcount);
  return 0;
}

/*--------------------------------------------------------------------*/
/*    int CleanEventSem(void *)                                       */
/*                                                                    */
/*    Clean Semaphores.                                               */
/*--------------------------------------------------------------------*/

int _CleanEventSem(void *vpSem) {
  if (hevt)
  { DosCloseEventSem (hevt);
    hevt = 0;
  }
}

