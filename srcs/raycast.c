#include "cub.h"

void	initialize_map_pos(t_cub *cub)
{
// 	// Set variables
// 	cub->pos->x = 12.0;
// 	cub->pos->y = 12.0;

// 	cub->dir->x = -0.5;
// 	cub->dir->y = 0.0;

// 	cub->proj_plane->x = 0;
// 	cub->proj_plane->y = 0.66;

	// timers for FPS calculation
	cub->time = 0;
	cub->old_time = 0;
}

/*
	SET_RAY_DIR:
	- Add to the direction vector, the projection plane vector and multiply it by the x-coordinate in camera space
	- Vectors have both an x and y component, so do this for both dimensions
*/

void	set_ray_dir(t_cub *cub)
{
	cub->ray_dir = (t_pair_d *)malloc(1 * sizeof(t_pair_d));
	if (cub->ray_dir == NULL)
		error_and_exit(ERRNO, cub);
	cub->ray_dir->x = cub->dir->x + cub->proj_plane->x * cub->camera_x;
	cub->ray_dir->y = cub->dir->y + cub->proj_plane->y * cub->camera_x;
}

/*
	SET_DELTA_DIST
	- Calculates the distance to the next gridline
	- If the ray is paralel to an axis, this distance is equal to 1e30.
*/
void	set_delta_dist(t_cub *cub)
{
	cub->delta_dist = (t_pair_d *)malloc(1 * sizeof(t_pair_d));
	if (cub->delta_dist == NULL)
		error_and_exit(ERRNO, cub);
	if (cub->ray_dir->x == 0)
		cub->delta_dist->x = 1e30;
	else
		cub->delta_dist->x = fabs(1.0 / cub->ray_dir->x);
	if (cub->ray_dir->y == 0)
		cub->delta_dist->y = 1e30;
	else
		cub->delta_dist->y = fabs(1.0 / cub->ray_dir->y);
}

/*
	INITIALIZE RAYCASTING
	- In this function we set the variables needed to perform the distance calculation to the walls
		- camera_x: 		Sets the x-coordinate in camera space (ranging from -1 to 1 over the screen's width)
		- ray_dir->x|y: 	The coordinates of the ray direction vector
		- map_pos->x|y: 	Integer value of the map pos to indicate in which square we are currently
		- side_dist->x|y: 	From the current position, this is the distance to the first gridline in x and y direction
		- delta_dist->x|y: 	The distance to cross a grid square in both x and y direction for the ray
		- step->x|y: 		The direction to step in x or y direction
		- hit: 				This variable checks later on whether or not the ray is hitting a wall or not
*/
void	initialize_raycasting(t_cub *cub, int x)
{
	// Camera Position
	cub->camera_x = (((double)(2 * x)) / (double)(WIDTH)) - 1;

	// Ray Direction
	set_ray_dir(cub);

	// Position in map grid (int)
	cub->map_pos = (t_pair_i *)malloc(1 * sizeof(t_pair_i));
	if (cub->map_pos == NULL)
		error_and_exit(ERRNO, cub);
	cub->map_pos->x = (int)(cub->pos->x);
	cub->map_pos->y = (int)(cub->pos->y);

	// Position to the nearest side
	cub->side_dist = (t_pair_d *)malloc(1 * sizeof(t_pair_d));
	if (cub->side_dist == NULL)
		error_and_exit(ERRNO, cub);

	// Distance between X-pos or Y-pos
	set_delta_dist(cub);

	// initialize the step pair
	cub->step = (t_pair_i *)malloc(1 * sizeof(t_pair_i));
	if (cub->step == NULL)
		error_and_exit(ERRNO, cub);

	// set hit
	cub->hit = 0;
}

void	free_raycasting_vars(t_cub *cub)
{
	free(cub->ray_dir);
	free(cub->map_pos);
	free(cub->side_dist);
	free(cub->delta_dist);
}

void	calculate_step(t_cub *cub)
{
	// for x-pos
	if (cub->ray_dir->x < 0)
	{
		cub->step->x = -1;
		cub->side_dist->x = (cub->pos->x - (double)(cub->map_pos->x)) * cub->delta_dist->x;
	}
	else
	{
		cub->step->x = 1;
		cub->side_dist->x = ((double)(cub->map_pos->x) + 1.0 - cub->pos->x) * cub->delta_dist->x;
	}
	// for y-pos
	if (cub->ray_dir->y < 0)
	{
		cub->step->y = -1;
		cub->side_dist->y = (cub->pos->y - (double)cub->map_pos->y) * cub->delta_dist->y;
	}
	else
	{
		cub->step->y = 1;
		cub->side_dist->y = ((double)cub->map_pos->y + 1.0 - cub->pos->y) * cub->delta_dist->y;
	}
}

void	perform_dda(t_cub *cub)
{
	while (cub->hit == 0)
	{
		// jump to the next map square either in x or y direction
		if (cub->side_dist->x < cub->side_dist->y)
		{
			cub->side_dist->x += cub->delta_dist->x;
			cub->map_pos->x += cub->step->x;
			cub->side = 0;
		}
		else
		{
			cub->side_dist->y += cub->delta_dist->y;
			cub->map_pos->y += cub->step->y;
			cub->side = 1;
		}
		// printf("map pos x is %d\n", cub->map_pos->x);
		// printf("map pos y is %d\n", cub->map_pos->y);
		if (cub->map[cub->map_pos->y][cub->map_pos->x] == 1)
		{
			// printf("test\n");
			cub->hit = 1;
			// printf("haha\n");
		}
	}
}

void	calculate_dist(t_cub *cub)
{
	if (cub->side == 0)
		cub->perp_wall_dist = cub->side_dist->x - cub->delta_dist->x;
	else
		cub->perp_wall_dist = cub->side_dist->y - cub->delta_dist->y;
}

void	raycast_loop(t_cub *cub)
{
	int				x;
	unsigned int	color;

	x = 0;
	initialize_map_pos(cub);
	while (x < WIDTH)
	{
		initialize_raycasting(cub, x);
		calculate_step(cub);
		perform_dda(cub);
		calculate_dist(cub);
		color = draw_pixels(cub);
		ver_line(cub, x, color);
		// free_raycasting_vars(cub);
		x++;
	}
}
