#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__mips__)
#define INSN_TYPE u_int32_t
#define INVAL_INSN  0x0000003f
#else
#error "Please fix this"
#endif


void
write_to_code()
{
  extern int func_150();
  /* picking a code page that should no longer be in the TLB */
	INSN_TYPE *x = (INSN_TYPE *) func_150;
	*x = INVAL_INSN;

	printf("IF THIS PRINTS THE TEST FAILED\n");
}

extern void	call_all();

#define PAGE_SIZE (4096)
#define PAGES     (128)
#define SIZE      (PAGE_SIZE * PAGES / sizeof(int))
#define NUM_REFS  (2)

unsigned int array[SIZE];

void
write_data()
{
	unsigned int refs = 0;
	unsigned int i = 0;

	for (refs = 0; refs < NUM_REFS-1; refs++) {
		for (i=0; i<SIZE; i+= PAGE_SIZE) {
			array[i] = i;
		}
	}
}

void
read_data()
{
	unsigned int i = 0;

	for (i=0; i<SIZE; i+= PAGE_SIZE) {
		if (array[i] != i) {
			printf("FAILED array[%d] = %u != %d\n", i, array[i], i);
			exit(1);
		}
	}
}


int
main()
{
	unsigned int i = 0;

	for (i=0; i<5; i++) {
	  call_all();
	  write_data();
	  call_all();
	  read_data();
	}

	/* This won't hopefully return becasue it crashes */
	write_to_code();
	exit(0);
}
