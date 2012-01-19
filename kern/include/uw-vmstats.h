#ifndef VM_STATS_H
#define VM_STATS_H

#include "opt-A3.h"
#if OPT_A3
/* UW specific code - This won't be needed or used until assignment 3 */

/* belongs in kern/include/vmstat.h */

/* ----------------------------------------------------------------------- */
/* Virtual memory stats */
/* Tracks stats on user programs */

/* !!!!!! NOTE !!!! WARNING !!!!!
 * All of the functions whose names begin with '_'
 * assume that atomicity is ensured elsewhere
 * (i.e., outside of these routines).
 * All of the functions whose names do not begin with '_'
 * use the lock provided in this code.
 *
 * Generally you will use the functions whose names
 * do not begin with '_'.
 *
 * However, you **may** find the functions beginning 
 * with '_' can be useful if e.g., 
 * atomicity is ensured in another way. For example 
 * the thread is already holding a lock that ensures
 * atomic access to these functions or they are
 * called while interrupts are off.
 *
 */

/* These are the different stats that get tracked.
 * See vmstats.c for strings corresponding to each stats.
 */

/* DO NOT ADD OR CHANGE WITHOUT ALSO CHANGING vmstats.h */
#define VMSTAT_TLB_FAULT              (0)
#define VMSTAT_TLB_FAULT_FREE         (1)
#define VMSTAT_TLB_FAULT_REPLACE      (2)
#define VMSTAT_TLB_INVALIDATE         (3)
#define VMSTAT_TLB_RELOAD             (4)
#define VMSTAT_PAGE_FAULT_ZERO        (5)
#define VMSTAT_PAGE_FAULT_DISK        (6)
#define VMSTAT_ELF_FILE_READ          (7)
#define VMSTAT_SWAP_FILE_READ         (8)
#define VMSTAT_SWAP_FILE_WRITE        (9)
#define VMSTAT_COUNT                 (10)

/* ----------------------------------------------------------------------- */

/* Initialize the statistics: must be called before using */
void vmstats_init();                     /* uses locking */
void _vmstats_init();                    /* atomicity must be ensured elsewhere */

/* Increment the specified count 
 * Example use: 
 *   vmstats_inc(VMSTAT_TLB_FAULT);
 *   vmstats_inc(VMSTAT_PAGE_FAULT_ZERO);
 */
void vmstats_inc(unsigned int index);    /* uses locking */
void _vmstats_inc(unsigned int index);   /* atomicity must be ensured elsewhere */

/* Print the statistics: assumes that at least vmstats_init has been called */
void vmstats_print();                    /* uses locking */
void _vmstats_print();                   /* atomicity must be ensured elsewhere */

#endif /* OPT_A3 */
#endif /* VM_STATS_H */
