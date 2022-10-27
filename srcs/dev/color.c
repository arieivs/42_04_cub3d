/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:15:31 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:15:33 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_t(int trgb)
{
	return ((trgb >> 24) & 255);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 255);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 255);
}

int	get_b(int trgb)
{
	return (trgb & 255);
}
