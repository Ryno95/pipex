#include "../headers/handle_errors.h"

void	handle_errors(int error_code, char *location)
{
	perror(location);
	exit(error_code);
}
