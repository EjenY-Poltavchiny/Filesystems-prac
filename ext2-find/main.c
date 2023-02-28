#include "solution.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <string.h>



int main(int argc, char** argv)
{
	char* filepath = (char *)malloc(sizeof(char) * 3);
	filepath[0] = '.';
	filepath[1] = '/';
	filepath[2] = '\0';
        int img = open(argv[1], O_RDONLY);
        if (img < 0)
                errx(1, "open(img) failed");

        int inode_nr = atoi(argv[2]);

        int t = dump_dir(img, inode_nr, filepath);
        if (t < 0)
        {
                errx(1, "dump_dir() failed");
        }
        close(img);
	free(filepath);
        return 0;
}

