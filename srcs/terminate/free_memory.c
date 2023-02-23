/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:16:38 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:16:39 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* Free cub
 * Not protecting close because we're already leaving,
 * this function is only called when exiting the programme.
 * If the map_fd was already closed, its value is 0.
 *
 * mlx_destroy_display is only available on LINUX version of mlx... add:
 * int	mlx_destroy_display(void *xvar);
 * on mlx.h on MAC, to avoid compilation errors (no need to define it)
 * (now I understand why everyone said mlx had leaks...)
 */
void	free_cub(t_cub *cub)
{
	if (cub->window)
		mlx_destroy_window(cub->mlx, cub->window);
	free_img(cub->img, cub);
	free_img(cub->nav_img, cub);
	free_map_and_walls(cub);
	if (cub->map_fd != 0)
		close(cub->map_fd);
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
	if (cub->mlx)
	{
		#if LINUX
		mlx_destroy_display(cub->mlx);
        #endif
		free(cub->mlx);
	}
	if (cub)
		free(cub);
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
	if (parse_info->line)
		free(parse_info->line);
	parse_info->line = NULL;
	if (parse_info->prefix)
		free(parse_info->prefix);
	parse_info->prefix = NULL;
	if (parse_info->content)
		free(parse_info->content);
	parse_info->content = NULL;
	if (parse_info->colors)
		free_split(parse_info->colors);
	parse_info->colors = NULL;
	if (parse_info->colors_rgb)
		free(parse_info->colors_rgb);
	parse_info->colors_rgb = NULL;
}
