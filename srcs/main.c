#include "cub.h"

void	move_forward(t_cub *cub, double edge, double move_speed)
{
	if (cub->map[(int)(cub->pos->y)][(int)(cub->pos->x + cub->dir->x * move_speed * edge)] != 1)
		cub->pos->x += cub->dir->x * move_speed;
	if (cub->map[(int)(cub->pos->y + cub->dir->y * move_speed * edge)] [(int)(cub->pos->x)] != 1)
		cub->pos->y += cub->dir->y * move_speed;
}

void	move_backward(t_cub *cub, double edge, double move_speed)
{
	if (cub->map[(int)(cub->pos->y)][(int)(cub->pos->x - cub->dir->x * move_speed * edge)] != 1)
		cub->pos->x -= cub->dir->x * move_speed;
	if (cub->map[(int)(cub->pos->y - cub->dir->y * move_speed * edge)][(int)(cub->pos->x)] != 1)
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
	if (cub->map[(int)(cub->pos->y)][(int)(cub->pos->x + cub->proj_plane->x * move_speed * edge)] != 1)
		cub->pos->x += cub->proj_plane->x * move_speed;
	if (cub->map[(int)(cub->pos->y + cub->proj_plane->y * move_speed * edge)][(int)(cub->pos->x)] != 1)
		cub->pos->y += cub->proj_plane->y * move_speed;
}

void	move_left(t_cub *cub, double edge, double move_speed)
{
	if (cub->map[(int)(cub->pos->y)][(int)(cub->pos->x - cub->proj_plane->x * move_speed * edge)] != 1)
		cub->pos->x -= cub->proj_plane->x * move_speed;
	if (cub->map[(int)(cub->pos->y - cub->proj_plane->y * move_speed * edge)][(int)(cub->pos->x)] != 1)
		cub->pos->y -= cub->proj_plane->y * move_speed;
}

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

char	*set_fps_string(char *str1, t_cub *cub, int mode)
{
	char	*new;

	if (mode == 0)
		str1 = ft_itoa((int)cub->curr_fps);
	else if (mode == 1)
		str1 = ft_itoa((int)cub->prev_fps);
	if (str1)
	{
		new =  ft_strjoin("FPS: ", str1);
		free(str1);
	}
	else
		return (NULL);
	return (new);
}

int	display_fps(t_cub *cub)
{
	char				*time_str;
	char				*prev_str;
	long double			frame_time;

	time_str = NULL;
	prev_str = NULL;
	cub->old_time = cub->time;
	cub->time = get_time_micros();
	frame_time = ((long double)(cub->time - cub->old_time)) / 1000000;
	cub->prev_fps = cub->curr_fps;
	cub->curr_fps = 1.0 / frame_time;
	if (fabs(cub->curr_fps - cub->prev_fps) > 1)
	{
		time_str = set_fps_string(time_str, cub, 0);
		prev_str = set_fps_string(prev_str, cub, 1);
		mlx_string_put(cub->mlx, cub->window, 25, 25, 0x00000000, prev_str);
		mlx_string_put(cub->mlx, cub->window, 25, 25, 0x00FFFFFF, time_str);
		free(time_str);
		free(prev_str);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;
	int		map_fd;

	if ((map_fd = check_args(ac, av)) == -1)
		return (1);
	cub = init_cub();
	init_mlx(&cub);
	validate_map(map_fd, av[1], &cub);
	print_cub(&cub);
	// free_cub(&cub); // just for now
	
	raycast_loop(&cub);
	mlx_put_image_to_window(cub.mlx, cub.window, cub.img, 0, 0);
	mlx_loop_hook(cub.mlx, display_fps, &cub);
	mlx_hook(cub.window, 2, 1L<<0, key_hook, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
