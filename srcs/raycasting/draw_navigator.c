#include "cub.h"

void	draw_square(t_cub *cub, int x, int y, int color)
{
	int i;
	int	j;

	i = 0;
	while (i < cub->pixel_per_square)
	{
		j = 0;
		while (j < cub->pixel_per_square)
		{
			my_mlx_pixel_put(cub, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

/* Borders (start/end x and y) are respective to the map grid,
 * not to the pixels on the screen.
 * Decided navigator cannot take more than a 1/3 of screen width/height,
 * this value was arbitrary.
 */
static void	set_navigation_x_borders(t_pair_i *start, t_pair_i *end, t_cub *cub)
{
	int	nav_width;

	nav_width = cub->pixel_per_square * cub->map_width;
	start->x = 0;
	end->x = cub->map_width;
	if (nav_width > WIDTH / 3)
	{
		start->x = (int)(cub->pos->x - (double)WIDTH / (6.0 * (double)cub->pixel_per_square));
		if (start->x < 0)
			start->x = 0;
		end->x = start->x + WIDTH / (3 * cub->pixel_per_square);
		if (end->x > cub->map_width)
		{
			end->x = cub->map_width;
			start->x = end->x - WIDTH / (3 * cub->pixel_per_square);
		}
	}
}

static void	set_navigation_y_borders(t_pair_i *start, t_pair_i *end, t_cub *cub)
{
	int	nav_height;

	nav_height = cub->pixel_per_square * cub->map_height;
	start->y = 0;
	end->y = cub->map_height;
	if (nav_height > HEIGHT / 3)
	{
		start->y = (int)(cub->pos->y - (double)HEIGHT / (6.0 * (double)cub->pixel_per_square));
		if (start->y < 0)
			start->y = 0;
		end->y = start->y + HEIGHT / (3 * cub->pixel_per_square);
		if (end->y > cub->map_height)
		{
			end->y = cub->map_height;
			start->y = end->y - HEIGHT / (3 * cub->pixel_per_square);
		}
	}
}

/* The counters i and j represent the point in the map grid
 * we are looking at. To convert it to the pixel screen,
 * one must remove the offset and * cub->pixel_per_square
*/
void	draw_navigator(t_cub *cub)
{
	t_pair_i	start;
	t_pair_i	end;
	int	i;
	int	j;

	set_navigation_x_borders(&start, &end, cub);
	set_navigation_y_borders(&start, &end, cub);
	i = start.y;
	while (i < end.y)
	{
		j = start.x;
		while (j < end.x)
		{
			if (cub->map[i][j] == OUT)
				draw_square(cub, (j - start.x) * cub->pixel_per_square,
					(i - start.y) * cub->pixel_per_square, 0x00000000);
			else if (cub->map[i][j] == IN || cub->map[i][j] == PLAYER)
				draw_square(cub, (j - start.x) * cub->pixel_per_square,
					(i - start.y) * cub->pixel_per_square, 0x00333333);
			else if (cub->map[i][j] == WALL)
				draw_square(cub, (j - start.x) * cub->pixel_per_square,
					(i - start.y) * cub->pixel_per_square, 0x00FFFFFF);
			j++;
		}
		i++;
	}
	draw_square(cub, ((int)cub->pos->x - start.x) * cub->pixel_per_square,
		((int)cub->pos->y - start.y) * cub->pixel_per_square, 0x00FF0000);
	//my_mlx_pixel_put(cub, ((int)cub->pos->x - start.x) * cub->pixel_per_square,
	//	((int)cub->pos->y - start.y) * cub->pixel_per_square, 0x00FFF000);
}
