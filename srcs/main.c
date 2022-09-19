#include "mlx.h"
#include "cub3d.h"

int worldMap[mapWidth][mapHeight] = 
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

// typedef struct	s_vars {
// 	void	*mlx;
// 	void	*win;
// }				t_vars;

// // Global vars
// t_vars	vars;

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

int	key_hook(int keycode, t_cub *cub)
{
	(void)keycode;
	(void)cub;
	printf("Hello from key_hook!\n");
	return (0);
}

void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->addr + (y * cub->line_length + x * (cub->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	verLine(t_cub *cub, int x, unsigned int color)
{
	// x			= coordinate of the vertical line
	// drawStart	= where we need to start drawing the texture color
	// drawEnd		= where we need to end drawing the texture color
	// color		= 32-bit trgb color value

	//printf("DrawStart is %d and DrawEnd is %d\n", drawStart, drawEnd);
	//printf("%d - %d\n", drawStart, drawEnd);
	for (int i = 0; i < screenHeight; i++)
	{
		if (i >= cub->draw_start && i <= cub->draw_end)
		{
			my_mlx_pixel_put(cub, x, i, color);
		}
		else
		{
			my_mlx_pixel_put(cub, x, i, 0x00000000);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img, 0, 0);
}

void	initialize_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (cub->mlx == NULL)
		exit (-2); // To be cleaned up
	cub->window = mlx_new_window(cub->mlx, screenWidth, screenHeight, "cub3d");
	cub->img = mlx_new_image(cub->mlx, screenWidth, screenHeight);
	cub->addr = mlx_get_data_addr(cub->img, &(cub->bits_per_pixel), &(cub->line_length), &(cub->endian));
	return ;
}

void	initialize_map_pos(t_cub *cub)
{
	// Allocate memory (DONT FORGET TO DELETE)
	cub->pos = (t_pair_d *)malloc(1 * sizeof(t_pair_d));
	if (cub->pos == NULL)
		exit(-3); // Error management
	cub->dir = (t_pair_d *)malloc(1 * sizeof(t_pair_d));
	if (cub->pos == NULL)
		exit(-3); // Error management
	cub->proj_plane = (t_pair_d *)malloc(1 * sizeof(t_pair_d));
	if (cub->pos == NULL)
		exit(-3); // Error management
	
	// Set variables
	cub->pos->x = 22.0;
	cub->pos->y = 12.0;

	cub->dir->x = -1.0;
	cub->dir->y = 0.0;

	cub->proj_plane->x = 0;
	cub->proj_plane->y = 0.66;

	// Option: add curr time and prev time frames here
	// double time = 0;
	// double old_time = 0;
}

void	initialize_raycasting(t_cub *cub, int x)
{
	// Camera Position
	cub->camera_x = (((double)(2 * x)) / (double)(screenWidth)) - 1;

	// Ray Direction
	cub->ray_dir = (t_pair_d *)malloc(1 * sizeof(t_pair_d));
	if (cub->ray_dir == NULL)
		exit (-3); // some error
	cub->ray_dir->x = cub->dir->x + cub->proj_plane->x * cub->camera_x;
	cub->ray_dir->y = cub->dir->y + cub->proj_plane->y * cub->camera_x;

	// Position in map grid (int)
	cub->map_pos = (t_pair_i *)malloc(1 * sizeof(t_pair_i));
	if (cub->map_pos == NULL)
		exit (-3); // some error
	cub->map_pos->x = (int)(cub->pos->x);
	cub->map_pos->y = (int)(cub->pos->y);

	// Position to the nearest side
	cub->side_dist = (t_pair_d *)malloc(1 * sizeof(t_pair_d));
	if (cub->side_dist == NULL)
		exit (-3); // some error

	// Distance between X-pos or Y-pos	
	cub->delta_dist = (t_pair_d *)malloc(1 * sizeof(t_pair_d));
	if (cub->delta_dist == NULL)
		exit(-3); // some error
	
	if (cub->ray_dir->x == 0)
		cub->delta_dist->x = 1e30;
	else
		cub->delta_dist->x = fabs(1.0 / cub->ray_dir->x);

	if (cub->ray_dir->y == 0)
		cub->delta_dist->y = 1e30;
	else
		cub->delta_dist->y = fabs(1.0 / cub->ray_dir->y);

	// initialize the step pair
	cub->step = (t_pair_d *)malloc(1 * sizeof(t_pair_d));
	if (cub->step == NULL)
		exit (-3); // some error

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
		if (worldMap[cub->map_pos->x][cub->map_pos->y] > 0)
			cub->hit = 1;
	}
}

void	calculate_dist(t_cub *cub)
{
	// printf("check: %lf\n", cub->delta_dist->x);
	if (cub->side == 0)
		cub->perp_wall_dist = cub->side_dist->x - cub->delta_dist->x;
	else
		cub->perp_wall_dist = cub->side_dist->y - cub->delta_dist->y;
}

int	set_pixel_color(t_cub *cub)
{
	unsigned int	color;

	if (worldMap[cub->map_pos->x][cub->map_pos->y] == 1)
		color = 0x00FF0000; // red
	else if (worldMap[cub->map_pos->x][cub->map_pos->y] == 2)
		color = 0x0000FF00; // green
	else if (worldMap[cub->map_pos->x][cub->map_pos->y] == 3)
		color = 0x000000FF; // blue
	else if (worldMap[cub->map_pos->x][cub->map_pos->y] == 4)
		color = 0x00FFFF00;	// yellow
	else
		color = 0x00FFFFFF; // white
	return (color);
}

unsigned int	draw_pixels(t_cub *cub)
{
	unsigned int	color;

	cub->line_height = (int)(((double)screenHeight) / cub->perp_wall_dist);
	cub->draw_start = -cub->line_height / 2 + screenHeight / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = cub->line_height / 2 + screenHeight / 2;
	if (cub->draw_end >= screenHeight)
		cub->draw_end = screenHeight - 1;
	color = set_pixel_color(cub);
	if (cub->side == 1)
		color = color / 1.25;
	return (color);
}

void	raycast_loop(t_cub *cub)
{
	int				x;
	unsigned int	color;

	x = 0;
	while (x < screenWidth)
	{
		initialize_raycasting(cub, x);
		calculate_step(cub);
		perform_dda(cub);
		calculate_dist(cub);
		color = draw_pixels(cub);
		verLine(cub, x, color);
		free_raycasting_vars(cub);
		x++;
	}
}

// int	close(int keycode, t_cub *cub)
// {
// 	mlx_destroy_window(cub->mlx, )
// }

int main(void)
{
	t_cub	cub;
	int		i;

	initialize_mlx(&cub);
	initialize_map_pos(&cub);
	raycast_loop(&cub);
	mlx_key_hook(cub.window, key_hook, &cub);
	mlx_loop(cub.mlx);
}