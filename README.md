# Lode's Computer Graphics Tutorial
Source : https://lodev.org/cgtutor/raycasting.html

## Intro
Raycasting is a rendering technique to create a 3D perspective in a 2D map. Only a calculation has to be done for every vertical line of the screen.

## Raycasting Basics
The basic idea is that the map is a 2d grid, with each square being either 0 or 1 (wall or no wall).

## Vectors Recap
Vectors are abstract notions but always have 2 essential components:
1. A direction in space
2. A magnitude or length

Vector in 2D euclidian space:

`v = 
[ vx 
  vy ]`

In computer graphics we can easily represent the above as a 2-element array of floating point numbers or a struct containing 2 floats. In 2D, we can say the direction of the vector is equal to `m = vy / vx`. This expresses the change in vertical position per unit of horizontal position x.

Vector magnitude (also called the norm) is represented by the formula `sqrt(vx^2 + vy^2)`


## Basics of working with MINILIBX
MiniLibx is a tiny graphics library written for UNIX. It allows us to render pixels to a window. We will not discuss set-up here as it is well explained at [42 Docs](https://harm-smits.github.io/42docs/libs/minilibx/introduction.html). However we would like to add some clarification to this guide on how to use MiniLibx.

### Displaying a pixel on the screen
Rather than work with written text, I'll write most of my comments inside of the code, which I find easier to read and digest.
```
#include <mlx.h> // Necessary header defined inside of the minilibx-linux folder

// Struct inw which we define several important data items:
typedef struct	s_data {
	void	*img;			// pointer to the image which we will layer on top of the screen
	char	*addr;			// returns info about the image, allowing us to modify it later.
	int		bits_per_pixel;	// will be set by MiniLibx
	int		line_length;	// will be set by MiniLibx
	int		endian;			// will be set by MiniLibx
}				t_data;

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init(); // Establishes the connection to the graphical system and stores it
	mlx_win = mlx_new_window(mlx, 640, 480, "Readme") // Provide dimensions for the screen and a name

	img.img = mlx_new_image(mlx, 640, 480) // creates a new image in memory. We can draw inside of this image
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	// Let's now try and put some pixels down in a loop using our pixel_put function
	for (int i = 0; i < 10; i++)
		my_mlx_pixel_put(&img, 5 + i, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
```
