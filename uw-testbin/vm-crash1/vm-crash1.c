#include <stdio.h>
#include <stdlib.h>

#if defined(__mips__)
#define INSN_TYPE u_int32_t
#define INVAL_INSN  0x0000003f
#else
#error "Please fix this"
#endif


int
main()
{

	INSN_TYPE *x = (INSN_TYPE *) main;
	*x = INVAL_INSN;

	printf("IF THIS PRINTS THE TEST FAILED\n");
	exit(1);
}



