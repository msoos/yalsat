/*-------------------------------------------------------------------------*/
/* Copyright 2013-2019 Armin Biere Johannes Kepler University Linz Austria */
/*-------------------------------------------------------------------------*/

#ifndef LIBYALS_H_INCLUDED
#define LIBYALS_H_INCLUDED

/*------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------------*/

typedef struct Yals Yals;

/*------------------------------------------------------------------------*/

Yals * yals_new ();
void yals_del (Yals *);

/*------------------------------------------------------------------------*/

typedef void * (*YalsMalloc)(void*,size_t);
typedef void * (*YalsRealloc)(void*,void*,size_t,size_t);
typedef void (*YalsFree)(void*,void*,size_t);

Yals * yals_new_with_mem_mgr (void*, YalsMalloc, YalsRealloc, YalsFree);

/*------------------------------------------------------------------------*/

void yals_srand (Yals *, unsigned long long seed);
long long yals_setopt (Yals *, const char * name, long long val);
void yals_setprefix (Yals *, const char *);
void yals_setout (Yals *, FILE *);
void yals_setphase (Yals *, long long lit);
void yals_setflipslimit (Yals *, long long);
void yals_setmemslimit (Yals *, long long);

long long yals_getopt (Yals *, const char * name);
void yals_usage (Yals *);
void yals_showopts (Yals *);

/*------------------------------------------------------------------------*/

void yals_add (Yals *, long long lit);

long long yals_sat (Yals *);

/*------------------------------------------------------------------------*/

long long yals_flips (Yals *);
long long yals_mems (Yals *);

long long yals_minimum (Yals *);
long long yals_lkhd (Yals *);
long long yals_deref (Yals *, long long lit);

const long long * yals_minlits (Yals *);

/*------------------------------------------------------------------------*/

void yals_stats (Yals *);

/*------------------------------------------------------------------------*/

void yals_seterm (Yals *, long long (*term)(void*), void*);

void yals_setime (Yals *, double (*time)(void));

void yals_setmsglock (Yals *,
       void (*lock)(void*), void (*unlock)(void*), void*);

/*------------------------------------------------------------------------*/

#endif
