#ifndef PIPEX_UTILS_H
# define PIPEX_UTILS_H

void	close_multiple(int fd1, int fd2);
void	wait_multiple(int *pid, int length);
char	*ft_get_env_var(const char *env[], const char *env_variable);

#endif