#include "cub.h"

void	*calloc_or_exit(size_t size, int count)
{
	void	*result;

	result = ft_calloc(size, count);
	if (!result)
		error_and_exit(ERRNO);
	return (result);
}

int	open_or_exit(char *file_path, mode_t mode)
{
	int	fd;

	fd = open(file_path, mode, 00755);
	if (fd == -1)
		error_and_exit(ERRNO);
	return (fd);
}

int	close_or_exit(int fd)
{
	if (close(fd) == -1)
		error_and_exit(ERRNO);
	return (0);
}
