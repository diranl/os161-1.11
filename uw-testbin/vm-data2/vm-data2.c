#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE       (4096)
#define PAGES           (2048)  /* 8 MB worth of data : won't all fit */
#define SIZE            (PAGE_SIZE * PAGES / sizeof(int))
#define NUM_REFS        (2)
#define PAGES_TO_TOUCH  (1536) /* Touching 6 MB of data */

/* Create a very large array */
unsigned int array[SIZE];

int
main()
{
	unsigned int i = 0;
	unsigned int index = 0;
	unsigned int refs = 0;

	for (refs = 0; refs < NUM_REFS; refs++) {
		for (i=0; i<PAGES_TO_TOUCH; i++) {
			index = i * PAGE_SIZE  / sizeof(int);
			array[index] = i;
		}
	}

	for (i=0; i<PAGES_TO_TOUCH; i++) {
		index = i * PAGE_SIZE  / sizeof(int);
		if (array[index] != i) {
			printf("FAILED array[%d] = %u != %d\n", i, array[index], i);
			exit(1);
		}
	}

	printf("SUCCEEDED\n");
	exit(0);
}
