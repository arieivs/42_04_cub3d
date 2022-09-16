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