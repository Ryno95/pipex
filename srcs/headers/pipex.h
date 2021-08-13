#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "defines.h"
# include "pipex_utils.h"
# include "get_exe_path.h"

void	run(int argc, const char *argv[], const char *env[]);
t_bool	is_valid_arguments(int argc, const char *argv[]);
void	handle_errors(int error_code, char *location);
int		redirect_stdin_and_stdout(int new_stdin, int new_stdout);
int		execute_command(const char *path, const char *argv[], const char *env[]);

#endif
