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
#define ALL_PERMISSIONS 0777

// ls -la | grep total

// int	child_process(const char *argv[])
// {
// 	int	fd;
// 	int	fd2;

// 	fd = open("results.txt", O_WRONLY | O_CREAT, ALL_PERMISSIONS);
// 	if (fd == -1)
// 		exit(3);
		
// 	fd2 = dup2(fd, STDOUT_FILENO);
// 	if (fd2 != STDOUT_FILENO)
// 		return (4);

// 	if (execute_command(argv[0], argv) == -1)
// 		return (-1);
// 	close(fd);
// 	close(fd2);
// 	return (1);
// }

// int	parent_process()
// {
// 	int	wstatus;
// 	wait(&wstatus);
// 	int status_code = WEXITSTATUS(wstatus);
// 	if (status_code == 0)
// 		printf("SUCCESS!");
// 	else
// 		printf("Failure code with status code: %d\n", WEXITSTATUS(wstatus));
// 	return (1);
// }

int	main()
{
	int	fd[PIPE_BOTH_ENDS];
	int	pid1;
	int	pid2;


	if (pipe(fd) == ERROR)
		return (1);
	pid1 = fork();
	if (pid1 == ERROR)
		return (2);
	else if (pid1 == CHILD_PROCESS_ID)
	{
		// child process 1, execute first command ("ls -la" or "ping -c 5")
		char *argv[] = {"/sbin/ping", "-c", "5", "google.com", NULL};
		// char *lsargv[] = {"/bin/ls", "-la", NULL};
		dup2(fd[WRITE_FD], STDOUT_FILENO);
		close(fd[READ_FD]);
		close(fd[WRITE_FD]);
		if (execve(argv[0], argv, NULL) == ERROR)
			printf("SHiiiiit\n");
	}

	pid2 = fork();
	if (pid2 == ERROR)
		return (3);
	else if (pid2 == CHILD_PROCESS_ID)
	{
		// child process 2, execute second command ("grep round"in this case)
		// char *argv[] = {"/bin/grep", "-e", NULL};
		char *lsargv[] = {"/bin/ls", "-la", NULL};
		dup2(fd[READ_FD], STDIN_FILENO);
		close(fd[READ_FD]);
		close(fd[WRITE_FD]);
		char *env[] = {"PWD=", NULL};
		if (execve(lsargv[0], lsargv, env) == ERROR)
		// if (execlp("grep", "grep", "round", NULL) == ERROR)
		{
			printf("Well that's not right.....\n");
			return (7);
		}
	}
	close(fd[READ_FD]);
	close(fd[WRITE_FD]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
