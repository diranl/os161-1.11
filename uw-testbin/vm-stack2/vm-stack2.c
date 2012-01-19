#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE             (4096)
#define STACK_PAGES_USED      (9)
#define STACK_ARRAY_ELEMS     (PAGE_SIZE * STACK_PAGES_USED / sizeof(int))
#define UNINIT_PAGES          (9)
#define UNINIT_ARRAY_ELEMS    (PAGE_SIZE * UNINIT_PAGES / sizeof(int))

unsigned int uninit[UNINIT_ARRAY_ELEMS];
unsigned int init[] = {
	0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 
 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 
 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 
 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 
};

#define INIT_ARRAY_ELEMS     (sizeof(init) / sizeof(int))

int
main()
{
	unsigned int array[STACK_ARRAY_ELEMS];
	unsigned int i = 0;

	/* check the uninitialized array before initialization */
	for (i=0; i<UNINIT_ARRAY_ELEMS; i++) {
		if (uninit[i] != 0) {
			printf("FAILED uninit[%d] = %u != %d\n", i, uninit[i], 0);
			exit(1);
		}
	}

	/* initialize the uninitialized data */
	for (i=0; i<UNINIT_ARRAY_ELEMS; i++) {
		uninit[i] = i * 100;
	}

	/* initialize the array on the stack */
	for (i=0; i<STACK_ARRAY_ELEMS; i++) {
		array[i] = i * 1000;
	}

	/* check the array on the stack */
	for (i=0; i<STACK_ARRAY_ELEMS; i++) {
		if (array[i] != i * 1000) {
			printf("FAILED array[%d] = %u != %d\n", i, array[i], i);
			exit(1);
		}
	}

	/* check the uninitialized array after initialization */
	for (i=0; i<UNINIT_ARRAY_ELEMS; i++) {
		if (uninit[i] != i * 100) {
			printf("FAILED uninit[%d] = %u != %d\n", i, uninit[i], i);
			exit(1);
		}
	}

	/* check the initialized array */
	for (i=0; i<INIT_ARRAY_ELEMS; i++) {
		if (init[i] != i) {
			printf("FAILED init[%d] = %u != %d\n", i, init[i], i);
			exit(1);
		}
	}

	printf("SUCCEEDED\n");
	exit(0);
}
