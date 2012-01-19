/*
 * hash: Takes a file and computes a "hash" value by adding together all
 * the values in the file mod some largish prime.
 *
 * Once the basic system calls are complete, this should work on any
 * file the system supports. However, it's probably of most use for
 * testing your file system code.
 *
 * This should really be replaced with a real hash, like MD5 or SHA-1.
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>

#ifdef HOST
#include "hostcompat.h"
#endif

#define HASHP 104729

/* default file name to use if one is not supplied */
char default_filename[] = "hashinput";

int
main(int argc, char *argv[])
{
	int fd;
	char readbuf[1];
	int j = 0;
	char *fname;

#ifdef HOST
	hostcompat_init(argc, argv);
#endif

	/* set default */
	fname = default_filename;

        if (argc == 2) {
	  /* override default from command line */
	  fname = argv[1];
	}
	else if (argc != 1) {
	  errx(1, "Usage: hash [filename]");
	}
	
	fd = open(fname, O_RDONLY, 0664);
	
	if (fd<0) { 
		err(1, "%s", fname);
	}

	for (;;) {
		if (read(fd, readbuf, 1) <= 0) break;
		j = ((j*8) + (int) readbuf[0]) % HASHP;
	}

	close(fd);
	
	printf("Hash : %d\n", j);

	return 0;
}
