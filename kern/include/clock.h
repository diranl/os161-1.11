#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "opt-synchprobs.h"

/*
 * Time-related definitions.
 *
 * hardclock() is called from the timer interrupt HZ times a second.
 * gettime() may be used to fetch the current time of day.
 * getinterval() computes the time from time1 to time2.
 */

/* hardclocks per second */
#if OPT_SYNCHPROBS
/* Make synchronization more exciting :) */
/* #define HZ  10000 */
/* Actually, don't make it more exciting, because it uses too much CPU time */
/* If you wish to change it back to 10000 and this will be run in a shared */
/* environment (i.e. not at home) you should also modify sys161 */
/* by changing the select statement on line 333 of main/clock.c */
/* That change will slow down the simulator so it doesn't hog the CPU */
/* See comments in that file for further details */
#define HZ  100
#else
/* More realistic value */
#define HZ  100
#endif

void hardclock(void);

void gettime(time_t *seconds, u_int32_t *nanoseconds);

void getinterval(time_t secs1, u_int32_t nsecs,
		 time_t secs2, u_int32_t nsecs2,
		 time_t *rsecs, u_int32_t *rnsecs);

#endif /* _CLOCK_H_ */
