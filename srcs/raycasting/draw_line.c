#include "cub.h"

void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->addr + (y * cub->line_length + x * (cub->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_verline(t_cub *cub, int x, unsigned int color)
{
	int	i;

	i = 0;
	while (i < HEIGHT)
	{
		if (i >= cub->draw_start && i <= cub->draw_end)
			my_mlx_pixel_put(cub, x, i, color);
		else if (i <= cub->draw_start)
			my_mlx_pixel_put(cub, x, i, cub->ceil_color);
		else if (i >= cub->draw_end)
			my_mlx_pixel_put(cub, x, i, cub->floor_color);
		i++;
	}
}

int	set_pixel_color(t_cub *cub)
{
	unsigned int	color;

	if (cub->map[cub->map_pos->y][cub->map_pos->x] == 1)
		color = 0x00FFF000;
	else if (cub->map[cub->map_pos->y][cub->map_pos->x] == 2)
		color = 0x0000FF00;
	else if (cub->map[cub->map_pos->y][cub->map_pos->x] == 3)
		color = 0x000000FF;
	else if (cub->map[cub->map_pos->y][cub->map_pos->x] == 4)
		color = 0x00FFFF00;
	else
		color = 0x00FFFFFF;
	return (color);
}

unsigned int	set_pixels(t_cub *cub)
{
	unsigned int	color;

	cub->line_height = (int)(((double)HEIGHT) / cub->perp_wall_dist);
	cub->draw_start = (- cub->line_height + HEIGHT) / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = (cub->line_height + HEIGHT) / 2;
	if (cub->draw_end >= HEIGHT)
		cub->draw_end = HEIGHT - 1;
	color = set_pixel_color(cub);
	if (cub->side == 1)
		color = color / 1.25;
	return (color);
}
