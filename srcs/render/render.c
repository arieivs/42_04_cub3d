#include "cub.h"

void	render(t_cub *cub)
{
	raycast(cub);
	draw_navigator(cub);
}

/*
	UPDATE_DISPLAY:
	-	Inside of mlx_loop_hook, so happening when NO event happens
	-	Checks the key value in the relevant struct set by key_down, key_up and
		mouse_hook
	-	If values in the struct are non-zero, apply movement to coords

	-	VAR: Edge detection = checks if map exists 10% beyond next square (1.1)
	-	VAR: Movement Speed = squares/frame (MOVE_SPEED macro)
	-	VAR: Rotation Speed = radians/frame (ROT_SPEED macro)

	-	Above values were set by experimentation for both MacOS and Linux.
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
	if (cub->mouse.left)
		rotate_left(cub, ROT_SPEED * cub->mouse.left / WIDTH);
	else if (cub->mouse.right)
		rotate_right(cub, ROT_SPEED * cub->mouse.right / WIDTH);
	if (cub->keys.a)
		move_left(cub, 1.1, MOVE_SPEED);
	else if (cub->keys.d)
		move_right(cub, 1.1, MOVE_SPEED);
	if (cub->keys.w || cub->keys.a || cub->keys.s || cub->keys.d
		|| cub->keys.up || cub->keys.down || cub->keys.left
		|| cub->keys.right || cub->mouse.left || cub->mouse.right)
		render(cub);
	return (0);
}
