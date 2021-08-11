#include "../headers/defines.h"
#include "../headers/get_exe_path.h"
#include "../headers/pipex_utils.h"
#include "../headers/handle_errors.h"
#include "../headers/pipex.h"
#include <stdio.h> 

#define MAX_PROCESSES 1084
#define FIRST_PROCESS 0

// typedef struct s_multi_pipe_fd
// {
// 	int	fd[PIPE_BOTH_ENDS];
// }	t_multi_pipe_fd;


// t_multi_pipe_fd	*create_multiple_pipes(int num_of_pipes)
// {
// 	int					i;
// 	t_multi_pipe_fd		**pipes;

// 	i = 0;
// 	pipes = (t_multi_pipe_fd **)ft_calloc(sizeof(t_multi_pipe_fd *), 1);
// 	while (i < num_of_pipes)
// 	{
// 		pipes[i] = (t_multi_pipe_fd *)malloc(sizeof(t_multi_pipe_fd));
// 		if (!pipes[i])
// 			return (NULL);
// 		if (pipe(pipes[i]->fd) == ERROR)
// 			return (NULL);
// 		i++;
// 		printf("%d\n", i);
// 	}
// 	return (pipes);
// }

// void	close_un_used_fds(int number_of_pipes, t_multi_pipe_fd **pipe_fd, int process)
// {
// 	int j;

// 	j = 0;
// 	while (j < number_of_pipes)
// 	{
// 		if (process != j)
// 			close((pipe_fd[j])->fd[READ_FD]);
// 		if (process + 1 != j)
// 			close(pipe_fd[j]->fd[WRITE_FD]);
// 		j++;
// 	}
// }

// int	fork_processes(int num_of_processes, int **pid, t_multi_pipe_fd **pipe_fd, int number_of_pipes)
// {
// 	int	i;
// 	int	j;
// 	for (i = 0; i < num_of_processes; i++)
// 	{
// 		pid[i] = fork();
// 		if (pid[i] == -1)
// 			printf("ERROR CREATING PROCESS");
// 		if (pid[i] == 0)
// 		{
// 			// child process
// 			close_un_used_fds(number_of_pipes, pipe_fd, i);
// 			// do child thingies
// 			//  here
			
// 			close(pipe_fd[i]->fd[READ_FD]);
// 			close(pipe_fd[i + 1]->fd[WRITE_FD]);
// 			return 0;
// 		}
// 	}
// 	return (0);
// }

// int main(int argc, const char *argv[], const char *env[])
// {
// 	const int				num_of_processes = argc - 3;
// 	const int				num_of_pipes = argc - 4;
// 	t_multi_pipe_fd			**pipe_fd;
// 	int						pid[MAX_PROCESSES];
// 	(void)argv;
// 	(void)env;
// 	pipe_fd = create_multiple_pipes(num_of_pipes);
// 	if (pipe_fd == NULL)
// 		handle_errors(PIPE_ERROR, "Multipipe creator");
// 	if (!fork_processes(num_of_processes, &pid[0], pipe_fd, num_of_pipes))
// 		printf("you fucked uuup\n");
// 	free(pipe_fd);
// 	return (0);
// }

int	set_stdout(int new_std_out)
{
	return (dup2(new_std_out, STDOUT_FD));
}

int	set_stdin(int new_std_in)
{
	return (dup2(new_std_in, STDIN_FD));
}

int	bonus_child_process(int *fd, const char *argv[], const char *env[])
{
	const int	infile = open(argv[1], O_RDONLY);
	const char	*path_var = ft_get_env_var(env, PATH_ID);
	const char	**cmd = (const char **)ft_split(argv[2], SPACE);
	char		*path;

	if (infile == ERROR || !cmd)
		handle_errors(SAFETY, "child_process 29");
	if (!redirect_stdin_and_stdout(infile, fd[WRITE_FD]))
		handle_errors(FD_ERROR, "child_process redirecting fds");
	close_multiple(fd[READ_FD], infile);
	path = get_executable_path(path_var, cmd[0]);
	if (!path)
		handle_errors(MALLOC_ERROR, "child_process path allocation");
	if (execute_command(path, cmd, env) == ERROR)
		handle_errors(EXECUTION_ERROR, "child_process execute command");
	return (1);
}

int main(int argc, char *argv[], char *env[])
{
	int 					currrent_pipe[PIPE_BOTH_ENDS];
	int 					previous_pipe[PIPE_BOTH_ENDS];
	const int				num_of_processes = argc - 3;
	int						*pid;
	int						user_fd[2];
	
	pid = (int *)malloc((num_of_processes + 1) * sizeof(int));
	if (!pid)
		handle_errors(MALLOC_ERROR, "main pid malloc");
	for(int i = 0; i < num_of_processes; i++)
	{
		if (!pipe(currrent_pipe) == ERROR)
			handle_errors(PIPE_ERROR, "pipe curretn main");
		pid[i] = fork();
		if (!pid[i])
			handle_errors(ERROR, "forking main");
		else if (pid[i] == CHILD_PROCESS_ID)
		{
			if (i == num_of_processes)
			{
				// set out to outfile
			}
			else
			{
				if (!set_stdout(currrent_pipe[WRITE_FD]))
					handle_errors(FD_ERROR, "main, setting child output");
			}
			if (i == FIRST_PROCESS)
			{
				// in == infile
			}
			else
			{
				if(set_stdin(previous_pipe[READ_FD]) == ERROR)
					handle_errors(FD_ERROR, "main, setting child input");
			}
			// do child stuff 
			close(currrent_pipe[WRITE_FD]);	
		}
		waitpid(pid[i], NULL, 0);
		current_to_previous_pipe(currrent_pipe, previous_pipe);
	}

	return (0);
}