#ifndef GET_EXE_PATH_H
# define GET_EXE_PATH_H

# include "defines.h"
# include <unistd.h>

char	*get_executable_path(const char *env[], const char *command);

#endif