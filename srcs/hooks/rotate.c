/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:15:51 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:15:52 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	rotate(t_cub *cub, double rs)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->dir->x;
	cub->dir->x = cub->dir->x * cos(rs) - cub->dir->y * sin(rs);
	cub->dir->y = old_dir_x * sin(rs) + cub->dir->y * cos(rs);
	old_plane_x = cub->proj_plane->x;
	cub->proj_plane->x = cub->proj_plane->x
		* cos(rs) - cub->proj_plane->y * sin(rs);
	cub->proj_plane->y = old_plane_x * sin(rs)
		+ cub->proj_plane->y * cos(rs);
}

void	rotate_left(t_cub *cub, double rs)
{
	rotate(cub, -rs);
}

void	rotate_right(t_cub *cub, double rs)
{
	rotate(cub, rs);
}
