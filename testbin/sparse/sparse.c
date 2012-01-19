/* 
 * sparse.c
 *
 * 	This program declares a large array, but only uses a small
 *      part of it.  The intention is that the full array will not
 *      fit into memory, but the used part of the array will fit.
 *
 *      This is similar to testbin/huge.
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* 
 * set these to match the page size of the 
 * machine and the number of pages of physical memory
 * in the machine.
 */
#define PageSize	4096
#define NumPages	128

/* a large array, 2 times the size of physical memory */
#define ArraySize (2*NumPages*PageSize)
char sparse[ArraySize];

int
main()
{
	int i,j;

	printf("Starting the sparse program\n");

	/* write some values into the array, but only
           touch one array entry on every 10th page */
	for (i=0; i<ArraySize; i+=(10*PageSize)) {
	  sparse[i]= 'a';
	}
	
	printf("stage [1] done\n");
	
	/* increment each location 5 times */
	for(j=0; j<5; j++) {
	  for (i=0; i<ArraySize; i+=(10*PageSize)) {
	    sparse[i] += 1;
	  }
	}
	
	printf("stage [2] done\n");
	
	/* check the values that were written */
	/* increment each location 5 times */
	for (i=0; i<ArraySize; i+=(10*PageSize)) {
	  if (sparse[i] != ('a'+5)) {
	    printf("Test failed! Unexpected value at array position %d\n", i);
	    return(1);
	  }
	}

	printf("SUCCESS\n");
	
	return 0;
}

