/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:11:58 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/11 11:18:19 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_pair_d	*init_pair_double(t_cub *cub)
{
	t_pair_d	*pair;

	pair = (t_pair_d *)calloc_or_exit(sizeof(t_pair_d), 1, cub);
	pair->x = 0.0;
	pair->y = 0.0;
	return (pair);
}

t_pair_i	*init_pair_int(t_cub *cub)
{
	t_pair_i	*pair;

	pair = (t_pair_i *)calloc_or_exit(sizeof(t_pair_i), 1, cub);
	pair->x = 0;
	pair->y = 0;
	return (pair);
}

static void	init_keys(t_cub *cub)
{
	cub->keys.w = 0;
	cub->keys.a = 0;
	cub->keys.s = 0;
	cub->keys.d = 0;
	cub->keys.up = 0;
	cub->keys.down = 0;
	cub->keys.left = 0;
	cub->keys.right = 0;
}

void	alloc_raycasting_pairs(t_cub *cub)
{
	cub->pos = init_pair_double(cub);
	cub->dir = init_pair_double(cub);
	cub->proj_plane = init_pair_double(cub);
	cub->ray_dir = init_pair_double(cub);
	cub->map_pos = init_pair_int(cub);
	cub->side_dist = init_pair_double(cub);
	cub->delta_dist = init_pair_double(cub);
	cub->step = init_pair_int(cub);
	cub->texel = init_pair_int(cub);
}

t_cub	init_cub(void)
{
	t_cub	cub;
	int		i;

	cub.mlx = NULL;
	cub.window = NULL;
	cub.img = NULL;
	cub.f_color = 0;
	cub.c_color = 0;
	cub.map = NULL;
	cub.map_height = 0;
	cub.map_width = 0;
	alloc_raycasting_pairs(&cub);
	init_keys(&cub);
	i = 0;
	while (i < 4)
		cub.walls[i++].path = NULL;
	return (cub);
}

t_parse_info	init_parse_info(void)
{
	t_parse_info	parse_info;

	parse_info.buff = NULL;
	parse_info.ret = 0;
	parse_info.line_nb = 1;
	parse_info.line_content = NULL;
	parse_info.prefix = NULL;
	parse_info.prefix_len = 0;
	parse_info.colors = NULL;
	parse_info.colors_rgb = NULL;
	parse_info.is_floor_color_set = 0;
	parse_info.is_ceil_color_set = 0;
	parse_info.file_name = NULL;
	parse_info.line_nb_map_start = 0;
	parse_info.max_map_width = 0;
	parse_info.is_player_set = 0;
	return (parse_info);
}

void	init_mlx_and_raycast(t_cub *cub)
{
	cub->pixel_per_square = 12;
	cub->mlx = mlx_init();
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Let's play!");
	cub->img = (t_img *)calloc_or_exit(sizeof(t_img), 1, cub);
	cub->img->img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img->addr = mlx_get_data_addr(cub->img->img_ptr,
			&cub->img->bits_per_pixel, &cub->img->line_length,
			&cub->img->endian);
	init_textures(cub);
}

void	init_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub->walls[i].tex = (t_img *)calloc_or_exit(sizeof(t_img), 1, cub);
		cub->walls[i].tex->width = ASSET_SIZE;
		cub->walls[i].tex->height = ASSET_SIZE;
		cub->walls[i].tex->img_ptr = mlx_xpm_file_to_image(cub->mlx,
				cub->walls[i].path, &(cub->walls[i].tex->width),
				&(cub->walls[i].tex->height));
		cub->walls[i].tex->addr = mlx_get_data_addr(cub->walls[i].tex->img_ptr,
				&cub->walls[i].tex->bits_per_pixel,
				&cub->walls[i].tex->line_length,
				&cub->walls[i].tex->endian);
		i++;
	}
}
