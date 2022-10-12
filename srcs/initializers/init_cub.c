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

static void	init_raycast_vars(t_cub *cub)
{
	cub->pos = init_pair_double(cub);
	cub->dir = init_pair_double(cub);
	cub->proj_plane = init_pair_double(cub);
	cub->camera_x = 0.0;
	cub->ray_dir = init_pair_double(cub);
	cub->map_pos = init_pair_int(cub);
	cub->side_dist = init_pair_double(cub);
	cub->delta_dist = init_pair_double(cub);
	cub->perp_wall_dist = 0.0;
	cub->step = init_pair_int(cub);
	cub->hit = 0;
	cub->texel = init_pair_int(cub);
	cub->wall_x = 0.0;
	cub->texel_step = 0.0;
	cub->texel_pos = 0.0;
	cub->line_height = 0;
	cub->draw_start = 0;
	cub->draw_end = 0;
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

t_cub	init_cub(void)
{
	t_cub	cub;
	int		i;

	cub.mlx = NULL;
	cub.window = NULL;
	cub.img = NULL;
	i = 0;
	while (i < 4)
		cub.walls[i++].path = NULL;
	cub.f_color = 0;
	cub.c_color = 0;
	cub.map = NULL;
	cub.map_height = 0;
	cub.map_width = 0;
	init_raycast_vars(&cub);
	init_keys(&cub);
	cub.nav_img = NULL;
	return (cub);
}
