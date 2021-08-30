#include "headers/defines.h"
#include "headers/pipex_utils.h"
#include "utils/gnl/get_next_line.h"
#include <unistd.h>

static void	append_command_to_path(char	*buffer, const char *command)
{
	const int	cmd_len = ft_strlen(command) + TERMINATOR;

	*buffer = FORWARD_SLASH;
	buffer += 1;
	ft_strlcpy(buffer, command, cmd_len);
}

static int	get_sub_path_len(const char *path)
{
	int	i;

	i = 0;
	while (path && path[i] != '\0' && path[i] != COLON)
		i++;
	return (i);
}

static void	copy_possible_path_to_buffer(const char *all_paths,
		char *buffer, int size)
{
	ft_strlcpy(buffer, all_paths, size + TERMINATOR);
}

int	is_executable(char *full_path_executable)
{
	return (access(full_path_executable, F_OK));
}

char	*get_executable_path(const char *env[], const char *command)
{
	const char	*all_paths = ft_get_env_var(env, PATH_ID);
	char		buffer[CMD_BUFFER_SIZE];
	int			single_path_len;

	if (!command || !all_paths)
		return (NULL);
	else if (ft_strchr(command, FORWARD_SLASH)
		&& is_executable((char *) command) == F_OK)
		return (ft_strdup(command));
	while (all_paths && *all_paths)
	{
		single_path_len = get_sub_path_len(all_paths);
		copy_possible_path_to_buffer(all_paths, &buffer[0], single_path_len);
		append_command_to_path(&buffer[single_path_len], command);
		if (is_executable(buffer) == F_OK)
			return (ft_strdup(&buffer[0]));
		all_paths += single_path_len;
		if (*all_paths == COLON)
			++all_paths;
	}
	return (NULL);
}
