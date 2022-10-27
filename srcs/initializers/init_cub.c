/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:15:01 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:15:03 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_pair_d	*init_pair_double(void)
{
	t_pair_d	*pair;

	pair = (t_pair_d *)calloc_or_exit(sizeof(t_pair_d), 1);
	pair->x = 0.0;
	pair->y = 0.0;
	return (pair);
}

t_pair_i	*init_pair_int(void)
{
	t_pair_i	*pair;

	pair = (t_pair_i *)calloc_or_exit(sizeof(t_pair_i), 1);
	pair->x = 0;
	pair->y = 0;
	return (pair);
}

static void	init_raycast_vars(t_cub *cub)
{
	cub->pos = init_pair_double();
	cub->dir = init_pair_double();
	cub->proj_plane = init_pair_double();
	cub->camera_x = 0.0;
	cub->ray_dir = init_pair_double();
	cub->map_pos = init_pair_int();
	cub->side_dist = init_pair_double();
	cub->delta_dist = init_pair_double();
	cub->perp_wall_dist = 0.0;
	cub->step = init_pair_int();
	cub->hit = 0;
	cub->texel = init_pair_int();
	cub->wall_x = 0.0;
	cub->texel_step = 0.0;
	cub->texel_pos = 0.0;
	cub->line_height = 0;
	cub->draw_start = 0;
	cub->draw_end = 0;
}

static void	init_keys_and_mouse(t_cub *cub)
{
	cub->keys.w = 0;
	cub->keys.a = 0;
	cub->keys.s = 0;
	cub->keys.d = 0;
	cub->keys.up = 0;
	cub->keys.down = 0;
	cub->keys.left = 0;
	cub->keys.right = 0;
	cub->mouse.left = 0;
	cub->mouse.right = 0;
}

t_cub	*init_cub(int map_fd)
{
	t_cub	*cub;
	int		i;

	cub = (t_cub *)calloc_or_exit(sizeof(t_cub), 1);
	get_cub(cub);
	cub->mlx = NULL;
	cub->window = NULL;
	cub->img = NULL;
	cub->map_fd = map_fd;
	i = 0;
	while (i < 4)
	{
		cub->walls[i].path = NULL;
		cub->walls[i++].tex = NULL;
	}
	cub->f_color = 0;
	cub->c_color = 0;
	cub->map = NULL;
	cub->map_height = 0;
	cub->map_width = 0;
	init_raycast_vars(cub);
	init_keys_and_mouse(cub);
	cub->nav_img = NULL;
	return (cub);
}
