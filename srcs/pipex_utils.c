#include "headers/defines.h"

int	redirect_stdin_and_stdout(int new_stdin, int new_stdout)
{
	if (dup2(new_stdin, STDIN_FD) == ERROR)
		return (0);
	if (dup2(new_stdout, STDOUT_FD) == ERROR)
		return (0);
	return (1);
}

void	wait_multiple(int *pid, int length)
{
	int i;

	i = 0;
	while (i < length)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

void	close_multiple(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
