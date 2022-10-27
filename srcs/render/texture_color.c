/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:16:28 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:16:29 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned int	get_texture_color(t_img *texture, int pixel_x, int pixel_y)
{
	return (*(unsigned int *)((texture->addr
			+ (pixel_y * texture->line_length)
			+ (pixel_x * texture->bits_per_pixel / 8))));
}
