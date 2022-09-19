#include "cub.h"

void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->addr + (y * cub->line_length + x * (cub->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ver_line(t_cub *cub, int x, unsigned int color)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		if (i >= cub->draw_start && i <= cub->draw_end)
			my_mlx_pixel_put(cub, x, i, color);
		else
			my_mlx_pixel_put(cub, x, i, 0x00000000);
	}
}

int	set_pixel_color(t_cub *cub)
{
	unsigned int	color;

	if (g_worldMap[cub->map_pos->x][cub->map_pos->y] == 1)
		color = 0x00FF0000; // red
	else if (g_worldMap[cub->map_pos->x][cub->map_pos->y] == 2)
		color = 0x0000FF00; // green
	else if (g_worldMap[cub->map_pos->x][cub->map_pos->y] == 3)
		color = 0x000000FF; // blue
	else if (g_worldMap[cub->map_pos->x][cub->map_pos->y] == 4)
		color = 0x00FFFF00;	// yellow
	else
		color = 0x00FFFFFF; // white
	return (color);
}

unsigned int	draw_pixels(t_cub *cub)
{
	unsigned int	color;

	cub->line_height = (int)(((double)HEIGHT) / cub->perp_wall_dist);
	cub->draw_start = -cub->line_height / 2 + HEIGHT / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = cub->line_height / 2 + HEIGHT / 2;
	if (cub->draw_end >= HEIGHT)
		cub->draw_end = HEIGHT - 1;
	color = set_pixel_color(cub);
	if (cub->side == 1)
		color = color / 1.25;
	return (color);
}