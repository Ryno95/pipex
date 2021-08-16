#include "../headers/defines.h"
#include "../headers/get_exe_path.h"
#include "../headers/pipex_utils.h"
#include "../headers/handle_errors.h"
#include "../headers/pipex.h"
#include <stdio.h> 
#include "bonus_utils.h"

void	set_stdout(int new_std_out, int file_to_close)
{
	if (dup2(new_std_out, STDOUT_FD) == ERROR)
		handle_errors(FD_ERROR, "redirect, setting child output");
	if (file_to_close != NO_FILE)
		close(file_to_close);
}

void	set_stdin(int new_std_in, int file_to_close)
{
	if (dup2(new_std_in, STDIN_FD) == ERROR)
		handle_errors(FD_ERROR, "redirect, setting child input");
	if (file_to_close != NO_FILE)
		close(file_to_close);
}

void	redirect_in_and_output(t_multi_pipes *pipes, t_in_and_outfile *files,
	int process, int num_of_processes)
{
	if (process == FIRST_PROCESS)
		set_stdin(files->infile, files->infile);
	else
		set_stdin(pipes->previous[READ_FD], NO_FILE);
	if (process == num_of_processes - 1)
		set_stdout(files->outfile, files->outfile);
	else
		set_stdout(pipes->current[WRITE_FD], pipes->current[READ_FD]);
}

void	get_files(t_in_and_outfile *files, const char *argv[], int argc)
{
	const char	*infile = (char *)argv[1];
	char		*outfile;

	if (ft_strncmp(infile, HERE_DOC, ft_strlen(infile)) == 0)
		files->infile = -3;
	else
	{
		files->infile = open(infile, O_RDONLY);
		if (files->infile == ERROR)
			handle_errors(FD_ERROR, "get_infile");
	}
	outfile = (char *)argv[argc - 1];
	files->outfile = open(outfile, O_WRONLY | O_CREAT, PERMISSIONS);
	if (files->outfile == ERROR)
		handle_errors(FD_ERROR, "get_outfile");
}

void	current_to_previous_pipe(t_multi_pipes *pipes)
{
	pipes->previous[READ_FD] = pipes->current[READ_FD];
	pipes->previous[WRITE_FD] = pipes->current[WRITE_FD];
}
