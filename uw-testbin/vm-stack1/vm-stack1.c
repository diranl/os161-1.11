#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE (4096)
#define PAGES     (9)
#define SIZE      (PAGE_SIZE * PAGES / sizeof(int))

int
main()
{
	unsigned int array[SIZE];
	unsigned int i = 0;

	for (i=0; i<SIZE; i++) {
		array[i] = i;
	}

	for (i=0; i<SIZE; i++) {
		if (array[i] != i) {
			printf("FAILED array[%d] = %u != %d\n", i, array[i], i);
			exit(1);
		}
	}

	printf("SUCCEEDED\n");
	exit(0);
}
