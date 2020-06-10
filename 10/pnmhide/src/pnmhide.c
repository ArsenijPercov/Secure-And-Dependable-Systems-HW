/*
 * pnmhide/src/pnmhide.c --
 */

#define _POSIX_C_SOURCE 2

#include <unistd.h>
#include <string.h>

#include "image.h"
#include "hide.h"

static const char *progname = "pnmhide";

int main(int argc, char *argv[])
{
    image_t im;
    char opt;
    char *msg = NULL;
    int eflag = 0, dflag = 0;
    char buffer[4096];
    int len;

    while ((opt = getopt(argc, argv, "e:d")) != -1) {
        switch (opt) {
        case 'e':
            eflag = 1;
            msg = optarg;
            break;
        case 'd':
            dflag = 1;
            break;
        default:
            fprintf(stderr, "Usage: %s [-e msg] [-d] pnmfile\n", progname);
            exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "%s: Expected file name after options\n", progname);
        exit(EXIT_FAILURE);
    }
    
    pm_init(progname, 0);

    if (im_read(&im, argv[optind]) != 0) {
        return EXIT_FAILURE;
    }

    if (eflag && msg) {
        len = im_encode(&im, msg);
	if (len < 0) {
	    fprintf(stderr, "%s: Encoding failure\n", progname);
	    im_free(&im);
	    return EXIT_FAILURE;
	}
	if (len != strlen(msg)) {
	    fprintf(stderr, "%s: Encoding truncated (%d bytes of %zu bytes)\n",
		    progname, len, strlen(msg));
	}
        if (im_write(&im, NULL) != 0) {
            im_free(&im);
            return EXIT_FAILURE;
        }
    }

    if (dflag) {
        len = im_decode(&im, buffer, sizeof(buffer));
	if (len < 0) {
	    fprintf(stderr, "%s: Decoding failure\n", progname);
	    im_free(&im);
	    return EXIT_FAILURE;
	}
        printf("res: %.*s\n", len, buffer);
    }
    
    im_free(&im);
    return EXIT_SUCCESS;
}
