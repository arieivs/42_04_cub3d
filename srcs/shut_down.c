# include "cub.h"

void	free_cub(t_cub *cub)
{
	// free map - it will be allocated
}

void	graceful_exit(t_cub cub)
{

	if (cub)
		free_cub(cub);
	ft_putstr_fd("Goodbye!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
