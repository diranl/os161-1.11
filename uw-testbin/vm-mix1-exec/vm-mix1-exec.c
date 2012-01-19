#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *argv[2] = { (char *)"vm-mix1", NULL };

int
main()
{
   execv("vm-mix1/vm-mix1", argv);
   exit(0);
}

