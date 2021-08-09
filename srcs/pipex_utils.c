#include "../pipex.h"
#include "utils/gnl/get_next_line.h"

int	redirect_stdin_and_stdout(int new_stdin, int new_stdout)
{
	if (dup2(new_stdin, STDIN_FD) == ERROR)
		return (0);
	if (dup2(new_stdout, STDOUT_FD) == ERROR)
		return (0);
	return (1);
}

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

char	*get_executable_path(const char *env_var, const char *cmd)
{
	char	**split_paths;
	char	*path_and_exe;
	int		i;

	split_paths = ft_split(env_var, COLON);
	if (!split_paths || ! cmd)
		return (NULL);
	i = 0;
	while (split_paths[i])
	{
		path_and_exe = ft_strjoin(split_paths[i], FORWARD_SLASH);
		path_and_exe = ft_gnl_strjoin(path_and_exe, (char *)cmd);
		if (!path_and_exe)
			return (NULL);
		if (access(path_and_exe, F_OK) == F_OK)
			return (path_and_exe);
		free(path_and_exe);
		i++;
	}
	return (NULL);
}
