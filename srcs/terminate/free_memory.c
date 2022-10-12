#include "cub.h"

static void	free_img(t_img *img, t_cub *cub)
{
	if (!img)
		return ;
	mlx_destroy_image(cub->mlx, img->img_ptr);
	free(img);
}

static void	free_map_and_walls(t_cub *cub)
{
	int	i;

	i = 0;
	if (cub->map)
	{
		while (i < cub->map_height)
			free(cub->map[i++]);
		free(cub->map);
		cub->map = NULL;
	}
	i = 0;
	while (i < 4)
	{
		if (cub->walls[i].path)
			free(cub->walls[i].path);
		free_img(cub->walls[i].tex, cub);
		i++;
	}
}

void	free_cub(t_cub *cub)
{
	if (cub->window)
		mlx_destroy_window(cub->mlx, cub->window);
	free_img(cub->img, cub);
	free_img(cub->nav_img, cub);
	free_map_and_walls(cub);
	if (cub->pos)
		free(cub->pos);
	if (cub->dir)
		free(cub->dir);
	if (cub->proj_plane)
		free(cub->proj_plane);
	if (cub->ray_dir)
		free(cub->ray_dir);
	if (cub->map_pos)
		free(cub->map_pos);
	if (cub->side_dist)
		free(cub->side_dist);
	if (cub->delta_dist)
		free(cub->delta_dist);
	if (cub->step)
		free(cub->step);
	if (cub->texel)
		free(cub->texel);
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
	if (parse_info->line_trimmed)
		free(parse_info->line_trimmed);
	parse_info->line_trimmed = NULL;
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
