#include "cub.h"

int	key_up(int keycode, t_cub *cub)
{
	if (keycode == W_KEY)
		cub->keys.w = 0;
	if (keycode == A_KEY)
		cub->keys.a = 0;
	if (keycode == S_KEY)
		cub->keys.s = 0;
	if (keycode == D_KEY)
		cub->keys.d = 0;
	if (keycode == UP_KEY)
		cub->keys.up = 0;
	if (keycode == DOWN_KEY)
		cub->keys.down = 0;
	if (keycode == LEFT_KEY)
		cub->keys.left = 0;
	if (keycode == RIGHT_KEY)
		cub->keys.right = 0;
	return (0);
}

int	key_down(int keycode, t_cub *cub)
{
	if (keycode == W_KEY)
		cub->keys.w = 1;
	if (keycode == A_KEY)
		cub->keys.a = 1;
	if (keycode == S_KEY)
		cub->keys.s = 1;
	if (keycode == D_KEY)
		cub->keys.d = 1;
	if (keycode == UP_KEY)
		cub->keys.up = 1;
	if (keycode == DOWN_KEY)
		cub->keys.down = 1;
	if (keycode == LEFT_KEY)
		cub->keys.left = 1;
	if (keycode == RIGHT_KEY)
		cub->keys.right = 1;
	return (0);
}

int	key_hook(int keycode, t_cub *cub)
{
	double	edge;
	double	move_speed;
	double	rot_speed;

	edge = 1.1;
	move_speed = 0.6;
	rot_speed = 0.1;
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
	raycast(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img, 0, 0);
	return (0);
}
