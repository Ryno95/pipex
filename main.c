#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(void)
{
	printf("CREATING FILE HERE\n");
	int file = open("results.txt", O_WRONLY | O_CREAT | 0777);
	printf("FILE SHOULD BE CREATED\nFD: %d\n", file);
	return (0);
}