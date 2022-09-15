#include "cub"

void	*calloc_or_exit(size_t size, int count)
{
	void	*result;

	result = ft_calloc(size, count);
	if (!result)
		error_and_exit(MEMORY_FAIL);
	return (result);
}

int	open_or_exit(char *file_path, mode_t mode)
{
	int	fd;

	fd = open(file_path, mode, 00755);
	if (fd == -1)
		error_and_exit(OPEN_FAIL);
	return (fd);
}

void	error_and_exit(t_cub cub)
{

	if (cub)
		free_cub(cub);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	exit(errno); // or EXIT_FAILURE?
}
