/*--------------------------------------------------------------------*/
/*       S e m . c                                                    */
/*                                                                    */
/*       Part of BinkD project                                        */
/*       Semaphore support (NT) for bsy.c module                      */
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
 * $Id: sem.c,v 2.3 2003/03/31 19:35:17 gul Exp $
 *
 * Revision history:
 * $Log: sem.c,v $
 * Revision 2.3  2003/03/31 19:35:17  gul
 * Clean semaphores usage
 *
 * Revision 2.2  2003/03/11 11:42:23  gul
 * Use event semaphores for exit threads
 *
 * Revision 2.1  2003/02/13 19:44:45  gul
 * Change \r\n -> \n
 *
 * Revision 2.0  2001/01/10 12:12:40  gul
 * Binkd is under CVS again
 *
 * Revision 1.2  1996/12/06  19:24:37 ufm
 * Revriting from "Semaphore" to "Mutex" object
 *
 * Revision 1.1  1996/12/05  03:37:50  mff
 * Support for multiple semaphores
 *
 * Revision 0.01  1996/12/04  14:52:58  ufm
 *      First revision
 *
 */

 static const char rcsid[] =
      "$Id: sem.c,v 2.3 2003/03/31 19:35:17 gul Exp $";

/*--------------------------------------------------------------------*/
/*                        System include files                        */
/*--------------------------------------------------------------------*/

#include <windows.h>
#include <winsock.h>


/*--------------------------------------------------------------------*/
/*                        Local include files                         */
/*--------------------------------------------------------------------*/

#include "..\tools.h"

/*--------------------------------------------------------------------*/
/*                         Global definitions                         */
/*--------------------------------------------------------------------*/

#define BsySem (*(HANDLE*)vpSem)

#define EvtSem (*(HANDLE*)vpSem)

/*--------------------------------------------------------------------*/
/*    int InitSem(void)                                               */
/*                                                                    */
/*    Initialise Semaphores.                                          */
/*--------------------------------------------------------------------*/

int _InitSem(void *vpSem) {

   BsySem = CreateMutex(NULL,FALSE,NULL);
   if (BsySem == NULL) {
      Log(0,"Unable to create Mutex object");
      return (-1);
   }
   return(0);
}

/*--------------------------------------------------------------------*/
/*    int CleanSem(void *)                                            */
/*                                                                    */
/*    Clean Semaphores.                                               */
/*--------------------------------------------------------------------*/

int _CleanSem(void *vpSem) {
   CloseHandle(BsySem);
   return(0);
}

/*--------------------------------------------------------------------*/
/*    int LockSem(void *)                                             */
/*                                                                    */
/*    Wait & lock semaphore                                           */
/*--------------------------------------------------------------------*/

int _LockSem(void *vpSem) {
   
   if (WaitForSingleObject(BsySem,INFINITE) == WAIT_FAILED) {
       Log(0,"Sem.c: WaitForSingleObject failed. Error code : %lx",GetLastError());
       return (-1);
   }
   return(0);
}

/*--------------------------------------------------------------------*/
/*    int ReleaseSem(void *)                                          */
/*                                                                    */
/*    Release Semaphore.                                              */
/*--------------------------------------------------------------------*/

int _ReleaseSem(void *vpSem) {
   
   ReleaseMutex(BsySem);
   return(0);
}

/*--------------------------------------------------------------------*/
/*    int InitEventSem(void *)                                        */
/*                                                                    */
/*    Initialise Event Semaphores.                                    */
/*--------------------------------------------------------------------*/

int _InitEventSem(void *vpSem) {

   EvtSem = CreateEvent(NULL,FALSE,FALSE,NULL);
   if (EvtSem == NULL) {
      Log(0,"Unable to create Event object");
      return (-1);
   }
   return(0);
}

/*--------------------------------------------------------------------*/
/*    int PostSem(void *)                                             */
/*                                                                    */
/*    Post Event Semaphores.                                          */
/*--------------------------------------------------------------------*/

int _PostSem(void *vpSem) {
   SetEvent(EvtSem);
   return(0);
}

/*--------------------------------------------------------------------*/
/*    int WaitSem(void *, int)                                        */
/*                                                                    */
/*    Wait Event Semaphores.                                          */
/*--------------------------------------------------------------------*/

int _WaitSem(void *vpSem, int timeout) {
   if (WaitForSingleObject(EvtSem, timeout * 1000l) == WAIT_TIMEOUT)
      return -1;
   return(0);
}

/*--------------------------------------------------------------------*/
/*    int CleanEventSem(void *)                                       */
/*                                                                    */
/*    Clean Event Semaphores.                                         */
/*--------------------------------------------------------------------*/

int _CleanEventSem(void *vpSem) {
   CloseHandle(EvtSem);
   return(0);
}

