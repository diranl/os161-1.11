/*
 * Create a large file in small increments.
 *
 * Should work on emufs (emu0:) once the basic system calls are done,
 * and should work on SFS when the file system assignment is
 * done. Sufficiently small files should work on SFS even before that
 * assignment.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <err.h>

/* default filename to use if one is not supplied */
char default_filename[] = "bigfile.out";

/* default output file size */
#define DEFAULT_FILESIZE 10000

static char buffer[100];

int
main(int argc, char *argv[])
{
	const char *filename;
	int i, size;
	int fileid;
	int len;

	/* set defaults */
	filename = default_filename;
	size = DEFAULT_FILESIZE;

	if (argc == 3) {
	  /* override defaults from command line */
	  filename = argv[1];
	  size = atoi(argv[2]);
	}
	else if (argc != 1) {
	  errx(1, "Usage: bigfile [<filename> <size>]");
	}

	printf("Creating a file of size %d\n", size);

	fileid = open(filename, O_WRONLY|O_CREAT|O_TRUNC);
	if (fileid < 0) {
		err(1, "%s: create", filename);
	}

	i=0;
	while (i<size) {
		snprintf(buffer, sizeof(buffer), "%-10d", i);
		len = write(fileid, buffer, strlen(buffer));
		if (len<0) {
			err(1, "%s: write", filename);
		}
	        i += len;
	}	

	close(fileid);

	return 0;
}
