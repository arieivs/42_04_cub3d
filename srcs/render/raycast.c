/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:16:20 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:16:21 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
	INITIALIZE RAYCASTING
	- In this function we set the variables needed to perform
	the distance calculation to the walls
		- camera_x: 		Sets the x-coord in camera space 
							(ranging from -1 to 1 over the screen's width)
		- ray_dir->x|y: 	The coord of the ray direction vector
		- map_pos->x|y: 	Integer value of the map pos to indicate in
							which square we are currently
		- side_dist->x|y: 	From the current position, this is the distance
							to the first gridline in x and y direction
		- delta_dist->x|y: 	The distance to cross a grid square in both x 
							and y direction for the ray
		- step->x|y: 		The direction to step in x or y direction
		- hit: 				This variable checks later on whether or not 
							the ray is hitting a wall or not
*/
void	initialize_raycasting(t_cub *cub, int x)
{
	cub->camera_x = (((double)(2 * x)) / (double)(WIDTH)) - 1;
	cub->ray_dir->x = cub->dir->x + cub->proj_plane->x * cub->camera_x;
	cub->ray_dir->y = cub->dir->y + cub->proj_plane->y * cub->camera_x;
	cub->map_pos->x = (int)(cub->pos->x);
	cub->map_pos->y = (int)(cub->pos->y);
	if (cub->ray_dir->x == 0)
		cub->delta_dist->x = 1e30;
	else
		cub->delta_dist->x = fabs(1.0 / cub->ray_dir->x);
	if (cub->ray_dir->y == 0)
		cub->delta_dist->y = 1e30;
	else
		cub->delta_dist->y = fabs(1.0 / cub->ray_dir->y);
	cub->hit = 0;
}

/*
	CALCULATE_STEP

	-	This function calculates for a given position, what the distance
		is to the next gridsquare
	-	This distance to the first grid square (side_dist) is basically
		a proportion of the distance to cross a full square (delta_dist).
*/
void	calculate_step(t_cub *cub)
{
	if (cub->ray_dir->x < 0)
	{
		cub->step->x = -1;
		cub->side_dist->x = (cub->pos->x
				- (double)(cub->map_pos->x)) * cub->delta_dist->x;
	}
	else
	{
		cub->step->x = 1;
		cub->side_dist->x = ((double)(cub->map_pos->x)
				+ 1.0 - cub->pos->x) * cub->delta_dist->x;
	}
	if (cub->ray_dir->y < 0)
	{
		cub->step->y = -1;
		cub->side_dist->y = (cub->pos->y
				- (double)cub->map_pos->y) * cub->delta_dist->y;
	}
	else
	{
		cub->step->y = 1;
		cub->side_dist->y = ((double)cub->map_pos->y
				+ 1.0 - cub->pos->y) * cub->delta_dist->y;
	}
}

/*
	PERFORM_DDA:
	-	DDA = Digital Differential Analysis
	-	A fast algorithm used to find when a ray hits the square grids of the map
	-	From the current position, it adds to the side_dist the delta_dist
	-	We keep repeating this until we hit a gridsquare with value 1.
*/
void	perform_dda(t_cub *cub)
{
	while (cub->hit == 0)
	{
		if (cub->side_dist->x < cub->side_dist->y)
		{
			cub->side_dist->x += cub->delta_dist->x;
			cub->map_pos->x += cub->step->x;
			cub->side = SIDE_X;
		}
		else
		{
			cub->side_dist->y += cub->delta_dist->y;
			cub->map_pos->y += cub->step->y;
			cub->side = SIDE_Y;
		}
		if (cub->map[cub->map_pos->y][cub->map_pos->x] == 1)
			cub->hit = 1;
	}
	if (cub->side == SIDE_X)
		cub->perp_wall_dist = cub->side_dist->x - cub->delta_dist->x;
	else
		cub->perp_wall_dist = cub->side_dist->y - cub->delta_dist->y;
}

void	calculate_drawline(t_cub *cub)
{
	cub->line_height = (int)(((double)HEIGHT) / cub->perp_wall_dist);
	cub->draw_start = (-cub->line_height + HEIGHT) / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = (cub->line_height + HEIGHT) / 2;
	if (cub->draw_end >= HEIGHT)
		cub->draw_end = HEIGHT - 1;
}

void	raycast(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		initialize_raycasting(cub, x);
		calculate_step(cub);
		perform_dda(cub);
		calculate_drawline(cub);
		apply_textures(cub, x);
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img->img_ptr, 0, 0);
}
