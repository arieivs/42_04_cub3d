#include "cub.h"

int g_worldMap[mapWidth][mapHeight] = 
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	move_forward(t_cub *cub, double edge, double move_speed)
{
	if (g_worldMap[(int)(cub->pos->x + cub->dir->x * move_speed * edge)][(int)(cub->pos->y)] == 0)
		cub->pos->x += cub->dir->x * move_speed;
	if (g_worldMap[(int)(cub->pos->x)][(int)(cub->pos->y + cub->dir->y * move_speed * edge)] == 0)
		cub->pos->y += cub->dir->y * move_speed;
}

void	move_backward(t_cub *cub, double edge, double move_speed)
{
	if (g_worldMap[(int)(cub->pos->x - cub->dir->x * move_speed * edge)][(int)(cub->pos->y)] == 0)
		cub->pos->x -= cub->dir->x * move_speed;
	if (g_worldMap[(int)(cub->pos->x)][(int)(cub->pos->y - cub->dir->y * move_speed * edge)] == 0)
		cub->pos->y -= cub->dir->y * move_speed;
}

void	rotate_left(t_cub *cub, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->dir->x;
	cub->dir->x = cub->dir->x * cos(rot_speed) - cub->dir->y * sin(rot_speed);
	cub->dir->y = old_dir_x * sin(rot_speed) + cub->dir->y * cos(rot_speed);
	old_plane_x = cub->proj_plane->x;
	cub->proj_plane->x = cub->proj_plane->x * cos(rot_speed) - cub->proj_plane->y * sin(rot_speed);
	cub->proj_plane->y = old_plane_x * sin(rot_speed) + cub->proj_plane->y * cos(rot_speed); 
}

void	rotate_right(t_cub *cub, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->dir->x;
	cub->dir->x = cub->dir->x * cos(-rot_speed) - cub->dir->y * sin(-rot_speed);
	cub->dir->y = old_dir_x * sin(-rot_speed) + cub->dir->y * cos(-rot_speed);
	old_plane_x = cub->proj_plane->x;
	cub->proj_plane->x = cub->proj_plane->x * cos(-rot_speed) - cub->proj_plane->y * sin(-rot_speed);
	cub->proj_plane->y = old_plane_x * sin(-rot_speed) + cub->proj_plane->y * cos(-rot_speed); 
}

void	move_right(t_cub *cub, double edge, double move_speed)
{
	if (g_worldMap[(int)(cub->pos->x + cub->proj_plane->x * move_speed * edge)][(int)(cub->pos->y)] == 0)
		cub->pos->x += cub->proj_plane->x * move_speed;
	if (g_worldMap[(int)(cub->pos->x)][(int)(cub->pos->y + cub->proj_plane->y * move_speed * edge)] == 0)
		cub->pos->y += cub->proj_plane->y * move_speed;
}

void	move_left(t_cub *cub, double edge, double move_speed)
{
	if (g_worldMap[(int)(cub->pos->x - cub->proj_plane->x * move_speed * edge)][(int)(cub->pos->y)] == 0)
		cub->pos->x -= cub->proj_plane->x * move_speed;
	if (g_worldMap[(int)(cub->pos->x)][(int)(cub->pos->y - cub->proj_plane->y * move_speed * edge)] == 0)
		cub->pos->y -= cub->proj_plane->y * move_speed;
}

int	key_hook(int keycode, t_cub *cub)
{
	double	edge;
	double	move_speed;
	double	rot_speed;

	edge = 1.1;
	move_speed = 0.5;
	rot_speed = 0.05;

	printf("hello from keycode %d\n", keycode);

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

// int	close(int keycode, t_cub *cub)
// {
// 	mlx_destroy_window(cub->mlx, )
// }

int	main(int ac, char **av)
{
	t_cub	cub;
	int		map_fd;

	// if ((map_fd = check_args(ac, av)) == -1)
	// 	return (1);
	cub = init_cub();
	// if (!check_map(map_fd, &cub))
	// {
	// 	free_cub(&cub); // to think
	// 	return (1);
	// }
	init_mlx(&cub);

	// SEPARATE
	(void)ac;
	(void)av;
	(void)map_fd;
	initialize_map_pos(&cub);
	raycast_loop(&cub);
	mlx_put_image_to_window(cub.mlx, cub.window, cub.img, 0, 0);
	mlx_hook(cub.window, 2, 1L<<0, key_hook, &cub);
	mlx_loop(cub.mlx);
	return (0);
}