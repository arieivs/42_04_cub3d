#include "cub.h"

int	main(int ac, char **av)
{
	t_cub	cub;
	int		map_fd;

	map_fd = check_args(ac, av);
	if (map_fd == -1)
		return (1);
	cub = init_cub();
	validate_map(map_fd, av[1], &cub);
	print_cub(&cub);
	init_mlx_and_raycast(&cub);
	init_textures(&cub);
	raycast(&cub);
	mlx_hook(cub.window, 3, 1L << 1, key_up, &cub);
	mlx_hook(cub.window, 2, 1L << 0, key_down, &cub);
	mlx_loop_hook(cub.mlx, update_display, &cub);
	// int pos = (10 * cub.line_length + 10 * (cub.bits_per_pixel / 8));
	// printf("pos value is %d\n", pos);
	mlx_loop(cub.mlx);
	return (0);
}
