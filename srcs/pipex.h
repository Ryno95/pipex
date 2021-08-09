#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "srcs/utils/libft/libft.h"
# include "defines.h"

void	run(int argc, const char *argv[], const char *env[]);
t_bool	is_valid_arguments(int argc, const char *argv[]);
void	handle_errors(int error_code, char *location);
int		redirect_stdin_and_stdout(int new_stdin, int new_stdout);

#endif
