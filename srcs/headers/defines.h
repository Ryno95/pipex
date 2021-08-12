#ifndef DEFINES_H
# define DEFINES_H

# include "../utils/libft/libft.h"

# define CHILD_PROCESS_ID 0
# define ERROR -1
# define PERMISSIONS 0644
# define SPACE ' '
# define COLON ':'
# define FORWARD_SLASH "/\0"
# define PATH_ID "PATH="

typedef enum e_pipe_fds
{
	READ_FD = 0,
	WRITE_FD = 1,
	PIPE_BOTH_ENDS = 2
}	t_pipe_fds;

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
	MALLOC_ERROR = 11,
	EXECUTION_ERROR = 12,
	SAFETY = 13,
	PIPE_ERROR = 14
}	t_errors;

#endif


typedef struct t_redirection
{
	int in;
	int out;
	int err;
};

typedef struct t_command
{
	int type;
	// char *arguments;
	char *path = "/bin/ls"
	char **argv = {"cat", "-e", "file.txt", ,NULL};
	t_redirection *redirect;
};

