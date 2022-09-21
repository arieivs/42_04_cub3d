#include "cub.h"
#include <string.h>

int	textures_colors_not_set(t_cub *cub, t_parse_info *parse_info)
{
	return (cub->no_fd == 0 || cub->so_fd == 0 || cub->we_fd == 0 ||
		cub->ea_fd == 0 || parse_info->is_floor_color_set == 0 ||
		parse_info->is_ceil_color_set == 0);
}

/* Checks if line is empty or only filled by whitespaces */
int	line_is_empty(char *line)
{
	int	i;

	if (!line)
		return (0);
	if (ft_strlen(line) == 0)
		return (1);
	i = 0;
	while (line[i])
	{
		if (!(line[i] >= 9 && line[i] <= 13) && line[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

int	color_values_valid(t_parse_info *parse_info)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!is_number(parse_info->colors[i]))
			return (0);
		parse_info->colors_rgb[i] = ft_atoi(parse_info->colors[i]);
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
int	color_valid(t_cub *cub, t_parse_info *parse_info, char *content)
{
	if (count_appearances(content, ',') != 2)
		return (0);
	parse_info->colors = ft_split(content, ',');
	if (ft_split_len(parse_info->colors) != 3)
		return (0);
	parse_info->colors_rgb = (int *)calloc_or_exit(sizeof(int), 3, cub);
	if (!color_values_valid(parse_info))
		return (0);
	if ((ft_strncmp(parse_info->prefix, "F", 1) == 0 && parse_info->is_floor_color_set) ||
		(ft_strncmp(parse_info->prefix, "C", 1) == 0 && parse_info->is_ceil_color_set))
		return (0);
	if (ft_strncmp(parse_info->prefix, "F", 1) == 0)
	{
		cub->floor_color = get_trgb(0, parse_info->colors_rgb[0],
			parse_info->colors_rgb[1], parse_info->colors_rgb[2]);
		parse_info->is_floor_color_set = 1;
		return (1);
	}
	cub->ceil_color = get_trgb(0, parse_info->colors_rgb[0],
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
int	texture_valid(t_cub *cub, t_parse_info *parse_info, char *content)
{
	int		fd;

	parse_info->file_name = ft_strtrim(content, "\t\n\v\f\r ");
	if (!has_right_file_ext(parse_info->file_name, "xpm"))
		return (0);
	if ((fd = open(parse_info->file_name, O_RDONLY)) == -1)
		return (error_and_return(FILE_INEXISTENT, 0));
	if ((ft_strncmp(parse_info->prefix, "NO", 2) == 0 && cub->no_fd != 0) ||
		(ft_strncmp(parse_info->prefix, "SO", 2) == 0 && cub->so_fd != 0) ||
		(ft_strncmp(parse_info->prefix, "WE", 2) == 0 && cub->we_fd != 0) ||
		(ft_strncmp(parse_info->prefix, "EA", 2) == 0 && cub->ea_fd != 0))
		return (0);
	if (ft_strncmp(parse_info->prefix, "NO", 2) == 0)
		cub->no_fd = fd;
	else if (ft_strncmp(parse_info->prefix, "SO", 2) == 0)
		cub->so_fd = fd;
	else if (ft_strncmp(parse_info->prefix, "WE", 2) == 0)
		cub->we_fd = fd;
	else
		cub->ea_fd = fd;
	return (1);
}

/*
 * Checks if the texture or color information is valid and stores it
 * - after prefix there might be white spaces -> accomodates for that
 * - if after the prefix there is no more information, it's not valid
 * - checks if prefix is correct
 * - checks if it's a color and if it's valid
 * - checks it it's a texture and if it's valid
 * - if the information is valid, it will be stored in cub struct
 * - it it's not a color neither a texture, return 0
 */
int	texture_or_color_valid(t_cub *cub, t_parse_info	*parse_info)
{
	int	i;
	int	is_valid;

	i = 1;
	is_valid = 0;
	while (line_is_empty(parse_info->line_content[i]))
		i++;
	if (!parse_info->line_content[i])
		return (0);
	parse_info->prefix = ft_strtrim(parse_info->line_content[0], "\t\v\f\r ");
	parse_info->prefix_len = ft_strlen(parse_info->prefix);
	if ((ft_strncmp(parse_info->prefix, "F", 1) == 0 ||
			ft_strncmp(parse_info->prefix, "C", 1) == 0) && parse_info->prefix_len == 1)
		is_valid = color_valid(cub, parse_info, parse_info->line_content[i]);
	if ((ft_strncmp(parse_info->prefix, "NO", 2) == 0 ||
			ft_strncmp(parse_info->prefix, "SO", 2) == 0 ||
			ft_strncmp(parse_info->prefix, "WE", 2) == 0 ||
			ft_strncmp(parse_info->prefix, "EA", 2) == 0) && parse_info->prefix_len == 2)
		is_valid = texture_valid(cub, parse_info, parse_info->line_content[i]);
	if (i + 1 != ft_split_len(parse_info->line_content))
		return (0);
	return (is_valid);
}

char	*replace_tab_with_spaces(char *line, t_cub *cub)
{
	int		tab_nb;
	char	*repl;
	int		i;
	int		j;

	tab_nb = count_appearances(line, '\t');
	if (!tab_nb)
		return (line);
	repl = calloc_or_exit(sizeof(char), ft_strlen(line) + tab_nb * 3 + 1, cub);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\t' && line[i++])
		{
			repl[j++] = ' ';
			repl[j++] = ' ';
			repl[j++] = ' ';
			repl[j++] = ' ';
		}
		else
			repl[j++] = line[i++];
	}
	free(line);
	return (repl);
}

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
 * - checks for invalid characters
 * - checks for multiplayers
 * - stores information for that map line and position/direction of player
 */
int	map_line_valid(t_cub *cub, t_parse_info *parse_info, int y)
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

void	check_map(int map_fd, char *map_name, t_cub	*cub)
{
	t_parse_info	parse_info;
	int				i;

	parse_info = init_parse_info();
	while (textures_colors_not_set(cub, &parse_info))
	{
		parse_info.ret = get_next_line(map_fd, &parse_info.buff);
		if (parse_info.ret <= 0)
			error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info, map_fd);
		if (line_is_empty(parse_info.buff))
		{
			parse_info.line_nb++;
			free(parse_info.buff);
			continue ;
		}
		parse_info.line_trimmed = ft_strtrim(parse_info.buff, "\t\v\f\r ");
		parse_info.line_content = ft_split(parse_info.line_trimmed, ' ');
		if (!texture_or_color_valid(cub, &parse_info))
			error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info, map_fd);
		printf("%d-%d: %s\n", parse_info.ret, parse_info.line_nb, parse_info.buff);
		parse_info.line_nb++;
		free_parse_info(&parse_info);
	}
	while ((parse_info.ret = get_next_line(map_fd, &parse_info.buff)) > 0 &&
		line_is_empty(parse_info.buff))
	{
		printf("Empty line %d\n", parse_info.line_nb);
		parse_info.line_nb++;
		free(parse_info.buff);
	}
	if (parse_info.ret <= 0) // think if really needed
		error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info, map_fd);
	parse_info.line_nb_map_start = parse_info.line_nb;
	while (parse_info.ret > 0)
	{
		printf("map line %d: %s\n", parse_info.line_nb, parse_info.buff);
		parse_info.buff = replace_tab_with_spaces(parse_info.buff, cub);
		if (ft_strlen(parse_info.buff) > parse_info.max_map_width)
			parse_info.max_map_width = ft_strlen(parse_info.buff);
		printf("max map width %lu\n", parse_info.max_map_width);
		free(parse_info.buff);
		parse_info.ret = get_next_line(map_fd, &parse_info.buff);
		parse_info.line_nb++;
	}
	if (parse_info.ret == -1)
		error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info, map_fd);
	printf("map line %d: %s\n", parse_info.line_nb, parse_info.buff);
	parse_info.buff = replace_tab_with_spaces(parse_info.buff, cub);
	if (ft_strlen(parse_info.buff) > parse_info.max_map_width)
		parse_info.max_map_width = ft_strlen(parse_info.buff);
	printf("max map width %lu\n", parse_info.max_map_width);
	free(parse_info.buff);
	parse_info.line_nb++;
	close(map_fd);
	map_fd = open(map_name, O_RDONLY);
	i = 1;
	while (i < parse_info.line_nb_map_start &&
		(parse_info.ret = get_next_line(map_fd, &parse_info.buff)) > 0)
	{
		printf("we're at %d-%s-\n", i, parse_info.buff);
		i++;
		free(parse_info.buff);
	}
	cub->map_height = parse_info.line_nb - parse_info.line_nb_map_start;
	cub->map_width = parse_info.max_map_width;
	printf("map starts at %d ends at %d height %d width %d\n", parse_info.line_nb_map_start, parse_info.line_nb, cub->map_height, cub->map_width);
	cub->map = (int **)ft_calloc(sizeof(int *), cub->map_height);
	i = 0;
	while ((parse_info.ret = get_next_line(map_fd, &parse_info.buff)) > 0)
	{
		cub->map[i] = (int *)ft_calloc(sizeof(int), cub->map_width);
		if (!map_line_valid(cub, &parse_info, i))
			error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info, map_fd);
		printf("just checked %d-%s\n", i, parse_info.buff);
		i++;
		free(parse_info.buff);
	}
	if (parse_info.ret == -1)
		error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info, map_fd);
	cub->map[i] = (int *)ft_calloc(sizeof(int), cub->map_width);
	if (!map_line_valid(cub, &parse_info, i))
		error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info, map_fd);
	printf("just checked %d-%s\n", i, parse_info.buff);
	free(parse_info.buff); // or remove these two lines
	parse_info.buff = NULL; // and leave it for free_parse_info
	
	// TODO validate map - check if closed and if player is set
	
	free_parse_info(&parse_info);
	close(map_fd);
}
