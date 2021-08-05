#include "../pipex.h"
#include "../utils/gnl/get_next_line.h"

char	*get_executable_path(const char *env, const char *cmd)
{
	char	*trimmed_env = ft_strtrim(env, "PATH=");
	char	**split_paths = ft_split(trimmed_env, COLON);
	char	*path_and_exe;

	if (!split_paths || ! cmd)
		return (NULL);

	for (int i = 0; split_paths[i]; i++)
	{
		path_and_exe = ft_strjoin(split_paths[i], FORWARD_SLASH);
		path_and_exe = ft_gnl_strjoin(path_and_exe, (char *)cmd);
		if (!path_and_exe)
			return (NULL);
		if (access(path_and_exe, F_OK) == F_OK)
			printf("%s\n", path_and_exe);
		free(path_and_exe);
	}
	return (NULL);
}