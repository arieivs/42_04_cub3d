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
	if (keycode == ESC_KEY)
		graceful_exit(cub);
	return (0);
}

/*
	UPDATE_DISPLAY:
	-	Inside of mlx_loop_hook, so happening when NO event happens
	-	Checks the key value in the relevant struct set by key_down and key_up
	-	If values in the struct are non-zero, apply movement to coords

	-	VAR: Edge detection = 1.1]
	-	VAR: Movement Speed = 0.05 squares/frame]
	-	VAR: Rotation Speed = 0.02 radians]

	-	Above values were set by experimentation. We can also change the
		static int frame value in the if statement

	-	Frametime: need to establish some values here that make the project
		run smoothly accross both Macs and Linux. Currently in milliseconds
*/
int	update_display(t_cub *cub)
{
	if (cub->keys.w || cub->keys.up)
		move_forward(cub, 1.1, MOVE_SPEED);
	else if (cub->keys.s || cub->keys.down)
		move_backward(cub, 1.1, MOVE_SPEED);
	if (cub->keys.left)
		rotate_left(cub, ROT_SPEED);
	else if (cub->keys.right)
		rotate_right(cub, ROT_SPEED);
	if (cub->keys.a)
		move_left(cub, 1.1, MOVE_SPEED);
	else if (cub->keys.d)
		move_right(cub, 1.1, MOVE_SPEED);
	if (cub->keys.w || cub->keys.a || cub->keys.s || cub->keys.d
		|| cub->keys.up || cub->keys.down || cub->keys.left
		|| cub->keys.right)
		raycast(cub);
	return (0);
}
