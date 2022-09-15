#include "cub.h"

t_cub	init_cub(void)
{
	t_cub	cub;

	cub.mlx = mlx_init();
	cub.window = mlx_new_window(cub.mlx, WIDTH, HEIGHT, "Janela");
	cub.img = mlx_new_image(cub.mlx, WIDTH, HEIGHT);
	cub.addr = mlx_get_data_addr(cub.img, &cub.bits_per_pixel,
			&cub.line_length, &cub.endian);
	cub.no_fd = 0;
	cub.so_fd = 0;
	cub.we_fd = 0;
	cub.ea_fd = 0;
	cub.floor_color = 0;
	cub.ceil_color = 0;
	cub.map = NULL;
	cub.pos->x = 0.0;
	cub.pos->y = 0.0;
	cub.dir->x = 0.0;
	cub.dir->y = 0.0;
	return (cub);
}