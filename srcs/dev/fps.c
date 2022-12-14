/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:15:39 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:15:41 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	put_fps_string(double fps, t_cub *cub)
{
	char	*str1;
	char	*str2;

	str1 = ft_itoa((int)fps);
	if (!str1)
		return ;
	str2 = ft_strjoin("FPS: ", str1);
	free(str1);
	mlx_string_put(cub->mlx, cub->window, 25, 25, 0x00FFF000, str2);
	free(str2);
}

void	display_fps(t_cub *cub)
{
	unsigned long long			time;
	static unsigned long long	old_time = 0;
	double						curr_fps;
	static double				prev_fps = 0.0;
	long double					frame_time;

	time = get_time_micros();
	frame_time = ((long double)(time - old_time)) / 1000000;
	curr_fps = 1.0 / frame_time;
	if (fabs(curr_fps - prev_fps) > 1)
	{
		put_fps_string(curr_fps, cub);
		put_fps_string(prev_fps, cub);
	}
	old_time = time;
	prev_fps = curr_fps;
}

unsigned long long	get_time_micros(void)
{
	struct timeval		tv;
	unsigned long long	curtime;

	gettimeofday(&tv, NULL);
	curtime = (unsigned long long)((tv.tv_sec * 1000000 + tv.tv_usec));
	return (curtime);
}
