#include "cub.h"

void	init_keys(t_cub *cub)
{
	cub->keys.w = 0;
	cub->keys.a = 0;
	cub->keys.s = 0;
	cub->keys.d = 0;
	cub->keys.up = 0;
	cub->keys.down = 0;
	cub->keys.left = 0;
	cub->keys.right = 0;
}

void	init_mouse(t_cub *cub)
{
	cub->mouse.left = 0;
	cub->mouse.right = 0;
}