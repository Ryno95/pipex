#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define PIPE_STANDARD_ARRAY_SIZE 2
#define READ_FD 0
#define WRITE_FD 1
#define CHILD_PROCESS_ID 0
#define SYSTEM_ERR -1

static void close_multiple(int fd_one, int fd_two)
{
	close(fd_one);
	close(fd_two);
}

int main(int argc, char *argv[])
{	
	int fd[PIPE_STANDARD_ARRAY_SIZE];
	int pid;

	if (pipe(fd) == SYSTEM_ERR)
		return (1);
	pid = fork();
	if (pid == SYSTEM_ERR)
		return (2);
	else if (pid == CHILD_PROCESS_ID)
	{
		int n;
		int array[10];
		srand(time(NULL));
		n = rand() % 10 + 1;
		for (int i = 0; i < n; i++)
			array[i] = rand() % 11;
		write(fd[WRITE_FD], &n, sizeof(int));
		if (write(fd[WRITE_FD], array, sizeof(int) * n) < 0)
			return (3);
		close_multiple(fd[READ_FD], fd[WRITE_FD]);
	}
	else
	{
		wait(NULL);
		int array_buf[10];
		int size, sum = 0;
		read(fd[READ_FD], &size, sizeof(int));
		read(fd[READ_FD], array_buf, sizeof(int) * size);
		for (int i = 0; i < size; i++)
			sum += array_buf[i];
		close_multiple(fd[READ_FD], fd[WRITE_FD]);
		printf("SUM: %d\n", sum);
	}
	return (0);
}