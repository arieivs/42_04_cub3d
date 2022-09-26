#include "cub.h"

/* Goes through the map for the first time and checks
 * its height and width, so later the appropriate memory
 * can be allocated */
void	evaluate_map_size(int map_fd, t_cub *cub, t_parse_info* parse_info)
{
	parse_info->line_nb_map_start = parse_info->line_nb;
	while (parse_info->ret > 0)
	{
		parse_info->buff = replace_tab_with_spaces(parse_info->buff, cub);
		if (ft_strlen(parse_info->buff) > parse_info->max_map_width)
			parse_info->max_map_width = ft_strlen(parse_info->buff);
		free(parse_info->buff);
		parse_info->ret = get_next_line(map_fd, &parse_info->buff);
		parse_info->line_nb++;
	}
	if (parse_info->ret == -1)
		error_and_exit_from_parsing(MAP_INCORRECT, cub, parse_info, map_fd);
	parse_info->buff = replace_tab_with_spaces(parse_info->buff, cub);
	if (ft_strlen(parse_info->buff) > parse_info->max_map_width)
		parse_info->max_map_width = ft_strlen(parse_info->buff);
	free(parse_info->buff);
	parse_info->line_nb++;
}

/* Sets player's initial position and direction */
void	set_player(t_cub *cub, char player, int x, int y)
{
	cub->map[y][x] = PLAYER;
	cub->pos->x = (double)x;
	cub->pos->y = (double)y;
	if (player == 'N')
		cub->dir->y = -1.0;
	else if (player == 'S')
		cub->dir->y = 1.0;
	else if (player == 'W')
		cub->dir->x = -1.0;
	else if (player == 'E')
		cub->dir->x = 1.0;
}

/*
 * Map line validation
 * - replaces tabs for 4 spaces each
 * - checks for invalid characters
 * - checks for multiplayers
 * - stores information for that map line and position/direction of player
 */
int	map_line_is_valid(t_cub *cub, t_parse_info *parse_info, int y)
{
	int	i;

	i = 0;
	parse_info->buff = replace_tab_with_spaces(parse_info->buff, cub);
	if (line_is_empty(parse_info->buff))
		return (0);
	while ((size_t)i < ft_strlen(parse_info->buff))
	{
		if (parse_info->buff[i] == ' ')
			cub->map[y][i] = OUT;
		else if (parse_info->buff[i] == '0' || parse_info->buff[i] == '1')
			cub->map[y][i] = (int)(parse_info->buff[i] - '0');
		else if (parse_info->buff[i] == 'N' || parse_info->buff[i] == 'S' ||
			parse_info->buff[i] == 'W' || parse_info->buff[i] == 'E')
		{
			if (parse_info->is_player_set)
				return(0);
			parse_info->is_player_set = 1;
			set_player(cub, parse_info->buff[i], i, y);
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
int	map_is_valid(t_cub *cub, t_parse_info *parse_info)
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
void	validate_map_grid(int map_fd, t_cub *cub, t_parse_info* parse_info)
{
	int	i;

	cub->map_height = parse_info->line_nb - parse_info->line_nb_map_start;
	cub->map_width = parse_info->max_map_width;
	cub->map = (int **)ft_calloc(sizeof(int *), cub->map_height);
	i = 0;
	while ((parse_info->ret = get_next_line(map_fd, &parse_info->buff)) > 0)
	{
		cub->map[i] = (int *)ft_calloc(sizeof(int), cub->map_width);
		if (!map_line_is_valid(cub, parse_info, i))
			error_and_exit_from_parsing(MAP_INCORRECT, cub, parse_info, map_fd);
		i++;
		free(parse_info->buff);
	}
	if (parse_info->ret == -1)
		error_and_exit_from_parsing(MAP_INCORRECT, cub, parse_info, map_fd);
	cub->map[i] = (int *)ft_calloc(sizeof(int), cub->map_width);
	if (!map_line_is_valid(cub, parse_info, i))
		error_and_exit_from_parsing(MAP_INCORRECT, cub, parse_info, map_fd);
	free(parse_info->buff); // or remove these two lines
	parse_info->buff = NULL; // and leave it for free_parse_info
	if (!map_is_valid(cub, parse_info))
		error_and_exit_from_parsing(MAP_INCORRECT, cub, parse_info, map_fd);
}
