/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:16:02 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 15:35:04 by svieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* Sets player's initial position and direction */
void	set_player(t_cub *cub, t_parse_info *parse_info, int x, int y)
{
	cub->map[y][x] = PLAYER;
	cub->pos->x = (double)x + 0.5;
	cub->pos->y = (double)y + 0.5;
	if (parse_info->buff[x] == 'N')
	{
		cub->dir->y = -1.0;
		cub->proj_plane->x = PROJ_PLANE_LEN;
	}
	else if (parse_info->buff[x] == 'S')
	{
		cub->dir->y = 1.0;
		cub->proj_plane->x = -PROJ_PLANE_LEN;
	}
	else if (parse_info->buff[x] == 'W')
	{
		cub->dir->x = -1.0;
		cub->proj_plane->y = -PROJ_PLANE_LEN;
	}
	else if (parse_info->buff[x] == 'E')
	{
		cub->dir->x = 1.0;
		cub->proj_plane->y = PROJ_PLANE_LEN;
	}
	parse_info->is_player_set = 1;
}

/*
 * Map line validation
 * - replaces tabs for 4 spaces each
 * - checks for invalid characters
 * - checks for multiplayers
 * - stores information for that map line and position/direction of player
 */
static int	map_line_is_valid(t_cub *cub, t_parse_info *parse_info, int y)
{
	int	i;

	i = 0;
	parse_info->buff = replace_tab_with_spaces(parse_info->buff);
	if (line_is_empty(parse_info->buff))
		return (0);
	while ((size_t)i < ft_strlen(parse_info->buff))
	{
		if (parse_info->buff[i] == ' ')
			cub->map[y][i] = OUT;
		else if (parse_info->buff[i] == '0' || parse_info->buff[i] == '1')
			cub->map[y][i] = (int)(parse_info->buff[i] - '0');
		else if (ft_strchr("NSWE", parse_info->buff[i]))
		{
			if (parse_info->is_player_set)
				return (0);
			set_player(cub, parse_info, i, y);
		}
		else
			return (0);
		i++;
	}
	while (i < cub->map_width)
		cub->map[y][i++] = OUT;
	return (1);
}

/*
 * Map validation
 * - makes sure there is a player
 * - checks if map is closed: interior/player cannot be at the border,
 *   nor in contact with the outside
 */
static int	map_is_valid(t_cub *cub, t_parse_info *parse_info)
{
	int	x;
	int	y;

	if (!parse_info->is_player_set)
		return (0);
	y = 0;
	while (y < cub->map_height)
	{
		x = 0;
		while (x < cub->map_width)
		{
			if ((cub->map[y][x] == IN || cub->map[y][x] == PLAYER) &&
				(y == 0 || y == cub->map_height - 1 ||
				x == 0 || x == cub->map_width - 1 ||
				cub->map[y - 1][x - 1] == OUT || cub->map[y - 1][x] == OUT ||
				cub->map[y - 1][x + 1] == OUT || cub->map[y][x - 1] == OUT ||
				cub->map[y][x + 1] == OUT || cub->map[y + 1][x - 1] == OUT ||
				cub->map[y + 1][x] == OUT || cub->map[y + 1][x + 1] == OUT))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

/* Goes through the map a second time, stores the information
 * and validates it */
void	validate_map_grid(t_cub *cub, t_parse_info *parse_info)
{
	int	i;

	cub->map = (int **)ft_calloc(sizeof(int *), cub->map_height);
	i = 0;
	while (i < cub->map_height)
	{
		parse_info->ret = get_next_line(cub->map_fd, &parse_info->buff);
		if (parse_info->ret == -1)
			error_and_exit(READ_FAIL);
		cub->map[i] = (int *)ft_calloc(sizeof(int), cub->map_width);
		if (!map_line_is_valid(cub, parse_info, i))
			error_and_exit(MAP_INCORRECT);
		i++;
		free(parse_info->buff);
	}
	while (parse_info->ret > 0)
	{
		parse_info->ret = get_next_line(cub->map_fd, &parse_info->buff);
		if (parse_info->ret == -1 || !line_is_empty(parse_info->buff))
			error_and_exit(MAP_INCORRECT);
		free(parse_info->buff);
	}
	parse_info->buff = NULL;
	if (!map_is_valid(cub, parse_info))
		error_and_exit(MAP_INCORRECT);
}
