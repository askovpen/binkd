/*
 *  perlhooks.h -- perl-hooks interface
 *
 *  perlhooks.h is a part of binkd project
 *
 *  Copyright (C) 2003  val khokhlov, FIDONet 2:550/180
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */
/*
 * $Id: perlhooks.h,v 2.4 2003/08/18 09:41:00 gul Exp $
 *
 * $Log: perlhooks.h,v $
 * Revision 2.4  2003/08/18 09:41:00  gul
 * Little cleanup in handle perl errors
 *
 * Revision 2.3  2003/08/18 07:29:09  val
 * multiple changes:
 * - perl error handling made via fork/thread
 * - on_log() perl hook
 * - perl: msg_send(), on_send(), on_recv()
 * - unless using threads define log buffer via xalloc()
 *
 * Revision 2.2  2003/08/13 08:20:45  val
 * try to avoid mixing Log() output and Perl errors in stderr
 *
 * Revision 2.1  2003/06/20 10:37:02  val
 * Perl hooks for binkd - initial revision
 *
*/
#ifndef _PERLHOOKS_H_
#define _PERLHOOKS_H_

#include "prothlp.h"
#include "protocol.h"
#include "protoco2.h"

enum perl_skip_type { SKIP_ND=1, SKIP_D=2 };

extern int perl_ok;           /* if sub is ok to run, its bit set to 1 */
extern char *perl_subnames[]; /* names for perl subs */

extern int perl_manages_queue; /* queue is managed from perl: sorting, etc */
extern int perl_wants_queue;   /* export queue to perl subs */

extern int perl_errpid;        /* pid or tid which handle perl errors */

int perl_init(char *); /* init root perl, parse hooks file, return success */
void perl_setup(void); /* set config vars to root perl */
void perl_done(int);   /* deallocate root perl, call on_exit() if arg=1 */
#ifdef HAVE_THREADS
void *perl_init_clone();        /* clone root perl */
void perl_done_clone(void *);   /* destruct a clone */
#endif

void perl_on_start(void);            /* start, after init */
void perl_on_exit(void);             /* exit, just before destruction */

int perl_on_call(FTN_NODE *);        /* before outgoing call */
int perl_on_error(FTN_ADDR *, const char *, const int); /* on errors: bad_try() */
char *perl_on_handshake(STATE *);    /* before xmitting ADR */
char *perl_after_handshake(STATE *); /* after handshake complete */
void perl_after_session(STATE *, char *); /* after session done */

int perl_before_recv(STATE *, off_t offs); /* before receiving file */
int perl_after_recv(STATE *, char *netname, off_t size, time_t time, 
                    FTN_ADDR *fa, int nfa, char *tmp_name, 
                    char *real_name);    /* after file has been received */
int perl_before_send(STATE *);       /* before sending file */
int perl_after_sent(STATE *, int);   /* after file has been sent */

int perl_on_log(char *, int, int *); /* when writing string to log */

int perl_on_send(STATE *, t_msg *, char **, char **); /* on msg_send2 */
int perl_on_recv(STATE *, char *, int);               /* when recv a block */

#endif
