#ifndef BONUS_UTILS_H
# define BONUS_UTILS_H
# define FIRST_PROCESS 0
# define NO_FILE -5
# define DEFAULT_WAIT_ID -1

# include "../headers/defines.h"

typedef struct s_multi_pipes
{
	int	current[PIPE_BOTH_ENDS];
	int	previous[PIPE_BOTH_ENDS];
}	t_multi_pipes;

typedef struct s_in_and_outfile
{
	int	infile;
	int	outfile;
}	t_in_and_outfile;

void	set_stdout(int new_std_out, int file_to_close);
void	set_stdin(int new_std_in, int file_to_close);
void	get_files(t_in_and_outfile *files, const char *argv[], int argc);
void	current_to_previous_pipe(t_multi_pipes *pipes);
void	redirect_in_and_output(t_multi_pipes *pipes, t_in_and_outfile *files,
			int process, int num_of_processes);

#endif