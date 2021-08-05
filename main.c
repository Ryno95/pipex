#include "pipex.h"

// ls -la | grep total

// int	child_process(const char *argv[])
// {
// 	int	fd;
// 	int	fd2;

// 	fd = open("results.txt", O_WRONLY | O_CREAT, PERMISSIONS);
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

// int	main()
// {
// 	int	fd[PIPE_BOTH_ENDS];
// 	int	pid1;
// 	int	pid2;


// 	if (pipe(fd) == ERROR)
// 		return (1);
// 	pid1 = fork();
// 	if (pid1 == ERROR)
// 		return (2);
// 	else if (pid1 == CHILD_PROCESS_ID)
// 	{
// 		// child process 1, execute first command ("ls -la" or "ping -c 5")
// 		char *argv[] = {"/sbin/ping", "-c", "5", "google.com", NULL};
// 		// char *lsargv[] = {"/bin/ls", "-la", NULL};
// 		dup2(fd[WRITE_FD], STDOUT_FILENO);
// 		close(fd[READ_FD]);
// 		close(fd[WRITE_FD]);
// 		if (execve(argv[0], argv, NULL) == ERROR)
// 			printf("SHiiiiit\n");
// 	}

// 	pid2 = fork();
// 	if (pid2 == ERROR)
// 		return (3);
// 	else if (pid2 == CHILD_PROCESS_ID)
// 	{
// 		// child process 2, execute second command ("grep round"in this case)
// 		// char *argv[] = {"/bin/grep", "-e", NULL};
// 		char *lsargv[] = {"/bin/ls", "-la", NULL};
// 		dup2(fd[READ_FD], STDIN_FILENO);
// 		close(fd[READ_FD]);
// 		close(fd[WRITE_FD]);
// 		char *env[] = {"PWD=", NULL};
// 		if (execve(lsargv[0], lsargv, env) == ERROR)
// 		// if (execlp("grep", "grep", "round", NULL) == ERROR)
// 		{
// 			printf("Well that's not right.....\n");
// 			return (7);
// 		}
// 	}
// 	close(fd[READ_FD]);
// 	close(fd[WRITE_FD]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (0);
// }

int	main(int argc, const char *argv[], const char *env[])
{
	(void)argv;
	(void)argc;
	(void)env;
	// run(argc, argv, env);
	get_executable_path(ft_get_env_var(env, PATH_ID), "ls");
	return (0);
}

// ./pipex infile ``grep a1'' ``wc -w'' outfile
// < infile grep a1 | wc -w > outfile