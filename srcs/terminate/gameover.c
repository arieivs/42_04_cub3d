#include "cub.h"

void	error_message(t_error_code error_code)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (error_code == WRONG_ARGC)
		ft_putstr_fd("Wrong number of arguments. Please provide a .cub file\n",
			STDERR_FILENO);
	else if (error_code == WRONG_FILE_EXT)
		ft_putstr_fd("Wrong file extension. Please provide a .cub file\n",
			STDERR_FILENO);
	else if (error_code == FILE_INEXISTENT)
		ft_putstr_fd("Inexistent file.\n", STDERR_FILENO);
	else if (error_code == MAP_INCORRECT)
		ft_putstr_fd("Incorrect Map. Please provide a valid .cub file\n",
			STDERR_FILENO);
	else if (error_code == MLX_FAILURE)
		ft_putstr_fd("MiniLibx failure. Please check your configuration\n",
			STDERR_FILENO);
	else
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
}

int	error_and_return(t_error_code error_code, int return_value)
{
	error_message(error_code);
	return (return_value);
}

void	error_and_exit(t_error_code error_code, t_cub *cub)
{
	if (cub)
		free_cub(cub);
	error_message(error_code);
	exit(EXIT_FAILURE);
}

void	error_and_exit_from_parsing(t_error_code error_code, t_cub *cub,
			t_parse_info *parse_info, int map_fd)
{
	if (parse_info)
		free_parse_info(parse_info);
	close(map_fd);
	error_and_exit(error_code, cub);
}

void	*calloc_or_exit(size_t size, int count, t_cub *cub)
{
	void	*result;

	result = ft_calloc(size, count);
	if (!result)
		error_and_exit(ERRNO, cub);
	return (result);
}
