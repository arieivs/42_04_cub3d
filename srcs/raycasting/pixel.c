#include "cub.h"

void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->img->addr + (y * cub->img->line_length +
		x * (cub->img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
