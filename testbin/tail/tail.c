/*
 * tail.c
 *
 * 	Outputs a file beginning at a specific location.
 *	Usage: tail <file> <location>
 *
 * This may be useful for testing during the file system assignment.
 */

#include <unistd.h>
#include <stdlib.h>
#include <err.h>

#define BUFSIZE 1000

/* Put buffer in data space.  We know that the program should allocate as */
/* much data space as required, but stack space is tight. */

char buffer[BUFSIZE];

/* default filename to use if one is not supplied */
char default_filename[] = "tailinput";

/* default location to use if one is not supplied */
#define DEFAULT_LOCATION 0

static
void
tail(int file, off_t where, const char *filename)
{
	int len;

	if (lseek(file, where, SEEK_SET)<0) {
		err(1, "%s", filename);
	}
	
	while ((len = read(file, buffer, sizeof(buffer))) > 0) {
		write(STDOUT_FILENO, buffer, len);
	}
}

int
main(int argc, char **argv)
{
	int file;
	char *fname;
	off_t loc;

	/* set defaults */
	fname = default_filename;
	loc = (off_t)(DEFAULT_LOCATION);

	if (argc == 3) {
	  /* override defaults from command line */
	  fname = argv[1];
	  loc = (off_t)atoi(argv[2]);
	}
	else if (argc != 1) {
	  errx(1, "Usage: tail [<file> <location>]");
	}

	file = open(fname, O_RDONLY);
	if (file < 0) {
		err(1, "%s", fname);
	}
	tail(file, loc, fname);
	close(file);
	return 0;
}

