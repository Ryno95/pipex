#define CTEST_MAIN
#define CTEST_COLOR_OK

#include "ctest.h"
#include <stdio.h>

int main(int argc, const char *argv[])
{
	printf("\n###############\n");
	printf("###############\n");
	printf("\n ## Tester ##\n\n");
	printf("###############\n");
	printf("###############\n\n");
	return ctest_main(argc, argv);
}