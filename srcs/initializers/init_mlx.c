/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:14:48 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:14:50 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub->walls[i].tex = (t_img *)calloc_or_exit(sizeof(t_img), 1);
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

/* Initialising mlx and all images
 * images: main img, walls' images and map/navigator image
* +2 when sizing navigator: accomodating for borders
*/
void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		error_and_exit(MLX_FAILURE);
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Let's play!");
	cub->img = (t_img *)calloc_or_exit(sizeof(t_img), 1);
	cub->img->width = WIDTH;
	cub->img->height = HEIGHT;
	cub->img->img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img->addr = mlx_get_data_addr(cub->img->img_ptr,
			&cub->img->bits_per_pixel, &cub->img->line_length,
			&cub->img->endian);
	init_textures(cub);
	cub->nav_img = (t_img *)calloc_or_exit(sizeof(t_img), 1);
	cub->nav_img->width = PIXEL_PER_SQUARE * (cub->map_width + 2);
	if (cub->nav_img->width > WIDTH / NAV_FRACT + 2 * PIXEL_PER_SQUARE)
		cub->nav_img->width = WIDTH / NAV_FRACT + 2 * PIXEL_PER_SQUARE;
	cub->nav_img->height = PIXEL_PER_SQUARE * (cub->map_height + 2);
	if (cub->nav_img->height > HEIGHT / NAV_FRACT + 2 * PIXEL_PER_SQUARE)
		cub->nav_img->height = HEIGHT / NAV_FRACT + 2 * PIXEL_PER_SQUARE;
	cub->nav_img->img_ptr = mlx_new_image(cub->mlx, cub->nav_img->width,
			cub->nav_img->height);
	cub->nav_img->addr = mlx_get_data_addr(cub->nav_img->img_ptr,
			&cub->nav_img->bits_per_pixel, &cub->nav_img->line_length,
			&cub->nav_img->endian);
}
