#include "cub.h"

void	validate_map_info(int map_fd, t_cub *cub, t_parse_info* parse_info)
{
	while (textures_colors_not_set(cub, parse_info))
	{
		parse_info->ret = get_next_line(map_fd, &parse_info->buff);
		if (parse_info->ret <= 0)
			error_and_exit_from_parsing(MAP_INCORRECT, cub, parse_info, map_fd);
		if (line_is_empty(parse_info->buff))
		{
			parse_info->line_nb++;
			free(parse_info->buff);
			continue ;
		}
		parse_info->line_trimmed = ft_strtrim(parse_info->buff, "\t\v\f\r ");
		parse_info->line_content = ft_split(parse_info->line_trimmed, ' ');
		if (!texture_or_color_is_valid(cub, parse_info))
			error_and_exit_from_parsing(MAP_INCORRECT, cub, parse_info, map_fd);
		parse_info->line_nb++;
		free_parse_info(parse_info);
	}
	while ((parse_info->ret = get_next_line(map_fd, &parse_info->buff)) > 0 &&
		line_is_empty(parse_info->buff))
	{
		parse_info->line_nb++;
		free(parse_info->buff);
	}
}

void	skimm_through_until_map_grid(int map_fd, t_parse_info* parse_info)
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

void	validate_map(int map_fd, char *map_name, t_cub	*cub)
{
	t_parse_info	parse_info;

	parse_info = init_parse_info();
	validate_map_info(map_fd, cub, &parse_info);
	if (parse_info.ret <= 0)
		error_and_exit_from_parsing(MAP_INCORRECT, cub, &parse_info, map_fd);
	evaluate_map_size(map_fd, cub, &parse_info);
	close(map_fd);
	map_fd = open(map_name, O_RDONLY);
	skimm_through_until_map_grid(map_fd, &parse_info);
	validate_map_grid(map_fd, cub, &parse_info);
	free_parse_info(&parse_info);
	close(map_fd);
}
