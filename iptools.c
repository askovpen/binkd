/*
 *  iptools.c -- Some useful TCP/IP utils
 *
 *  iptools.c is a part of binkd project
 *
 *  Copyright (C) 1997-1998  Dima Maloff, 5047/13
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */

/*
 * $Id: iptools.c,v 2.1 2003/02/22 11:45:41 gul Exp $
 *
 * $Log: iptools.c,v $
 * Revision 2.1  2003/02/22 11:45:41  gul
 * Do not resolve hosts if proxy or socks5 using
 *
 * Revision 2.0  2001/01/10 12:12:38  gul
 * Binkd is under CVS again
 *
 * Revision 1.3  1998/06/19  05:19:33  mff
 * changes in get_hostname()
 *
 * Revision 1.2  1997/10/23  04:01:29  mff
 * +find_port(), minor changes for Amiga port
 *
 * Revision 1.1  1997/03/28  06:52:14  mff
 * Initial revision
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#if !defined(WIN32)
#include <sys/ioctl.h>
#endif

#include "iphdr.h"
#include "iptools.h"
#include "tools.h"
#include "readcfg.h"

/*
 * Finds ASCIIZ address
 */
const char *get_hostname (struct sockaddr_in *addr, char *host, int len)
{
  struct hostent *hp;
  struct sockaddr_in s;

  memcpy(&s, addr, sizeof(s));
  hp = ((backresolv == 0) ? 0 :
	gethostbyaddr ((char *) &s.sin_addr,
		       sizeof s.sin_addr,
		       AF_INET));

  strnzcpy (host, hp ? hp->h_name : inet_ntoa (s.sin_addr), len);

  return host;
}

#ifdef HAVE_THREADS
void copy_hostent(struct hostent *dest, struct hostent *src)
{
  int naddr;
  char **cp;

  memcpy(dest, src, sizeof(struct hostent));
  for (cp = src->h_addr_list, naddr = 0; cp && *cp; naddr++, cp++);
  dest->h_addr_list = malloc((naddr+1)*sizeof(dest->h_addr_list[0]));
  if (dest->h_addr_list)
  {
    dest->h_addr_list[0] = malloc(naddr*src->h_length);
    if (dest->h_addr_list[0])
    {
      for (cp = src->h_addr_list, naddr=0; cp && *cp; cp++, naddr++)
      {
        dest->h_addr_list[naddr] = dest->h_addr_list[0]+naddr*src->h_length;
        memcpy(dest->h_addr_list[naddr], *cp, src->h_length);
      }
      dest->h_addr_list[naddr] = NULL;
    }
  }
}
#endif

/*
 * Sets non-blocking mode for a given socket
 */
void setsockopts (SOCKET s)
{

#if defined(FIONBIO)
#if defined(UNIX) || defined(IBMTCPIP) || defined(AMIGA)
  int arg;

  arg = 1;
  if (ioctl (s, FIONBIO, (char *) &arg, sizeof arg) < 0)
    Log (1, "ioctl (FIONBIO): %s", TCPERR ());

#elif defined(WIN32)
  u_long arg;

  arg = 1;
  if (ioctlsocket (s, FIONBIO, &arg) < 0)
    Log (1, "ioctlsocket (FIONBIO): %s", TCPERR ());
#endif
#endif

#if defined(UNIX) || defined(EMX) || defined(AMIGA)
  if (fcntl (s, F_SETFL, O_NONBLOCK) == -1)
    Log (1, "fcntl: %s", strerror (errno));
#endif
}

/*
 * Find the port number (in the host byte order) by a port number string or
 * a service name. Find_port ("") will return binkp's port from
 * /etc/services or even (if there is no binkp entry) 24554.
 * Returns 0 on error.
 */
int find_port (char *s)
{
  struct servent *entry = getservbyname (*s ? s : PRTCLNAME, "tcp");

  if (entry)
    return ntohs (entry->s_port);
  if (*s == 0)
    return DEF_PORT;
  if (isdigit (*s))
    return atoi (s);

  Log (1, "%s: incorrect port", s);
  return 0;
}

/*
 * Find the host IP address list by a domain name or IP address string.
 * Returns NULL on error.
 */
struct hostent *find_host(char *host, struct hostent *he, char **alist)
{
  struct in_addr defaddr;
  struct hostent *hp;

  if (!isdigit(host[0]) ||
      (defaddr.s_addr = inet_addr (host)) == INADDR_NONE)
  {
    /* If not a raw ip address, try nameserver */
    Log (5, "resolving `%s'...", host);
#ifdef HAVE_THREADS
    LockSem(&hostsem);
#endif
    if ((hp = gethostbyname(host)) == NULL)
    {
      Log(1, "%s: unknown host", host);
#ifdef HAVE_THREADS
      ReleaseSem(&hostsem);
#endif
      return NULL;
    }
#ifdef HAVE_THREADS
    copy_hostent(he, hp);
    ReleaseSem(&hostsem);
    return he;
#endif
  }
  /* Raw ip address, fake */
  hp = he;
  hp->h_name = host;
  hp->h_aliases = 0;
  hp->h_addrtype = AF_INET;
  hp->h_length = sizeof (struct in_addr);
  hp->h_addr_list = alist;
  hp->h_addr_list[0] = (char *) &defaddr;
  hp->h_addr_list[1] = (char *) 0;
  return hp;
}

