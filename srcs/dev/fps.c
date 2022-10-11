#include "cub.h"

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

char	*set_fps_string(char *str1, t_cub *cub, int mode)
{
	char	*new;

	if (mode == 0)
		str1 = ft_itoa((int)cub->curr_fps);
	else if (mode == 1)
		str1 = ft_itoa((int)cub->prev_fps);
	if (str1)
	{
		new = ft_strjoin("FPS: ", str1);
		free(str1);
	}
	else
		return (NULL);
	return (new);
}

unsigned long long	get_time_micros(void)
{
	struct timeval		tv;
	unsigned long long	curtime;

	gettimeofday(&tv, NULL);
	curtime = (unsigned long long)((tv.tv_sec * 1000000 + tv.tv_usec));
	return (curtime);
}