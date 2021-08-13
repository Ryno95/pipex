#include "../headers/defines.h"
#include "../headers/get_exe_path.h"
#include "../headers/pipex_utils.h"
#include "../headers/handle_errors.h"
#include "../headers/pipex.h"
#include <stdio.h> 

#define MAX_PROCESSES 1084
#define FIRST_PROCESS 0
#define HERE_DOC "here_doc"

typedef struct s_multi_pipes
{
	int	current[PIPE_BOTH_ENDS];
	int	previous[PIPE_BOTH_ENDS];
}	t_multi_pipes;

typedef struct s_in_and_outfile
{
	int infile;
	int outfile;
}	t_in_and_outfile;

int	set_stdout(int new_std_out)
{
	return (dup2(new_std_out, STDOUT_FD));
}

int	set_stdin(int new_std_in)
{
	return (dup2(new_std_in, STDIN_FD));
}

void redirect_in_and_output(t_multi_pipes *pipes, t_in_and_outfile *files, int process, int num_of_processes)
{
	if (process == FIRST_PROCESS)
	{
		if (set_stdin(files->infile) == ERROR)
			handle_errors(FD_ERROR, "redirect, setting child input");
		close(files->infile);
	}
	else
	{
		if(set_stdin(pipes->previous[READ_FD]) == ERROR)
			handle_errors(FD_ERROR, "redirect, setting child input");
	}

	if (process == num_of_processes - 1)
	{
		if (!set_stdout(files->outfile))
			handle_errors(FD_ERROR,"redirect, setting output to file");
		close(files->outfile);
	}
	else
	{
		if (!set_stdout(pipes->current[WRITE_FD]))
			handle_errors(FD_ERROR, "redirect, setting child output");
	}
}

void	get_files(t_in_and_outfile *files, const char *argv[], int argc)
{
	const char	*infile = (char *)argv[1];
	char		*outfile;

	if (ft_strncmp(infile, HERE_DOC, ft_strlen(infile)) == 0)
		files->infile = -1;
	else
	{
		files->infile = open(infile, O_RDONLY);
		if (files->infile == ERROR)
			handle_errors(FD_ERROR, "get_infile");
	} 
	outfile = (char *)argv[argc - 1];
	files->outfile = open(outfile, O_WRONLY | O_CREAT, PERMISSIONS);
	if (files->outfile == -1)
		handle_errors(FD_ERROR, "get_outfile");
}

void	current_to_previous_pipe(t_multi_pipes *pipes)
{
	pipes->previous[READ_FD] = pipes->current[READ_FD];
	pipes->previous[WRITE_FD] = pipes->current[WRITE_FD];
}

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
	printf("performing command: %s\n", path);
	if (execute_command(path, cmd, env) == ERROR)
		handle_errors(EXECUTION_ERROR, "child_process execute command");
}
int main(int argc, const char *argv[], const char *env[])
{
	t_multi_pipes			pipes;
	const int				num_of_processes = argc - 3;
	int						*pid;
	t_in_and_outfile		files;
	
	(void)env;
	get_files(&files, argv, argc);
	pid = (int *)malloc((num_of_processes + 1) * sizeof(int));
	if (!pid)
		handle_errors(MALLOC_ERROR, "main pid malloc");
	for(int i = 0; i < num_of_processes; i++)
	{
		if (pipe(pipes.current) == ERROR)
			handle_errors(PIPE_ERROR, "pipe current main");
		pid[i] = fork();
		if (pid[i] == ERROR)
			handle_errors(ERROR, "forking main");
		else if (pid[i] == CHILD_PROCESS_ID)
		{
			redirect_in_and_output(&pipes, &files, i, num_of_processes);
			close(pipes.current[READ_FD]);
			if (i > FIRST_PROCESS)
				close(pipes.previous[WRITE_FD]);
			close(pipes.current[READ_FD]);
			child(argv, env, i);
		}
		// close fuuuuckiing fds fucker!
		if (i != FIRST_PROCESS)
			close(pipes.previous[READ_FD]);
		close(pipes.current[WRITE_FD]);
		current_to_previous_pipe(&pipes);
	}
	close_multiple(pipes.current[READ_FD], pipes.current[WRITE_FD]);
	close_multiple(pipes.previous[READ_FD], pipes.previous[WRITE_FD]);
	close_multiple(files.infile, files.outfile);
	printf("Finished all child processes\n");
	for (int j = 0; j < num_of_processes; j++)
		waitpid(pid[j], NULL, 0);
	return (0);
}