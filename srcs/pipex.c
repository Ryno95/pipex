#include "../pipex.h"

t_bool	is_valid_arguments(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	return (FALSE);
}

void	run(int argc, char *argv[], char *env[])
{
	if (!is_valid_arguments(argc, argv))
		return ;
	(void)env;
	return ;
}
