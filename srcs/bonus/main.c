#include "bonus_utils.h"
#include "../headers/defines.h"
#include "../headers/get_exe_path.h"
#include "../headers/pipex_utils.h"
#include "../headers/handle_errors.h"
#include "../headers/pipex.h"
#include <stdio.h> 

static void	child(const char *argv[], const char *env[], int process)
{
	const char	**cmd = (const char **)ft_split(argv[process + 2], SPACE);
	const char	*path = get_executable_path(env, cmd[0]);

	if (!cmd || !path)
		handle_errors(SAFETY, "child, invalid command");
	if (execute_command(path, cmd, env) == ERROR)
		handle_errors(EXECUTION_ERROR, "child_process execute command");
}

static int	create_new_process(t_multi_pipes *pipes)
{
	int	pid;

	if (pipe(pipes->current) == ERROR)
		handle_errors(PIPE_ERROR, "pipe current main");
	pid = fork();
	if (pid == ERROR)
		handle_errors(ERROR, "forking main");
	return (pid);
}

static void	wait_for_all_processes(int num_of_processes)
{
	int	i;

	i = 0;
	while (i < num_of_processes)
	{
		waitpid(DEFAULT_WAIT_ID, NULL, 0);
		i++;
	}
}

static int	run_processes(const char *argv[], const char *env[],
	int num_of_processes, t_in_and_outfile *files)
{
	t_multi_pipes			pipes;
	int						pid;
	int						i;

	i = 0;
	while (i < num_of_processes)
	{
		pid = create_new_process(&pipes);
		if (pid == CHILD_PROCESS_ID)
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
	return (1);
}

int	main(int argc, const char *argv[], const char *env[])
{
	const int				num_of_processes = argc - 3;
	t_in_and_outfile		files;

	if (argc < 4 || num_of_processes < 1)
		handle_errors(SAFETY, "USAGE: ./pipex file1 cmd1 cmd2 cmd... file2");
	get_files(&files, argv, argc);
	run_processes(argv, env, num_of_processes, &files);
	close_multiple(files.infile, files.outfile);
	wait_for_all_processes(num_of_processes);
	return (0);
}
