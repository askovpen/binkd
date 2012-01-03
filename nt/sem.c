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
 * $Id: sem.c,v 2.9 2012/01/03 17:25:35 green Exp $
 *
 * Revision history:
 * $Log: sem.c,v $
 * Revision 2.9  2012/01/03 17:25:35  green
 * Implemented IPv6 support
 * - replace (almost) all getXbyY function calls with getaddrinfo/getnameinfo (RFC2553) calls
 * - Add compatibility layer for target systems not supporting RFC2553 calls in rfc2553.[ch]
 * - Add support for multiple listen sockets -- one for IPv4 and one for IPv6 (use V6ONLY)
 * - For WIN32 platform add configuration parameter IPV6 (mutually exclusive with BINKD9X)
 * - On WIN32 platform use Winsock2 API if IPV6 support is requested
 * - config: node IP address literal + port supported: [<ipv6 address>]:<port>
 *
 * Revision 2.8  2003/08/26 22:18:49  gul
 * Fix compilation under w32-mingw and os2-emx
 *
 * Revision 2.7  2003/08/05 05:36:14  hbrew
 * 'static const char rcsid[]' removed
 *
 * Revision 2.6  2003/03/31 22:11:34  gul
 * Fixed semaphores usage
 *
 * Revision 2.5  2003/03/31 21:49:01  gul
 * Avoid infinite recursion
 *
 * Revision 2.4  2003/03/31 19:56:11  gul
 * minor fix in close semaphores functions
 *
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

/*--------------------------------------------------------------------*/
/*                        System include files                        */
/*--------------------------------------------------------------------*/

#include "../iphdr.h"


/*--------------------------------------------------------------------*/
/*                        Local include files                         */
/*--------------------------------------------------------------------*/

#include "../readcfg.h"
#include "../tools.h"

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
   if (BsySem) {
      CloseHandle(BsySem);
      BsySem = 0;
   }
   return(0);
}

/*--------------------------------------------------------------------*/
/*    int LockSem(void *)                                             */
/*                                                                    */
/*    Wait & lock semaphore                                           */
/*--------------------------------------------------------------------*/

int _LockSem(void *vpSem) {
   unsigned long errcode;

   if (BsySem == 0) return (-1);
   if (WaitForSingleObject(BsySem,INFINITE) == WAIT_FAILED) {
       errcode = GetLastError();
       _CleanSem(vpSem);
       Log(0, "Sem.c: WaitForSingleObject failed. Error code : %lx", errcode);
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
   
   if (BsySem == 0) return (-1);
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
   if (EvtSem == 0) return (-1);
   SetEvent(EvtSem);
   return(0);
}

/*--------------------------------------------------------------------*/
/*    int WaitSem(void *, int)                                        */
/*                                                                    */
/*    Wait Event Semaphores.                                          */
/*--------------------------------------------------------------------*/

int _WaitSem(void *vpSem, int timeout) {
   if (EvtSem == 0) return (-1);
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
   if (EvtSem) {
      CloseHandle(EvtSem);
      EvtSem = 0;
   }
   return(0);
}

