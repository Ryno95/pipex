#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "utils/libft/libft.h"

#define PIPE_BOTH_ENDS 2
#define READ_FD 0
#define WRITE_FD 1
#define CHILD_PROCESS_ID 0
#define ERROR -1
#define PERMISSIONS 0644
#define SPACE ' '

typedef enum e_stdin_out
{
	STDIN_FD = 0,
	STDOUT_FD = 1
}	t_stdin_out;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_errors
{
	FD_ERROR = 10,
	MALLOC_ERROR = 11
}	t_errors;

void	run(int argc, const char *argv[], const char *env[]);
t_bool  is_valid_arguments(int argc, const char *argv[]);