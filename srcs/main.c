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
	raycast(&cub);
	mlx_put_image_to_window(cub.mlx, cub.window, cub.img, 0, 0);
	mlx_loop_hook(cub.mlx, display_fps, &cub);
	mlx_hook(cub.window, 2, 1L << 0, key_hook, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
