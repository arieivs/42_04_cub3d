#include "cub.h"

int	textures_colors_not_set(t_cub *cub, t_parse_info *parse_info)
{
	return (cub->walls[NO].path == NULL || cub->walls[SO].path == NULL || cub->walls[WE].path == NULL ||
		cub->walls[EA].path == NULL || parse_info->is_floor_color_set == 0 ||
		parse_info->is_ceil_color_set == 0);
}

int	color_values_are_valid(t_parse_info *parse_info)
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
int	color_is_valid(t_cub *cub, t_parse_info *parse_info, char *content)
{
	if (count_appearances(content, ',') != 2)
		return (0);
	parse_info->colors = ft_split(content, ',');
	if (ft_split_len(parse_info->colors) != 3)
		return (0);
	parse_info->colors_rgb = (int *)calloc_or_exit(sizeof(int), 3, cub);
	if (!color_values_are_valid(parse_info))
		return (0);
	if ((ft_strncmp(parse_info->prefix, "F", 1) == 0 && parse_info->is_floor_color_set) ||
		(ft_strncmp(parse_info->prefix, "C", 1) == 0 && parse_info->is_ceil_color_set))
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
int	texture_is_valid(t_cub *cub, t_parse_info *parse_info, char *content)
{
	int		fd;

	parse_info->file_name = ft_strtrim(content, "\t\n\v\f\r ");
	if (!has_right_file_ext(parse_info->file_name, "xpm"))
		return (0);
	if ((fd = open(parse_info->file_name, O_RDONLY)) == -1)
		return (error_and_return(FILE_INEXISTENT, 0));
	if ((ft_strncmp(parse_info->prefix, "NO", 2) == 0 && cub->walls[NO].path) ||
		(ft_strncmp(parse_info->prefix, "SO", 2) == 0 && cub->walls[SO].path) ||
		(ft_strncmp(parse_info->prefix, "WE", 2) == 0 && cub->walls[WE].path) ||
		(ft_strncmp(parse_info->prefix, "EA", 2) == 0 && cub->walls[EA].path))
		return (0);
	if (ft_strncmp(parse_info->prefix, "NO", 2) == 0)
		cub->walls[NO].path = ft_strdup(parse_info->file_name);
	else if (ft_strncmp(parse_info->prefix, "SO", 2) == 0)
		cub->walls[SO].path = ft_strdup(parse_info->file_name);
	else if (ft_strncmp(parse_info->prefix, "WE", 2) == 0)
		cub->walls[WE].path = ft_strdup(parse_info->file_name);
	else
		cub->walls[EA].path = ft_strdup(parse_info->file_name);
	close(fd);
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
int	texture_or_color_is_valid(t_cub *cub, t_parse_info	*parse_info)
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
		is_valid = color_is_valid(cub, parse_info, parse_info->line_content[i]);
	if ((ft_strncmp(parse_info->prefix, "NO", 2) == 0 ||
			ft_strncmp(parse_info->prefix, "SO", 2) == 0 ||
			ft_strncmp(parse_info->prefix, "WE", 2) == 0 ||
			ft_strncmp(parse_info->prefix, "EA", 2) == 0) && parse_info->prefix_len == 2)
		is_valid = texture_is_valid(cub, parse_info, parse_info->line_content[i]);
	if (i + 1 != ft_split_len(parse_info->line_content))
		return (0);
	return (is_valid);
}
