#include "../pipex.h"

int	execute_command(const char *path, const char *argv[], const char *env[])
{
	return (execve(path, (char *const *)argv, (char *const *)env));
}

t_bool	is_valid_arguments(int argc, const char *argv[])
{
	(void)argv;
	(void)argc;
	return (TRUE);
}

int	child_process(int *fd, const char *argv[], const char *env[])
{
	const int	infile = open(argv[1], O_RDONLY);
	const char	*path_var = ft_get_env_var(env, PATH_ID);
	const char	**cmd = (const char **)ft_split(argv[2], SPACE);
	char		*path;

	if (infile == ERROR)
		handle_errors(FD_ERROR, "child_process");
	close(fd[READ_FD]);
	dup2(infile, STDIN_FD);
	dup2(fd[WRITE_FD], STDOUT_FD);
	if (!cmd)
		handle_errors(MALLOC_ERROR, "child_process");
	path = get_executable_path(path_var, cmd[0]);
	if (!path)
		handle_errors(MALLOC_ERROR, "child_process");
	if (execute_command(path, cmd, env) == ERROR)
		handle_errors(EXECUTION_ERROR, "child_process");
	return (0);
}

int	parent_process(int *fd, const char *argv[], const char *env[])
{
	const int	outfile = open(argv[4], O_WRONLY | O_CREAT, PERMISSIONS);
	const char	**cmd = (const char **)ft_split(argv[3], SPACE);
	const char	*path_var = ft_get_env_var(env, PATH_ID);
	char		*path;

	close(fd[WRITE_FD]);
	dup2(fd[READ_FD], STDIN_FD);
	dup2(outfile, STDOUT_FILENO);
	path = get_executable_path(path_var, cmd[0]);
	if (execute_command(path, cmd, env) == ERROR)
		handle_errors(EXECUTION_ERROR, "parent_process");
	return (0);
}

void	run(int argc, const char *argv[], const char *env[])
{
	int	pid;
	int	fd[PIPE_BOTH_ENDS];

	if (!is_valid_arguments(argc, argv) || pipe(fd) == ERROR)
		handle_errors(1, "run");
	pid = fork();
	if (pid == ERROR)
		perror("pidfuckup");
	else if (pid == CHILD_PROCESS_ID)
		child_process(fd, argv, env);
	else
	{
		// pid = fork();
		// // if (pid == CHILD_PROCESS_ID)
		// // 	child_process
		wait(NULL);
		parent_process(fd, argv, env);
	}
	close(fd[READ_FD]);
	close(fd[WRITE_FD]);
	(void)env;
	return ;
}
