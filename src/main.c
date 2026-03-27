#include <stdio.h>
#include <stdlib.h>

#include "fakelib/lib.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	(void)fake_lib();

	fprintf(stdout, "Hello World!\n");
	return EXIT_SUCCESS;
}
