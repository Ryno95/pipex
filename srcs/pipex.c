#include "headers/pipex.h"

int	execute_command(const char *path, const char *argv[], const char *env[])
{
	return (execve(path, (char *const *)argv, (char *const *)env));
}

t_bool	is_valid_arguments(int argc, const char *argv[])
{
	(void)argv;
	return (argc == 5);
}

int	child_process(int *fd, const char *argv[], const char *env[])
{
	const int	infile = open(argv[1], O_RDONLY);
	const char	*path_var = ft_get_env_var(env, PATH_ID);
	const char	**cmd = (const char **)ft_split(argv[2], SPACE);
	char		*path;

	if (infile == ERROR || !cmd)
		handle_errors(SAFETY, "child_process 22");
	if (!redirect_stdin_and_stdout(infile, fd[WRITE_FD]))
		handle_errors(FD_ERROR, "child_process 24");
	close_multiple(fd[READ_FD], infile);
	path = get_executable_path(path_var, cmd[0]);
	if (!path)
		handle_errors(MALLOC_ERROR, "child_process 28");
	if (execute_command(path, cmd, env) == ERROR)
		handle_errors(EXECUTION_ERROR, "child_process 30");
	return (1);
}

int	parent_process(int *fd, const char *argv[], const char *env[])
{
	const int	outfile = open(argv[4], O_WRONLY | O_CREAT, PERMISSIONS);
	const char	**cmd = (const char **)ft_split(argv[3], SPACE);
	const char	*path_var = ft_get_env_var(env, PATH_ID);
	char		*path;

	if (!cmd || outfile == ERROR)
		handle_errors(SAFETY, "parent_process 42");
	if (!redirect_stdin_and_stdout(fd[READ_FD], outfile))
		handle_errors(SAFETY, "parent_process 44");
	close_multiple(fd[WRITE_FD], outfile);
	path = get_executable_path(path_var, cmd[0]);
	if (!path)
		handle_errors(MALLOC_ERROR, "parent_process 48");
	if (execute_command(path, cmd, env) == ERROR)
		handle_errors(EXECUTION_ERROR, "parent_process 50");
	return (1);
}

void	run(int argc, const char *argv[], const char *env[])
{
	int	pid[2];
	int	fd[PIPE_BOTH_ENDS];

	if (!is_valid_arguments(argc, argv) || pipe(fd) == ERROR)
		handle_errors(1, "USAGE: ./pipex file1 cmd1 cmd2 file2");
	pid[0] = fork();
	if (pid[0] == ERROR)
		handle_errors(ERROR, "main");
	else if (pid[0] == CHILD_PROCESS_ID)
		child_process(fd, argv, env);
	pid[1] = fork();
	if (pid[1] == CHILD_PROCESS_ID)
		parent_process(fd, argv, env);
	close_multiple(fd[READ_FD], fd[WRITE_FD]);
	wait_multiple(&pid[0], (sizeof(pid) / sizeof(int)));
	return ;
}
