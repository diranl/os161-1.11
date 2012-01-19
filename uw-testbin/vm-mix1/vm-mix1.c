#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* This is creating a program that has
 * a few more text pages than the average
 * program we usually have.
 */

// #define DEBUG

extern void	call_all();

#define PAGE_SIZE           (4096)
#define DATA_BYTES          (3 * 1024 * 1024)
#define PAGES               (DATA_BYTES / PAGE_SIZE)
#define ELEM_SIZE           (sizeof(unsigned int))
#define ELEMS               ((PAGE_SIZE * PAGES / sizeof(unsigned int)) / 2)
#define ELEMS_PER_PAGE      (PAGE_SIZE / ELEM_SIZE)
#define NUM_REFS            (2)

#define STACK_PAGES_USED    (9)
#define STACK_ARRAY_ELEMS   (PAGE_SIZE * STACK_PAGES_USED / sizeof(unsigned int))

unsigned int init[] = {
  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
};

#define INIT_ARRAY_ELEMS     (sizeof(init) / sizeof(int))

unsigned int array1[ELEMS];
unsigned int array2[ELEMS];

void
write_data(unsigned int array[], unsigned int start)
{
	unsigned int ref = 0;
	unsigned int i = 0;

	for (ref = 0; ref < NUM_REFS-1; ref++) {
		for (i=0; i<ELEMS; i++) {
      array[i] = start + (i / ELEMS_PER_PAGE);
		}
	}
}

void
read_data(unsigned int array[], unsigned int start, const char *array_name)
{
  unsigned int ref = 0;
	unsigned int i = 0;

	for (ref = 0; ref < NUM_REFS-1; ref++) {
		for (i=0; i<ELEMS; i++) {
			if (array[i] != (start + (i / ELEMS_PER_PAGE))) {
				printf("FAILED in file %s at line %d %s[%d] = %u != %u ref = %d\n", 
                __FILE__, __LINE__, array_name, i, array[i], i, ref+1);
				exit(1);
			}
		}
  }
}

void
print_data(unsigned int array[])
{
	unsigned int i = 0;
  unsigned int count = 0;

	for (i=0; i<ELEMS; i+= (ELEMS_PER_PAGE)) {
		printf("[%10u] = %10u ", i, array[i]);
    if (((count+1) % 4) == 0) {
      printf("\n");
    }
    count++;
	}
  printf("\n");
}

void
do_work(unsigned int start)
{
	unsigned int stack_array[STACK_ARRAY_ELEMS];
	unsigned int i = 0;
  unsigned int array1_start = start;
  unsigned int array2_start = start + (ELEMS / (ELEMS_PER_PAGE)) + 10;

  printf("Checking uninitialized array1\n");
	/* check the uninitialized array1 before initialization */
	for (i=0; i<ELEMS; i++) {
		if (array1[i] != 0) {
			printf("FAILED in file %s at line %d: array1[%d] = %u != %d\n", __FILE__, __LINE__, i, array1[i], 0);
			exit(1);
		}
	}

  printf("Checking uninitialized array2\n");
	/* check the uninitialized array2 before initialization */
	for (i=0; i<ELEMS; i++) {
		if (array2[i] != 0) {
			printf("FAILED in file %s at line %d: array2[%d] = %u != %d\n", __FILE__, __LINE__, i, array2[i], 0);
			exit(1);
		}
	}

	for (i=0; i<STACK_ARRAY_ELEMS; i++) {
		stack_array[i] = i * 1000;
	}

	for (i=0; i<2; i++) {
	  call_all();
	  write_data(array1, array1_start);
	  call_all();
    printf("Checking initialized array1\n");
	  read_data(array1, array1_start, "array1");
	}

	/* check the uninitialized array2 again before initialization */
  printf("Checking initialized array2 again\n");
	for (i=0; i<ELEMS; i++) {
		if (array2[i] != 0) {
			printf("FAILED in file %s at line %d: array2[%d] = %u != %d\n", __FILE__, __LINE__, i, array2[i], 0);
			exit(1);
		}
	}

  printf("Checking initialized stack_array\n");
	for (i=0; i<STACK_ARRAY_ELEMS; i++) {
		if (stack_array[i] != i * 1000) {
			printf("FAILED in file %s at line %d: stack_array[%d] = %u != %d\n", __FILE__, __LINE__, i, stack_array[i], i);
			exit(1);
		}
	}

  printf("Checking initialized init\n");
	/* check the initialized array */
	for (i=0; i<INIT_ARRAY_ELEMS; i++) {
		if (init[i] != i) {
			printf("FAILED in file %s at line %d: init[%d] = %u != %d\n", __FILE__, __LINE__, i, init[i], i);
			exit(1);
		}
	}

	for (i=0; i<2; i++) {
	  call_all();
	  write_data(array2, array2_start);
	  call_all();
    printf("Checking initialized array2\n");
	  read_data(array2, array2_start, "array2");
	}

  printf("Checking initialized stack_array\n");
	for (i=0; i<STACK_ARRAY_ELEMS; i++) {
		if (stack_array[i] != i * 1000) {
			printf("FAILED in file %s at line %d: stack_array[%d] = %u != %d\n", __FILE__, __LINE__, i, stack_array[i], i);
			exit(1);
		}
	}

	/* check the initialized array */
  printf("Checking initialized init\n");
	for (i=0; i<INIT_ARRAY_ELEMS; i++) {
		if (init[i] != i) {
			printf("FAILED in file %s at line %d: init[%d] = %u != %d\n", __FILE__, __LINE__, i, init[i], i);
			exit(1);
		}
	}


  printf("Checking initialized array1 for the last time\n");
	read_data(array1, array1_start, "array1");
  printf("Checking initialized array2 for the last time\n");
	read_data(array2, array2_start, "array2");


	printf("SUCCEEDED\n");
}

int
main()
{

#ifdef DEBUG
  printf("PAGE_SIZE = %d\n", PAGE_SIZE);
  printf("DATA_BYTES = %d\n", DATA_BYTES);
  printf("ELEMS = %d\n", ELEMS);
  printf("ELEMS_PER_PAGE = %d\n", ELEMS_PER_PAGE);
  printf("PAGES = %d\n", PAGES);
  printf("Array elements = %d\n", ELEMS);
  printf("Pages per array = %d\n", ((ELEMS * sizeof(unsigned int)) / PAGE_SIZE));
#endif

  do_work(1);
#ifdef DEBUG
	printf("array 1\n");
	print_data(array1);
	printf("array 2\n");
	print_data(array2);
#endif
  exit(0);
}

