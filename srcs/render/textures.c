/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:16:34 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:36:10 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
	GET_WALL_DIR:
	-	Calculates which side of a wall is facing us. 
	-	If the wall's y-coordinate is lower than ours,
		we see the south side of the wall (SO)
	-	If the wall's y-coordinate is higher than ours,
		we see the north side of the wall (NO)
	-	If the wall's x-coordinate is lower than ours,
		we see the east side of the wall (EA)
	-	Else, we see the west-side (WE)
*/
t_dir_code	get_wall_dir(t_cub *cub)
{
	if (cub->side == SIDE_Y && cub->map_pos->y < cub->pos->y)
		return (SO);
	if (cub->side == SIDE_Y && cub->map_pos->y > cub->pos->y)
		return (NO);
	if (cub->side == SIDE_X && cub->map_pos->x < cub->pos->x)
		return (EA);
	return (WE);
}

/*
	CALCULATEXWALL_X
	-	wall_x is where exactly the ray hits the texture
		in its x-coordinate.
	-	We can calculate this value by multiplying the vector `ray_dir`
		with the scalar `perp_wall_dist` and add x-pos or y-pos
		depending on which side of the wall we hit.
*/
void	calculate_wall_x(t_cub *cub)
{
	if (cub->side == SIDE_X)
		cub->wall_x = cub->pos->y + cub->perp_wall_dist * cub->ray_dir->y;
	else
		cub->wall_x = cub->pos->x + cub->perp_wall_dist * cub->ray_dir->x;
	cub->wall_x -= floor(cub->wall_x);
}

/*
	CALCULATE_TEX_X
	-	A texel is a pixel of a texture. Texels need to be scaled to pixels
		on the game screen.
	-	texel->x is the integer texel column we have to use of the texture
	-	We can calculate it by multiplying wall_x with the asset size
	-	Opposite walls must be mirrored, which is achieved by subtracting
		the texel->x value from ASSET_SIZE.
*/
void	calculate_tex_x(t_cub *cub)
{
	cub->texel->x = (int)(cub->wall_x * ((double)ASSET_SIZE));
	if (cub->side == SIDE_X && cub->ray_dir->x > 0)
		cub->texel->x = ASSET_SIZE - cub->texel->x - 1;
	if (cub->side == SIDE_Y && cub->ray_dir->y < 0)
		cub->texel->x = ASSET_SIZE - cub->texel->x - 1;
}

/*
	DRAW_TEXTURE
	-	Let's now use the draw_start and draw_end value to draw
		a vertical pixel column to the screen.
	-	This function is used inside of a loop and loops over the
		pixel column to determine the correct texel->y to be used.
	-	Apply floor and ceiling colours if outside the drawing range
	-	Else, find the integer position of the texel->y, and set to 0
		if this number is negative to not go out of bounds.
	-	Increase the texel_pos with the step, check which direction
		the wall is facing and depending on this, retrieve the hex code
		from the texture
*/
void	draw_texture(int x, int i, t_cub *cub)
{
	t_dir_code		wall_dir;
	unsigned int	color;

	if (i < cub->draw_start)
		color = cub->c_color;
	else if (i >= cub->draw_start && i < cub->draw_end)
	{
		cub->texel->y = (int)cub->texel_pos;
		if (cub->texel->y < 0)
			cub->texel->y = 0;
		cub->texel_pos += cub->texel_step;
		wall_dir = get_wall_dir(cub);
		color = get_texture_color(cub->walls[wall_dir].tex,
				cub->texel->x, cub->texel->y);
	}
	else
		color = cub->f_color;
	my_mlx_pixel_put(cub->img, x, i, color);
}

/*
	APPLY_TEXTURES
	-	Let's apply the textures now to the screen
	-	texel_step: the step by which we must iterate over a texel-column
			->	If we have a large texture (512), but small line to be
				drawn (256), we must step over the texture with a step of 2
			-> If we have a small asset (256), but a large line to be
				drawn (512), we must step over the texture with step 0.5
	-	texel_pos: the y-coordinate of the texture do we need to apply from
		the texel column. Note that the line_length variable is not limited
		to the height of the screen.
	-	Finally, in the draw_texture loop we loop over the texel-column to
		draw the individual y-pixels.
*/
void	apply_textures(t_cub *cub, int x)
{
	int	i;

	calculate_wall_x(cub);
	calculate_tex_x(cub);
	cub->texel_step = 1.0 * ASSET_SIZE / cub->line_height;
	cub->texel_pos = (cub->draw_start - HEIGHT / 2
			+ (double)cub->line_height / 2) * cub->texel_step;
	i = 0;
	while (i < HEIGHT)
		draw_texture(x, i++, cub);
}
