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

int	mouse_hook(int x, int y, t_cub *cub)
{
	(void)y;
	if (x > MS_L_RANGE * WIDTH && x < MS_R_RANGE * WIDTH)
	{
		cub->mouse.left = 0;
		cub->mouse.right = 0;
	}
	else if (x < MS_L_RANGE * WIDTH)
	{
		cub->mouse.left = fabs(MS_L_RANGE * WIDTH - x);
		cub->mouse.right = 0;
	}
	else if (x > MS_R_RANGE * WIDTH)
	{
		cub->mouse.left = 0;
		cub->mouse.right = fabs(MS_R_RANGE * WIDTH - x);
	}
	return (0);
}