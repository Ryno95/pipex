#include <stdlib.h>
#include <stdio.h>

void	handle_errors(int error_code, char *location)
{
	perror(location);
	exit(error_code);
}
