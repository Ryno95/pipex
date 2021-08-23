#include "bonus_utils.h"
#include "../headers/defines.h"
#include "../headers/get_exe_path.h"
#include "../headers/pipex_utils.h"
#include "../headers/handle_errors.h"
#include "../headers/pipex.h"
#include <stdio.h> 

void	child(const char *argv[], const char *env[], int process)
{
	const char	*path_var = ft_get_env_var(env, PATH_ID);
	const char	**cmd = (const char **)ft_split(argv[process + 2], SPACE);
	char		*path;

	if (!cmd)
		handle_errors(SAFETY, "child, invalid command");
	path = get_executable_path(path_var, cmd[0]);
	if (!path)
		handle_errors(MALLOC_ERROR, "child_process path allocation");
	if (execute_command(path, cmd, env) == ERROR)
		handle_errors(EXECUTION_ERROR, "child_process execute command");
}

int	create_new_process(t_multi_pipes *pipes)
{
	int	pid;

	if (pipe(pipes->current) == ERROR)
		handle_errors(PIPE_ERROR, "pipe current main");
	pid = fork();
	if (pid == ERROR)
		handle_errors(ERROR, "forking main");
	return (pid);
}

void	wait_for_all_processes(int *pid, int num_of_processes)
{
	int	i;

	i = 0;
	while (i < num_of_processes)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

int	*run_processes(const char *argv[], const char *env[],
	int num_of_processes, t_in_and_outfile *files)
{
	t_multi_pipes			pipes;
	int						*pid;
	int						i;

	pid = (int *)ft_calloc((num_of_processes + 1), sizeof(int));
	if (!pid)
		handle_errors(MALLOC_ERROR, "main pid malloc");
	i = 0;
	while (i < num_of_processes)
	{
		pid[i] = create_new_process(&pipes);
		if (pid[i] == CHILD_PROCESS_ID)
		{
			redirect_in_and_output(&pipes, files, i, num_of_processes);
			child(argv, env, i);
		}
		if (i != FIRST_PROCESS)
			close(pipes.previous[READ_FD]);
		close(pipes.current[WRITE_FD]);
		current_to_previous_pipe(&pipes);
		i++;
	}
	return (pid);
}

int	main(int argc, const char *argv[], const char *env[])
{
	const int				num_of_processes = argc - 3;
	int						*pid;
	t_in_and_outfile		files;

	get_files(&files, argv, argc);
	pid = run_processes(argv, env, num_of_processes, &files);
	close_multiple(files.infile, files.outfile);
	wait_for_all_processes(pid, num_of_processes);
	free(pid);
	return (0);
}
