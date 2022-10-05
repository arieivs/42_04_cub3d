#include "cub.h"

int update_display(t_cub *cub)
{
	static int fps = 0;

	if (fps++ == 5)
	{
		if (cub->keys.w || cub->keys.up)
			move_forward(cub, 1.1, 0.08);
		else if (cub->keys.s || cub->keys.down)
			move_backward(cub, 1.1, 0.08);
		if (cub->keys.left)
			rotate_left(cub, 0.04);
		else if (cub->keys.right)
			rotate_right(cub, 0.04);
		if (cub->keys.a)
			move_left(cub, 1.1, 0.08);
		else if (cub->keys.d)
			move_right(cub, 1.1, 0.08);
		if (cub->keys.w || cub->keys.a || cub->keys.s || cub->keys.d
			|| cub->keys.up || cub->keys.down || cub->keys.left || cub->keys.right)
		{
			raycast(cub);
			mlx_put_image_to_window(cub->mlx, cub->window, cub->img, 0, 0);
		}
		fps = 0;
	}
	return (0);
}

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
	init_mlx(&cub);
	raycast(&cub);
	mlx_put_image_to_window(cub.mlx, cub.window, cub.img, 0, 0);
	mlx_hook(cub.window, 3, 1L << 1, key_up, &cub);
	mlx_hook(cub.window, 2, 1L << 0, key_down, &cub);
	mlx_loop_hook(cub.mlx, update_display, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
