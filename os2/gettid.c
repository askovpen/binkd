/*
 * $Id: gettid.c,v 2.0 2001/01/10 12:12:40 gul Exp $
 *
 * Revision history:
 * $Log: gettid.c,v $
 * Revision 2.0  2001/01/10 12:12:40  gul
 * Binkd is under CVS again
 *
 *
 */
#ifdef __WATCOMC__
  #define __IBMC__ 0
  #define __IBMCPP__ 0
#endif

#define INCL_DOS
#include <os2.h>

int gettid()
{ 
  PTIB ptib;
  PPIB ppib;
 
  DosGetInfoBlocks(&ptib, &ppib);
 
  return (int) (ptib->tib_ptib2->tib2_ultid);
}

