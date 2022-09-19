#include "cub.h"

int	textures_colors_not_set(t_cub *cub, t_parse_info *parse_info)
{
	/*return (cub->no_fd == 0 || cub->so_fd == 0 || cub->we_fd == 0 ||
		cub->ea_fd == 0 || parse_info->is_floor_color_set == 0 ||
		parse_info->is_ceil_color_set == 0);*/
	(void)cub;
	return (parse_info->is_floor_color_set == 0 ||
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
 * checks if there's 3 values from 0 to 255
 */
int	color_valid(t_cub *cub, t_parse_info *parse_info, char *content)
{
	int		i;
	int		*colors_rgb;

	parse_info->colors = ft_split(content, ',');
	if (ft_split_len(parse_info->colors) != 3)
		return (0);
	i = 0;
	colors_rgb = (int *)calloc_or_exit(sizeof(int), 3, cub);
	while (i < 3)
	{
		colors_rgb[i] = ft_atoi(parse_info->colors[i]);
		if (colors_rgb[i] < 0 || colors_rgb[i] > 255)
		{
			free(colors_rgb);
			return (0);
		}
		i++;
	}
	if (ft_strncmp(parse_info->prefix, "F", 1) == 0)
	{
		cub->floor_color = get_trgb(0, colors_rgb[0], colors_rgb[1], colors_rgb[2]);
		parse_info->is_floor_color_set = 1;
		free(colors_rgb);
		return (1);
	}
	cub->ceil_color = get_trgb(0, colors_rgb[0], colors_rgb[1], colors_rgb[2]);
	parse_info->is_ceil_color_set = 1;
	free(colors_rgb);
	return (1);
}

int	texture_valid(t_cub *cub, t_parse_info *parse_info, char *content)
{
	(void)cub;
	(void)parse_info;
	(void)content;
	// TODO
	//cub->no_fd = open(parse_info->line_content[i], O_RDONLY);
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
	while (line_is_empty(parse_info->line_content[i])) // check if needed - tabs!
		i++;
	if (!parse_info->line_content[i])
		return (0); // makes sense? or it will fail naturally on open?
	parse_info->prefix = ft_strtrim(parse_info->line_content[0], "\t\n\v\f\r ");
	parse_info->prefix_len = ft_strlen(parse_info->prefix);
	// CHECK should I tream suffix as well?
  	if ((ft_strncmp(parse_info->prefix, "F", 1) == 0 ||
			ft_strncmp(parse_info->prefix, "C", 1) == 0) && parse_info->prefix_len == 1)
		return (color_valid(cub, parse_info, parse_info->line_content[i]));
	if ((ft_strncmp(parse_info->prefix, "NO", 2) == 0 ||
			ft_strncmp(parse_info->prefix, "SO", 2) == 0 ||
			ft_strncmp(parse_info->prefix, "WE", 2) == 0 ||
			ft_strncmp(parse_info->prefix, "EA", 2) == 0) && parse_info->prefix_len == 2)
		return (texture_valid(cub, parse_info, parse_info->line_content[i]));
	return (0);
}

int	check_map(int map_fd, t_cub	*cub)
{
	t_parse_info	parse_info;

	parse_info = init_parse_info();
	while (textures_colors_not_set(cub, &parse_info))
	{
		parse_info.ret = get_next_line(map_fd, &parse_info.buff);
		if (parse_info.ret <= 0)
			error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info);
		if (line_is_empty(parse_info.buff))
			continue ;
		parse_info.line_content = ft_split(parse_info.buff, ' ');
		if (!texture_or_color_valid(cub, &parse_info))
			error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info);
		parse_info.line_nb++;
		printf("%d-%d: %s\n", parse_info.ret, parse_info.line_nb, parse_info.buff);
		free_parse_info(&parse_info);
	}
	// TODO 
	// validate map
	// store map
	// bullshit below
	/*printf("%d-%d: %s\n", parse_info.ret, parse_info.line_nb++, parse_info.buff);
	if (parse_info.ret == 0)
		printf("Reached EOF\n");
	if (parse_info.ret == -1)
		printf("An Error occurred\n");
	close(map_fd);
	free(parse_info.buff);*/
	//free_parse_info(&parse_info);
	return (0);
}
