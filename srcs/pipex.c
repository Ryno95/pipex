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

	if (!infile)
		handle_errors(FD_ERROR);
	close(fd[READ_FD]);
	dup2(infile, STDIN_FD);
	dup2(fd[WRITE_FD], STDOUT_FD);
	if (!cmd)
		handle_errors(MALLOC_ERROR);
	path = get_executable_path(path_var, cmd[0]);
	if (!path)
		handle_errors(MALLOC_ERROR);
	if (execute_command(path, cmd, env) == ERROR)
		printf("Shoiiiiit\n");
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
		printf("FUCKUP\n");
	return (0);
}

void	run(int argc, const char *argv[], const char *env[])
{
	int	pid;
	int	fd[PIPE_BOTH_ENDS];

	if (!is_valid_arguments(argc, argv) || pipe(fd) == ERROR)
		handle_errors(1);
	pid = fork();
	if (pid == ERROR)
		handle_errors(2);
	else if (pid == CHILD_PROCESS_ID)
		child_process(fd, argv, env);
	else
	{
		wait(NULL);
		parent_process(fd, argv, env);
		printf("END of parent proccess\n");
	}
	close(fd[READ_FD]);
	close(fd[WRITE_FD]);
	(void)env;
	return ;
}
