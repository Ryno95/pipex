#include "headers/handle_errors.h"
#include "headers/defines.h"

void	handle_errors(int error_code, char *location)
{
	if (error_code == SAFETY)
		write(2, location, ft_strlen(location));
	else
		perror(location);
	exit(error_code);
}
