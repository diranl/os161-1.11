/*
 * Demonstrate different segments.
 */
#include <unistd.h>

#define N   (200)

int x = 0xdeadbeef;
int t1;
int t2;
int t3;
int array[4096];
char const *str = "Hello World\n";
const int z = 0xabcddcba;

struct example {
  int ypos;
	int xpos;
};

int
main()
{
	int count = 0;
	const int value = 1;
	t1 = N;
	t2 = 2;
	count = x + t1;
	t2 = z + t2 + value;

	reboot(RB_POWEROFF);
	return 0; /* avoid compiler warnings */
}
