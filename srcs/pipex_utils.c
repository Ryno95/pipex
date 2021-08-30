#include "headers/defines.h"

char	*ft_get_env_var(const char *env[], const char *env_variable)
{
	const int	var_len = ft_strlen(env_variable);
	int			i;

	if (!env || !env_variable)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], env_variable, var_len) == 0)
			return (((char *)env[i]) + var_len);
		i++;
	}
	return (NULL);
}

int	redirect_stdin_and_stdout(int new_stdin, int new_stdout)
{
	if (dup2(new_stdin, STDIN_FD) == ERROR)
		return (0);
	if (dup2(new_stdout, STDOUT_FD) == ERROR)
		return (0);
	return (1);
}

void	wait_multiple(int *pid, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

void	close_multiple(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
