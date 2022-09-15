# Cub3D
Create a simple videogame using Raycasting 🎮​

<br/>

## ⚙️​ Setup - Minilibx
For reference, here's [hsmit's guide](https://harm-smits.github.io/42docs/libs/minilibx) and [gontjarow's guide](https://gontjarow.github.io/MiniLibX/) to minilibx.

On your Makefile, check in which OS your programme is being compiled by doing
```
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
	# we're in a Mac
ifeq ($(UNAME), Linux)
	# we're using Linux
endif
```

### 🐧​ Linux
```
git clone https://github.com/42Paris/minilibx-linux.git
```
On your Makefile, after compiling minilibx, compile your project with the static library ```libmlx.a``` and the additional grapfical libraries ```-lXext -lX11 -lm -lz```.

### 🍏​ Apple
Download the minilibx_mms provided on intra.
On your Makefile, after compiling minilibx, copy the dynamic library ```libmlx.dylib``` to your root repository, to facilitate its usage.

<br/>

## Raycasting
[Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)

### Intro
Raycasting is a rendering technique to create a 3D perspective in a 2D map. Only a calculation has to be done for every vertical line of the screen.

### Raycasting Basics
The basic idea is that the map is a 2d grid, with each square being either 0 or 1 (wall or no wall).

### Vectors Recap
Vectors are abstract notions but always have 2 essential components:
1. A direction in space
2. A magnitude or length

Vector in 2D euclidian space:

`v = 
[ vx
  vy ]`

In computer graphics we can easily represent the above as a 2-element array of floating point numbers or a struct containing 2 floats. In 2D, we can say the direction of the vector is equal to `m = vy / vx`. This expresses the change in vertical position per unit of horizontal position x.

Vector magnitude (also called the norm) is represented by the formula `sqrt(vx^2 + vy^2)`

<br/>

## Resources Dump - to be organised
* If you are doing your project on Linux and you want to hook an event to close the window on the ❌ you have to do it as: ```mlx_hook(mlx->win, 33, 0, destroy_window, mlx);```
* [Parsing/Invalid maps tester](https://github.com/mlaraki/cub3D_leaks_maps_tester)
* [another map tester](https://github.com/humblEgo/cub3D_map_tester)
* [gleal's readme](https://github.com/gleal42/cub3d)
* [another raycasting tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
* [the start of a series of videos](https://platform.thinkific.com/videoproxy/v1/play/bt4rgv7eplmd9ibbfds0?time=370&autoplay=true&crosstime=738)
* [video tutorial](https://www.youtube.com/watch?v=gYRrGTC7GtA)

<br/>

## 🍻​ De Trappistinhos
This project is being done by [Hevhove](https://github.com/Hevhove) and [arieivs](https://github.com/arieivs)

<br/>

Happy raycasting! ​🎨​
