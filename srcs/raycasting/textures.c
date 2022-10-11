#include "cub.h"

t_dir_code	get_wall_dir(t_cub *cub)
{
	if (cub->side == SIDE_Y && cub->map_pos->y < cub->pos->y)
		return (NO);
	if (cub->side == SIDE_Y && cub->map_pos->y > cub->pos->y)
		return (SO);
	if (cub->side == SIDE_X && cub->map_pos->x < cub->pos->x)
		return (WE);
	return (EA);
}

void	calculate_wall_x(t_cub *cub)
{
	if (cub->side == SIDE_X)
		cub->wall_x = cub->pos->y + cub->perp_wall_dist * cub->ray_dir->y;
	else
		cub->wall_x = cub->pos->x + cub->perp_wall_dist * cub->ray_dir->x;
	cub->wall_x -= floor(cub->wall_x);
}

void	calculate_tex_x(t_cub *cub)
{
	cub->texel->x = (int)(cub->wall_x * ((double)ASSET_SIZE));
	if (cub->side == SIDE_X && cub->ray_dir->x > 0)
		cub->texel->x = ASSET_SIZE - cub->texel->x - 1;
	if (cub->side == SIDE_Y && cub->ray_dir->y < 0)
		cub->texel->x = ASSET_SIZE - cub->texel->x - 1;
}

void	draw_texture(int x, int i, t_cub *cub)
{
	t_dir_code		wall_dir;
	unsigned int	color;

	if (i < cub->draw_start)
		color = cub->c_color;
	else if (i > cub->draw_start && i < cub->draw_end)
	{
		cub->texel->y = (int)cub->texel_pos & (ASSET_SIZE - 1);
		cub->texel_pos += cub->texel_step;
		wall_dir = get_wall_dir(cub);
		color = get_texture_color(cub->walls[wall_dir].tex,
				cub->texel->x, cub->texel->y);
	}
	else
		color = cub->f_color;
	my_mlx_pixel_put(cub, x, i, color);
}

void	apply_textures(t_cub *cub, int x)
{
	int	i;

	calculate_wall_x(cub);
	calculate_tex_x(cub);
	cub->texel_step = 1.0 * ASSET_SIZE / cub->line_height;
	cub->texel_pos = (cub->draw_start - HEIGHT / 2
			+ cub->line_height / 2) * cub->texel_step;
	i = 0;
	while (i < HEIGHT)
		draw_texture(x, i++, cub);
}
