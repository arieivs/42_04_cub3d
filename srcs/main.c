#include "cub.h"

int	key_hook(int keycode, t_cub *cub)
{
	double	edge;
	double	move_speed;
	double	rot_speed;

	edge = 1.1;
	move_speed = 0.5;
	rot_speed = 0.08;
	if (keycode == ESC_KEY)
		graceful_exit(cub);
	else if (keycode == W_KEY || keycode == UP_KEY)
		move_forward(cub, edge, move_speed);
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		move_backward(cub, edge, move_speed);
	else if (keycode == LEFT_KEY)
		rotate_left(cub, rot_speed);
	else if (keycode == RIGHT_KEY)
		rotate_right(cub, rot_speed);
	else if (keycode == A_KEY)
		move_left(cub, edge, move_speed);
	else if (keycode == D_KEY)
		move_right(cub, edge, move_speed);
	raycast_loop(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img, 0, 0);
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
	init_mlx(&cub);
	validate_map(map_fd, av[1], &cub);
	print_cub(&cub);
	// free_cub(&cub); // just for now
	raycast_loop(&cub);
	mlx_put_image_to_window(cub.mlx, cub.window, cub.img, 0, 0);
	mlx_loop_hook(cub.mlx, display_fps, &cub);
	mlx_hook(cub.window, 2, 1L << 0, key_hook, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
