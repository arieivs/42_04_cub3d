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
		return (0); // will this give issues?
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

/*
 * Color validation
 * - checks if there's 3 values from 0 to 255
 * - makes sure this color hadn't been defined already
 * - not ok: ,255,,0,4,
 * - ok: 255, +160, 1
 */
int	color_valid(t_cub *cub, t_parse_info *parse_info, char *content)
{
	int		i;

	parse_info->colors = ft_split(content, ',');
	if (ft_split_len(parse_info->colors) != 3)
		return (0);
	i = 0;
	parse_info->colors_rgb = (int *)calloc_or_exit(sizeof(int), 3, cub);
	while (i < 3)
	{
		parse_info->colors_rgb[i] = ft_atoi(parse_info->colors[i]);
		if (parse_info->colors_rgb[i] < 0 || parse_info->colors_rgb[i] > 255)
			return (0);
		i++;
	}
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
	// doesn't care about:
	// +160
	// ,255,5,,5, (commas around)
	// 3, 6 , 6 (spaces)
}

/*
 * Texture validation
 * - checks it's an .xpm file
 * - checks the files exists/can be opened
 * - makes sure this texture hadn't been defined already
 */
int	texture_valid(t_cub *cub, t_parse_info *parse_info, char *content)
{
	char	*file_name;
	int		fd;

	file_name = ft_strtrim(content, "\t\n\v\f\r ");
	if (!has_right_file_ext(file_name, "xpm"))
		return (0);
	if ((fd = open(file_name, O_RDONLY)) == -1)
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

	i = 1;
	while (line_is_empty(parse_info->line_content[i]))
		i++;
	if (!parse_info->line_content[i])
		return (0);
	parse_info->prefix = ft_strtrim(parse_info->line_content[0], "\t\n\v\f\r ");
	parse_info->prefix_len = ft_strlen(parse_info->prefix);
	if ((ft_strncmp(parse_info->prefix, "F", 1) == 0 ||
			ft_strncmp(parse_info->prefix, "C", 1) == 0) && parse_info->prefix_len == 1)
		return (color_valid(cub, parse_info, parse_info->line_content[i]));
	if ((ft_strncmp(parse_info->prefix, "NO", 2) == 0 ||
			ft_strncmp(parse_info->prefix, "SO", 2) == 0 ||
			ft_strncmp(parse_info->prefix, "WE", 2) == 0 ||
			ft_strncmp(parse_info->prefix, "EA", 2) == 0) && parse_info->prefix_len == 2)
		return (texture_valid(cub, parse_info, parse_info->line_content[i]));
	return (0);
	// if there's extra info I don't track that
}

/*
 * Map line validation
 * - checks for invalid characters
 * - checks for multiplayers
 * - stores information for that map line and position/direction of player
 */
int	map_line_valid(int	*map_line, t_cub *cub, t_parse_info *parse_info)
{
	int	i;
	int	line_len;

	i = 0;
	// TODO replace line tabs with spaces
	line_len = ft_strlen(parse_info->buff);
	if (line_is_empty(parse_info->buff))
		return (0);
	while (i < line_len)
	{
		if (parse_info->buff[i] == ' ')
			map_line[i] = OUT;
		else if (parse_info->buff[i] == '0' || parse_info->buff[i] == '1')
			map_line[i] = (int)(parse_info->buff[i] - '0');
		else if (parse_info->buff[i] == 'N' || parse_info->buff[i] == 'S' ||
			parse_info->buff[i] == 'W' || parse_info->buff[i] == 'E')
		{
			if (parse_info->is_player_set)
				return(0);
			map_line[i] = PLAYER;
			parse_info->is_player_set = 1;
			// TODO define pos and dir
		}
		else
			return (0);
		i++;
	}
	while (i < cub->map_width)
	{
		map_line[i] = OUT;
		i++;
	}
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
			continue ;
		}
		parse_info.line_content = ft_split(parse_info.buff, ' ');
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
		// TODO replace tabs with 4 spaces
		if (ft_strlen(parse_info.buff) > parse_info.max_map_width)
			parse_info.max_map_width = ft_strlen(parse_info.buff);
		printf("max map width %lu\n", parse_info.max_map_width);
		free(parse_info.buff);
		parse_info.ret = get_next_line(map_fd, &parse_info.buff);
		parse_info.line_nb++;
	}
	if (parse_info.ret == 0) // should just give error if -1 instead?
	{
		printf("map line %d: %s\n", parse_info.line_nb, parse_info.buff);
		// TODO replace tabs with 4 spaces
		if (ft_strlen(parse_info.buff) > parse_info.max_map_width)
			parse_info.max_map_width = ft_strlen(parse_info.buff);
		printf("max map width %lu\n", parse_info.max_map_width);
		free(parse_info.buff);
		parse_info.line_nb++;
	}
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
		// store line map - needs to be &cub->map[i] ?
		cub->map[i] = (int *)ft_calloc(sizeof(int), cub->map_width);
		if (!map_line_valid(cub->map[i], cub, &parse_info))
			error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info, map_fd);
		printf("just checked %d-%s\n", i, parse_info.buff);
		i++;
		free(parse_info.buff);
	}
	if (parse_info.ret == 0)// should just give error if -1 instead?
	{
		cub->map[i] = (int *)ft_calloc(sizeof(int), cub->map_width);
		if (!map_line_valid(cub->map[i], cub, &parse_info))
			error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info, map_fd);
		printf("just checked %d-%s\n", i, parse_info.buff);
		free(parse_info.buff); // or remove these two lines
		parse_info.buff = NULL; // and leave it for free_parse_info
	}
	// TODO validate map - check if closed and if player is set
	close(map_fd);
	free_parse_info(&parse_info);
}
