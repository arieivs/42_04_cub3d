#include "cub.h"

unsigned int	get_texture_color(t_img *texture, int pixel_x, int pixel_y)
{
	return (*(unsigned int *)((texture->addr
			+ (pixel_y * texture->line_length)
			+ (pixel_x * texture->bits_per_pixel / 8))));
}
