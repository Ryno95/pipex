#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define PIPE_BOTH_ENDS 2
#define READ_FD 0
#define WRITE_FD 1
#define CHILD_PROCESS_ID 0
#define ERROR -1
#define PERMISSIONS 0644

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

void	run(int argc, char *argv[], char *env[]);
t_bool  is_valid_arguments(int argc, char *argv[]);