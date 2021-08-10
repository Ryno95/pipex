#include "../headers/defines.h"
#include "../headers/get_exe_path.h"
#include "../headers/pipex_utils.h"
#include "../headers/handle_errors.h"
#include <stdio.h> 

#define MAX_PROCESSES 1084

typedef struct s_multi_pipe_fd
{
	int	fd[PIPE_BOTH_ENDS];
}	t_multi_pipe_fd;


t_multi_pipe_fd	*create_multiple_pipes(int num_of_pipes)
{
	int					i;
	t_multi_pipe_fd		**pipes;

	i = 0;
	pipes = (t_multi_pipe_fd **)ft_calloc(sizeof(t_multi_pipe_fd *), 1);
	while (i < num_of_pipes)
	{
		pipes[i] = (t_multi_pipe_fd *)malloc(sizeof(t_multi_pipe_fd));
		if (!pipes[i])
			return (NULL);
		if (pipe(pipes[i]->fd) == ERROR)
			return (NULL);
		i++;
		printf("%d\n", i);
	}
	return (pipes);
}

void	close_un_used_fds(int number_of_pipes, t_multi_pipe_fd **pipe_fd, int process)
{
	int j;

	j = 0;
	while (j < number_of_pipes)
	{
		if (process != j)
			close((pipe_fd[j])->fd[READ_FD]);
		if (process + 1 != j)
			close(pipe_fd[j]->fd[WRITE_FD]);
		j++;
	}
}

int	fork_processes(int num_of_processes, int **pid, t_multi_pipe_fd **pipe_fd, int number_of_pipes)
{
	int	i;
	int	j;
	for (i = 0; i < num_of_processes; i++)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			printf("ERROR CREATING PROCESS");
		if (pid[i] == 0)
		{
			// child process
			close_un_used_fds(number_of_pipes, pipe_fd, i);
			// do child thingies
			//  here
			close(pipe_fd[i]->fd[READ_FD]);
			close(pipe_fd[i + 1]->fd[WRITE_FD]);
			return 0;
		}
	}
	return (0);
}

int main(int argc, const char *argv[], const char *env[])
{
	const int				num_of_processes = argc - 3;
	const int				num_of_pipes = argc - 4;
	t_multi_pipe_fd			**pipe_fd;
	int						pid[MAX_PROCESSES];
	(void)argv;
	(void)env;
	pipe_fd = create_multiple_pipes(num_of_pipes);
	if (pipe_fd == NULL)
		handle_errors(PIPE_ERROR, "Multipipe creator");
	if (!fork_processes(num_of_processes, &pid[0], pipe_fd, num_of_pipes))
		printf("you fucked uuup\n");
	free(pipe_fd);
	return (0);
}
