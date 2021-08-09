#ifndef GET_EXE_PATH_H
# define GET_EXE_PATH_H

# include "defines.h"
# include <unistd.h>

char	*ft_get_env_var(const char *env[], const char *env_variable);
char	*get_executable_path(const char *env_var, const char *cmd);

#endif