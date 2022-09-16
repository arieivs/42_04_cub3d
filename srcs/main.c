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

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

// Global vars
t_vars	vars;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	key_hook(int keycode, t_vars *vars)
{
	(void)keycode;
	(void)vars;
	printf("Hello from key_hook!\n");
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

verLine(int x, int drawStart, int drawEnd, int color)
{
	// x			= coordinate of the vertical line
	// drawStart	= where we need to start drawing the texture color
	// drawEnd		= where we need to end drawing the texture color
	// color		= 32-bit trgb color value

	t_data img;
	img.img = mlx_new_image(vars.mlx, 1, screenHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	printf("DrawStart is %d and DrawEnd is %d\n", drawStart, drawEnd);
	for (int i = 0; i < screenHeight; i++)
	{
		if (i > drawStart && i < drawEnd)
		{
			my_mlx_pixel_put(&img, i, x, color);
		}
		else
		{
			my_mlx_pixel_put(&img, i, x, 0xFF000FFF);
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, x, 0);
}

// MAIN
int	main(void)
{
	// Mlx Launch and stuff...
	
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		exit (-2);
	vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "Cub3d");

	// Tutorial below...color

	double	posX = 22;		// Starting Positions
	double	posY = 12;

	double	dirX = -1;		// Direction Vector
	double	dirY = 0;

	double planeX = 0;		// Camera Plane
	double planeY = 0.66; 

	double time = 0;		// time of current and previous frame
	double old_time = 0;

	for (int x = 0; x < screenWidth; x++)
	{
		// calculate ray position and direction
		double cameraX = (((double)(2 * x)) / (double)(screenWidth)) - 1;
		// printf("cameraX is %lf | ", cameraX);
		double rayDirX = dirX + planeX * cameraX;
		// printf("RayX is %lf | ", rayDirX);
		double rayDirY = dirY + planeY * cameraX;
		// printf("RayY is %lf | \n", rayDirY);

		// Digital Differential Analysis var setup
		// Map box we are in
		int mapX = (int)posX;
		int mapY = (int)posY;

		// lenght of ray from current position to next x or y side
		double sideDistX;
		double sideDistY;

		// lengt After the DDA is done, we have to calculate the distance of the ray to the wall, so that we can calculate how high the wall has to be drawn after this. h of ray from one x or y side to next x or y side
		double deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);
		double perpWallDist; // used to avoid fisheye effect

		// what direction to step in x or y direction (either +1 or -1)
		int stepX;
		int	stepY;

		int hit = 0; 	// was there a wall hit?
		int side;		// was a NS or a EW wall hit

		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - (double)mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = ((double)mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - (double)mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = ((double)mapY + 1.0 - posY) * deltaDistY;
		}

		// Perform DDA
		while (hit == 0)
		{
			// jump to the next map square either in x or y direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) {hit = 1;}
		}

		// Calculate distance projected on camera direction
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		
		// Calculate height of line to draw on screen
		int lineHeight = (int)(((double)screenHeight) / perpWallDist);

		// Calculate lowest and highest pixel to fill in current stripe
		int	drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		
		// choose wall color
		unsigned int color;
		switch (worldMap[mapX][mapY])
		{
			case 1:
				color = 0xFFFF0000; // red
				break ;
			case 2:
				color = 0xFF00FF00; // green
				break ;
			case 3:
				color = 0xFF0000FF; // blue
				break ;
			case 4:
				color = 0xFFFFFFFF; // white
				break ;
			default:
				color = 0xFFFFFF00;	// yellow
		}
		// give x and y sides different brightness
		// if (side == 1)
		// 	color = color / 2;

		verLine(x, drawStart, drawEnd, color);
		//printf("x is now: %d\n", x);
	}
	// t_data img;
	// img.img = mlx_new_image(vars.mlx, 1, screenHeight);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// unsigned int color = 0xFFFFFFFF;
	// my_mlx_pixel_put(&img, 0, 0, color);
	// my_mlx_pixel_put(&img, 1, 0, color);
	// my_mlx_pixel_put(&img, 2, 0, color);
	// my_mlx_pixel_put(&img, 3, 0, color);
	// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	// MLX set-up
	
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
}