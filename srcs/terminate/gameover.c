#include "cub.h"

static void	error_message_parse(t_error_code error_code)
{
	if (error_code == READ_FAIL)
		ft_putstr_fd("Something went wrong when reading the file.\n",
			STDERR_FILENO);
	else if (error_code == MAP_INCOMPLETE)
		ft_putstr_fd("Incomplete Map. Please provide a valid .cub file\n",
			STDERR_FILENO);
	else if (error_code == MAP_TEXT_COLOR_INCORRECT)
	{
		ft_putstr_fd("Incorrect Map - the textures and/or colors values ",
			STDERR_FILENO);
		ft_putstr_fd("are incorrect. Please provide a valid .cub file\n",
			STDERR_FILENO);
	}
	else if (error_code == MAP_INCORRECT)
		ft_putstr_fd("Incorrect Map. Please provide a valid .cub file\n",
			STDERR_FILENO);
}

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
	else if (error_code == READ_FAIL || error_code == MAP_INCOMPLETE ||
		error_code == MAP_TEXT_COLOR_INCORRECT || error_code == MAP_INCORRECT)
		error_message_parse(error_code);
	else if (error_code == MLX_FAILURE)
		ft_putstr_fd("MiniLibx failure. Please check your configuration\n",
			STDERR_FILENO);
	else
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

int	error_and_return(t_error_code error_code, int return_value)
{
	error_message(error_code);
	return (return_value);
}

void	error_and_exit(t_error_code error_code)
{
	t_cub			*cub;
	t_parse_info	*parse_info;

	cub = get_cub(NULL);
	parse_info = get_parse_info(NULL, 0);
	if (cub)
		free_cub(cub);
	if (parse_info)
		free_parse_info(parse_info);
	error_message(error_code);
	exit(EXIT_FAILURE);
}
