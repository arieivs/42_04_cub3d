#include "cub.h"

int	has_right_file_ext(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 5)
		return (0);
	if (str[len - 4] == '.' && str[len - 3] == 'c' && str[len - 2] == 'u' &&
		str[len - 1] == 'b')
		return (1);
	return (0);
}

int	check_args(int ac, char **av)
{
	int	file_fd;

	if (ac != 2)
		return (error_and_return(WRONG_ARGC, -1));
	if (!has_right_file_ext(av[1]))
		return (error_and_return(WRONG_FILE_EXT, -1));
	file_fd = open(av[1], O_RDONLY);
	if (file_fd == -1)
		return (error_and_return(FILE_INEXISTENT, -1));
	return (file_fd);
}

t_cub	init_cub(void)
{
	t_cub	cub;

	cub.mlx = NULL;
	cub.window = NULL;
	cub.img = NULL;
	cub.addr = NULL;
	cub.no_fd = 0;
	cub.so_fd = 0;
	cub.we_fd = 0;
	cub.ea_fd = 0;
	cub.floor_color = 0;
	cub.ceil_color = 0;
	cub.map = NULL;
	cub.pos = (t_pair *)calloc_or_exit(sizeof(t_pair), 1, &cub);
	cub.pos->x = 0.0;
	cub.pos->y = 0.0;
	cub.dir = (t_pair *)calloc_or_exit(sizeof(t_pair), 1, &cub);
	cub.dir->x = 0.0;
	cub.dir->y = 0.0;
	cub.proj_plane = (t_pair *)calloc_or_exit(sizeof(t_pair), 1, &cub);
	cub.proj_plane->x = 0.0;
	cub.proj_plane->y = 0.0;
	return (cub);
}

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
		if (!(str[i] >= 9 && str[i] <= 13) && str[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

/* Checks if line has the information for a texture and color
 * and if that information is valid (file exists, color is correct...)
 * if yes, it stores it in the cub struct, else it returns 0
 */
int	texture_or_color_valid(t_cub *cub, t_parse_info	parse_info)
{
	char	*clean_prefix;
	int		prefix_len;
	int		i;

	clean_prefix = ft_strtrim(parse_info->line_content[0], "\t\n\v\f\r ");
	prefix_len = ft_strlen(clean_prefix);
	// CHECK should I tream suffix as well?
	i = 1;
	while (line_is_empty(parse_info->line_content[i]))
		i++;
	if (ft_strncmp(clean_prefix, "NO", 2) && prefix_len == 2)
	{
		cub->no_fd = open()
	}
	free (clean_prefix);
}

t_parse_info	init_parse_info(void)
{
	t_parse_info	parse_info;

	parse_info.buff	= NULL;
	parse_info.ret = 0;
	parse_info.line_nb = 1;
	parse_info.is_floor_color_set = 0;
	parse_info.is_ceil_color_set = 0;
	parse_info.line_content = NULL;
	return (parse_info);
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
		parse_info.line_content = ft_split(parse_info.buff);
		if (!texture_or_color_valid(cub, &parse_info))
			error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info);
		printf("%d-%d: %s\n", parse_info.ret, parse_info.line_nb, parse_info.buff);
		parse_info.line_nb++;
		free(parse_info.buff);
		free_split(parse_info.line_content);
	}
	// bullshit below
	printf("%d-%d: %s\n", parse_info.ret, parse_info.line_nb++, parse_info.buff);
	if (parse_info.ret == 0)
		printf("Reached EOF\n");
	if (parse_info.ret == -1)
		printf("An Error occurred\n");
	close(map_fd);
	free(parse_info.buff);
	return (0);
}

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Let's play!");
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel,
			&cub->line_length, &cub->endian);
}
