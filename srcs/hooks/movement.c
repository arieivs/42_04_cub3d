/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:15:47 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:15:48 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_forward(t_cub *cub, double edge, double ms)
{
	if (cub->map[(int)(cub->pos->y)][(int)(cub->pos->x + cub->dir->x
		* ms * edge)] != 1)
		cub->pos->x += cub->dir->x * ms;
	if (cub->map[(int)(cub->pos->y + cub->dir->y * ms
			* edge)][(int)(cub->pos->x)] != 1)
		cub->pos->y += cub->dir->y * ms;
}

void	move_backward(t_cub *cub, double edge, double ms)
{
	if (cub->map[(int)(cub->pos->y)][(int)(cub->pos->x - cub->dir->x
		* ms * edge)] != 1)
		cub->pos->x -= cub->dir->x * ms;
	if (cub->map[(int)(cub->pos->y - cub->dir->y
			* ms * edge)][(int)(cub->pos->x)] != 1)
		cub->pos->y -= cub->dir->y * ms;
}

void	move_right(t_cub *cub, double edge, double ms)
{
	if (cub->map[(int)(cub->pos->y)][(int)(cub->pos->x + cub->proj_plane->x
		* ms * edge)] != 1)
		cub->pos->x += cub->proj_plane->x * ms;
	if (cub->map[(int)(cub->pos->y + cub->proj_plane->y
			* ms * edge)][(int)(cub->pos->x)] != 1)
		cub->pos->y += cub->proj_plane->y * ms;
}

void	move_left(t_cub *cub, double edge, double ms)
{
	if (cub->map[(int)(cub->pos->y)][(int)(cub->pos->x - cub->proj_plane->x
		* ms * edge)] != 1)
		cub->pos->x -= cub->proj_plane->x * ms;
	if (cub->map[(int)(cub->pos->y - cub->proj_plane->y
			* ms * edge)][(int)(cub->pos->x)] != 1)
		cub->pos->y -= cub->proj_plane->y * ms;
}
