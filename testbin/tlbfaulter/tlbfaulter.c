/* 
 * tlbfaulter.c
 *
 * 	This program creates an array larger than the TLB footprint,
 *      but hopefully smaller than memory.
 *      It first touches each page of the array once, which should cause
 *      each page to be loaded into memory.
 *      Then it touches the pages sequentially in a tight loop - the
 *      goal is to force the TLB to be filled quickly, so that TLB
 *      replacements will be necessary.
 *
 *      If this generates "out of memory" errors, you will need
 *      to increase the memory size of the machine (in sys161.conf)
 *      to run this test.
 */

#include <stdio.h>
#include <stdlib.h>

/* 
 * set these to match the page size of the 
 * machine and the number of entries in the TLB
 */
#define PageSize	4096
#define TLBSize	        64

/* an array a bit larger than the size of the TLB footprint */
#define ArraySize ((TLBSize+5)*PageSize)
char tlbtest[ArraySize];

int
main()
{
	int i,j;

	printf("Starting the tlbfaulter program\n");

	/* load up the array */
	for (i=0; i<ArraySize; i++) {
	  tlbtest[i]= 'a';
	}
	
	printf("tlbfaulter: array initialization completed\n");
	
	/* touch one array entry on each page, sequentially, 5 times */
	for(j=0; j<5; j++) {
	  for (i=0; i<ArraySize; i+=PageSize) {
	    tlbtest[i] += 1;
	  }
	}
	
	printf("tlbfaulter: array updates completed\n");

	/* check the array values we updated */
	for (i=0; i<ArraySize; i+=PageSize) {
          if (tlbtest[i] != ('a'+5)) {
            printf("Test failed! Unexpected value at array position %d\n", i);
            return(1);
          }
	}

	printf("SUCCESS\n");
	
	return 0;
}

