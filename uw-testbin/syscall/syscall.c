/* See how function and system calls happens. */
#include <unistd.h>
#include <errno.h>

int
main()
{
	int x;
 	x = close(999);
  if (x < 0) {
	  return errno;
  } else {
	  return x;
  }
}
