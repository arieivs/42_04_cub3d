#include "cub.h"

int	graceful_exit(t_cub *cub)
{
	if (cub)
		free_cub(cub);
	ft_putstr_fd("Goodbye!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
