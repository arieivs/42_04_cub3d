#include "cub.h"

int	has_right_file_ext(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 5)
		return (0);
	if (str[len - 4] == '.' && str[len - 3] == 'c' && str[len - 2] == 'u' &&
		str[len - 1] == 'b')
		return (1);
	return (0);
}

int	check_args(int ac, char **av)
{
	int	file_fd;

	if (ac != 2)
		return (error_and_return(WRONG_ARGC, -1));
	if (!has_right_file_ext(av[1]))
		return (error_and_return(WRONG_FILE_EXT, -1));
	file_fd = open(av[1], O_RDONLY);
	if (file_fd == -1)
		return (error_and_return(FILE_INEXISTENT, -1));
	return (file_fd);
}
