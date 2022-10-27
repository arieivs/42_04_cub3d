/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:15:56 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:27:36 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	textures_colors_not_set(t_cub *cub, t_parse_info *parse_info)
{
	return (cub->walls[NO].path == NULL || cub->walls[SO].path == NULL
		|| cub->walls[WE].path == NULL || cub->walls[EA].path == NULL
		|| parse_info->is_floor_color_set == 0
		|| parse_info->is_ceil_color_set == 0);
}

static int	color_values_are_valid(t_parse_info *parse_info)
{
	int		i;
	char	*color_trimmed;

	i = 0;
	while (i < 3)
	{
		color_trimmed = ft_strtrim(parse_info->colors[i], "\t\v\f\r ");
		if (!is_number(color_trimmed))
		{
			free(color_trimmed);
			return (0);
		}
		parse_info->colors_rgb[i] = ft_atoi(color_trimmed);
		free(color_trimmed);
		if (parse_info->colors_rgb[i] < 0 || parse_info->colors_rgb[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

/*
 * Color validation
 * - checks if there's 3 values from 0 to 255
 * - makes sure this color hadn't been defined already
 * - not ok: ,255,,0,4,
 * - not ok: spaces in the middle (since we're splitting over spaces first)
 * - ok: 255,+160,1
 */
static int	color_is_valid(t_cub *cub, t_parse_info *parse_info, char *content)
{
	if (count_appearances(content, ',') != 2)
		return (0);
	parse_info->colors = ft_split(content, ',');
	if (ft_split_len(parse_info->colors) != 3)
		return (0);
	parse_info->colors_rgb = (int *)calloc_or_exit(sizeof(int), 3);
	if (!color_values_are_valid(parse_info))
		return (0);
	if ((ft_strncmp(parse_info->prefix, "F", 1) == 0
			&& parse_info->is_floor_color_set)
		|| (ft_strncmp(parse_info->prefix, "C", 1) == 0
			&& parse_info->is_ceil_color_set))
		return (0);
	if (ft_strncmp(parse_info->prefix, "F", 1) == 0)
	{
		cub->f_color = get_trgb(0, parse_info->colors_rgb[0],
				parse_info->colors_rgb[1], parse_info->colors_rgb[2]);
		parse_info->is_floor_color_set = 1;
		return (1);
	}
	cub->c_color = get_trgb(0, parse_info->colors_rgb[0],
			parse_info->colors_rgb[1], parse_info->colors_rgb[2]);
	parse_info->is_ceil_color_set = 1;
	return (1);
}

/*
 * Texture validation
 * - checks it's an .xpm file
 * - checks the files exists/can be opened
 * - makes sure this texture hadn't been defined already
 */
static int	texture_is_valid(t_cub *cub, t_parse_info *parse_info)
{
	int		fd;

	if (!has_right_file_ext(parse_info->content, "xpm"))
		return (0);
	if ((fd = open(parse_info->content, O_RDONLY)) == -1)
		return (error_and_return(FILE_INEXISTENT, 0));
	if ((ft_strncmp(parse_info->prefix, "NO", 2) == 0 && cub->walls[NO].path)
		|| (ft_strncmp(parse_info->prefix, "SO", 2) == 0 && cub->walls[SO].path)
		|| (ft_strncmp(parse_info->prefix, "WE", 2) == 0 && cub->walls[WE].path)
		|| (ft_strncmp(parse_info->prefix, "EA", 2) == 0 && cub->walls[EA].path))
		return (0);
	if (ft_strncmp(parse_info->prefix, "NO", 2) == 0)
		cub->walls[NO].path = ft_strdup(parse_info->content);
	else if (ft_strncmp(parse_info->prefix, "SO", 2) == 0)
		cub->walls[SO].path = ft_strdup(parse_info->content);
	else if (ft_strncmp(parse_info->prefix, "WE", 2) == 0)
		cub->walls[WE].path = ft_strdup(parse_info->content);
	else
		cub->walls[EA].path = ft_strdup(parse_info->content);
	close_or_exit(fd);
	return (1);
}

/*
 * Checks if the texture or color information is valid and stores it
 * - checks if prefix is correct
 * - checks if it's a color and if it's valid
 * - checks it it's a texture and if it's valid
 * - if the information is valid, it will be stored in cub struct
 * - it it's not a color neither a texture, return 0
 */
int	texture_or_color_is_valid(t_cub *cub, t_parse_info	*parse_info)
{
	int	is_valid;

	is_valid = 0;
	if (parse_info->prefix_len == 0 || ft_strlen(parse_info->content) == 0)
		return (0);
	if ((ft_strncmp(parse_info->prefix, "F", 1) == 0
			|| ft_strncmp(parse_info->prefix, "C", 1) == 0)
		&& parse_info->prefix_len == 1)
		is_valid = color_is_valid(cub, parse_info, parse_info->content);
	if ((ft_strncmp(parse_info->prefix, "NO", 2) == 0
			|| ft_strncmp(parse_info->prefix, "SO", 2) == 0
			|| ft_strncmp(parse_info->prefix, "WE", 2) == 0
			|| ft_strncmp(parse_info->prefix, "EA", 2) == 0)
		&& parse_info->prefix_len == 2)
			is_valid = texture_is_valid(cub, parse_info);
	return (is_valid);
}
