#include "cub.h"

void	free_cub(t_cub *cub)
{
	if (cub->mlx)
		mlx_destroy_window(cub->mlx, cub->window);
	if (cub->no_fd != 0)
		close(cub->no_fd);
	if (cub->so_fd != 0)
		close(cub->so_fd);
	if (cub->we_fd != 0)
		close(cub->we_fd);
	if (cub->ea_fd != 0)
		close(cub->ea_fd); // TODO protect close?
	// free cub->map - it will be allocated
	if (cub->pos)
		free(cub->pos);
	if (cub->dir)
		free(cub->dir);
	if (cub->proj_plane)
		free(cub->proj_plane);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_parse_info(t_parse_info	*parse_info)
{
	if (buff)
		free(buff);
	if (line_content)
		free_split(line_content);
}

void	graceful_exit(t_cub *cub)
{
	if (cub)
		free_cub(cub);
	ft_putstr_fd("Goodbye!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
