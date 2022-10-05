#include "cub.h"

t_cub	init_cub(void)
{
	t_cub	cub;

	cub.mlx = NULL;
	cub.window = NULL;
	cub.img = NULL;
	cub.addr = NULL;
	cub.walls.no_fd = 0;
	cub.walls.so_fd = 0;
	cub.walls.we_fd = 0;
	cub.walls.ea_fd = 0;
	cub.floor_color = 0;
	cub.ceil_color = 0;
	cub.map = NULL;
	cub.map_height = 0;
	cub.map_width = 0;
	cub.pos = (t_pair_d *)calloc_or_exit(sizeof(t_pair_d), 1, &cub);
	cub.pos->x = 0.0;
	cub.pos->y = 0.0;
	cub.dir = (t_pair_d *)calloc_or_exit(sizeof(t_pair_d), 1, &cub);
	cub.dir->x = 0.0;
	cub.dir->y = 0.0;
	cub.proj_plane = (t_pair_d *)calloc_or_exit(sizeof(t_pair_d), 1, &cub);
	cub.proj_plane->x = 0.0;
	cub.proj_plane->y = 0.0;
	cub.time = 0;
	cub.old_time = 0;
	cub.map_pos = (t_pair_i *)calloc_or_exit(sizeof(t_pair_i), 1, &cub);
	cub.ray_dir = (t_pair_d *)calloc_or_exit(sizeof(t_pair_d), 1, &cub);
	cub.side_dist = (t_pair_d *)calloc_or_exit(sizeof(t_pair_d), 1, &cub);
	cub.delta_dist = (t_pair_d *)calloc_or_exit(sizeof(t_pair_d), 1, &cub);
	cub.step = (t_pair_i *)calloc_or_exit(sizeof(t_pair_i), 1, &cub);
	return (cub);
}

t_parse_info	init_parse_info(void)
{
	t_parse_info	parse_info;

	parse_info.buff	= NULL;
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

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Let's play!");
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel,
			&cub->line_length, &cub->endian);
}
