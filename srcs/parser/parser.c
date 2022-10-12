#include "cub.h"

/*
 * VALIDATE MAP 🍻
 * - validates map's info - textures and colours 🎨
 * - if the file ends there, error
 * - goes through the actual map a first time, to check its dimensions
 * - reopens the file and goes back to the beginning of the map
 * - validates map, first each individual line, then as a whole 🗺
 * - if at any point there is an error, everything is freed and we exit
 */

void	validate_map_info(t_cub *cub, t_parse_info* parse_info)
{
	while (textures_colors_not_set(cub, parse_info))
	{
		parse_info->ret = get_next_line(cub->map_fd, &parse_info->buff);
		if (parse_info->ret <= 0)
			error_and_exit(MAP_INCORRECT);
		if (line_is_empty(parse_info->buff))
		{
			parse_info->line_nb++;
			free(parse_info->buff);
			continue ;
		}
		parse_info->line_trimmed = ft_strtrim(parse_info->buff, "\t\v\f\r ");
		parse_info->line_content = ft_split(parse_info->line_trimmed, ' ');
		if (!texture_or_color_is_valid(cub, parse_info))
			error_and_exit(MAP_INCORRECT);
		parse_info->line_nb++;
		free_parse_info(parse_info);
	}
	while ((parse_info->ret = get_next_line(cub->map_fd, &parse_info->buff)) > 0
		&& line_is_empty(parse_info->buff))
	{
		parse_info->line_nb++;
		free(parse_info->buff);
	}
}

static void	skimm_through_until_map_grid(int map_fd, t_parse_info* parse_info)
{
	int	i;

	i = 1;
	while (i < parse_info->line_nb_map_start &&
		(parse_info->ret = get_next_line(map_fd, &parse_info->buff)) > 0)
	{
		i++;
		free(parse_info->buff);
	}
}

void	validate_map(char *map_name, t_cub	*cub)
{
	t_parse_info	parse_info;

	parse_info = init_parse_info();
	validate_map_info(cub, &parse_info);
	if (parse_info.ret <= 0)
		error_and_exit(MAP_INCORRECT);
	evaluate_map_size(cub, &parse_info);
	cub->map_fd = close_or_exit(cub->map_fd);
	cub->map_fd = open_or_exit(map_name, O_RDONLY);
	skimm_through_until_map_grid(cub->map_fd, &parse_info);
	validate_map_grid(cub, &parse_info);
	free_parse_info(&parse_info);
	cub->map_fd = close_or_exit(cub->map_fd);
}
