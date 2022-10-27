/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:16:12 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:16:13 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	draw_square(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < PIXEL_PER_SQUARE)
	{
		j = 0;
		while (j < PIXEL_PER_SQUARE)
		{
			if (i == 0 || i == PIXEL_PER_SQUARE - 1
				|| j == 0 || j == PIXEL_PER_SQUARE - 1)
				my_mlx_pixel_put(cub->nav_img, x + i, y + j, 0x00000000);
			else
				my_mlx_pixel_put(cub->nav_img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

/* Borders (start/end x and y) are respective to the map grid,
 * not to the pixels on the screen.
 * Decided navigator cannot take more than a 1/3 of screen width/height,
 * this value was arbitrary (NAV_FRACT).
 */
static void	set_navigation_x_borders(t_pair_i *start, t_pair_i *end, t_cub *cub)
{
	int	nav_width;

	nav_width = PIXEL_PER_SQUARE * cub->map_width;
	start->x = 0;
	end->x = cub->map_width;
	if (nav_width > WIDTH / NAV_FRACT)
	{
		start->x = (int)(cub->pos->x - (double)WIDTH
				/ ((double)NAV_FRACT * 2.0 * (double)PIXEL_PER_SQUARE));
		if (start->x < 0)
			start->x = 0;
		end->x = start->x + WIDTH / (NAV_FRACT * PIXEL_PER_SQUARE);
		if (end->x > cub->map_width)
		{
			end->x = cub->map_width;
			start->x = end->x - WIDTH / (NAV_FRACT * PIXEL_PER_SQUARE);
		}
	}
}

static void	set_navigation_y_borders(t_pair_i *start, t_pair_i *end, t_cub *cub)
{
	int	nav_height;

	nav_height = PIXEL_PER_SQUARE * cub->map_height;
	start->y = 0;
	end->y = cub->map_height;
	if (nav_height > HEIGHT / NAV_FRACT)
	{
		start->y = (int)(cub->pos->y - (double)HEIGHT
				/ ((double)NAV_FRACT * 2.0 * (double)PIXEL_PER_SQUARE));
		if (start->y < 0)
			start->y = 0;
		end->y = start->y + HEIGHT / (NAV_FRACT * PIXEL_PER_SQUARE);
		if (end->y > cub->map_height)
		{
			end->y = cub->map_height;
			start->y = end->y - HEIGHT / (NAV_FRACT * PIXEL_PER_SQUARE);
		}
	}
}

/* The counters i and j represent the point in the map grid
 * we are looking at. To convert it to the pixel screen,
 * one must remove the offset and * PIXEL_PER_SQUARE
*/
static void	actual_draw_navigator(t_cub *cub, t_pair_i start, t_pair_i end)
{
	int	i;
	int	j;

	i = start.y - 1;
	while (i < end.y + 1)
	{
		j = start.x - 1;
		while (j < end.x + 1)
		{
			if (i == start.y - 1 || i == end.y || j == start.x - 1 || j == end.x)
				draw_square(cub, (j - start.x + 1) * PIXEL_PER_SQUARE,
					(i - start.y + 1) * PIXEL_PER_SQUARE, 0x00000000);
			else if (cub->map[i][j] == OUT)
				draw_square(cub, (j - start.x + 1) * PIXEL_PER_SQUARE,
					(i - start.y + 1) * PIXEL_PER_SQUARE, 0x00000000);
			else if (cub->map[i][j] == IN || cub->map[i][j] == PLAYER)
				draw_square(cub, (j - start.x + 1) * PIXEL_PER_SQUARE,
					(i - start.y + 1) * PIXEL_PER_SQUARE, 0x00333333);
			else if (cub->map[i][j] == WALL)
				draw_square(cub, (j - start.x + 1) * PIXEL_PER_SQUARE,
					(i - start.y + 1) * PIXEL_PER_SQUARE, 0x00FFFFFF);
			j++;
		}
		i++;
	}
}

/* Draw Navigator 🗺
 * - sets the borders of our little navigator: if the original map
 *   is too big, then only a part is shown
 * - draws the navigator
 * - draws the player as a red square: tried to add a small line
 *   to show in which direction the player was looking, but didn't
 *   look very well...
 */
void	draw_navigator(t_cub *cub)
{
	t_pair_i	start;
	t_pair_i	end;

	set_navigation_x_borders(&start, &end, cub);
	set_navigation_y_borders(&start, &end, cub);
	actual_draw_navigator(cub, start, end);
	draw_square(cub, ((int)cub->pos->x - start.x + 1) * PIXEL_PER_SQUARE,
		((int)cub->pos->y - start.y + 1) * PIXEL_PER_SQUARE, 0x00FF0000);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->nav_img->img_ptr, 0, 0);
}
