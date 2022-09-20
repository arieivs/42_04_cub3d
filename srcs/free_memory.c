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

void	free_parse_info(t_parse_info *parse_info)
{
	if (parse_info->buff)
		free(parse_info->buff);
	parse_info->buff = NULL;
	if (parse_info->line_content)
		free_split(parse_info->line_content);
	parse_info->line_content = NULL;
	if (parse_info->prefix)
		free(parse_info->prefix);
	parse_info->prefix = NULL;
	if (parse_info->colors)
		free_split(parse_info->colors);
	parse_info->colors = NULL;
	if (parse_info->colors_rgb)
		free(parse_info->colors_rgb);
	parse_info->colors_rgb = NULL;
	if (parse_info->file_name)
		free(parse_info->file_name);
	parse_info->file_name = NULL;
}

void	graceful_exit(t_cub *cub)
{
	if (cub)
		free_cub(cub);
	ft_putstr_fd("Goodbye!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
