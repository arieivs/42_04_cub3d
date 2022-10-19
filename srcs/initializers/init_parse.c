#include "cub.h"

t_parse_info	*init_parse_info(void)
{
	t_parse_info	*parse_info;

	parse_info = (t_parse_info *)calloc_or_exit(sizeof(t_parse_info), 1);
	get_parse_info(parse_info, 0);
	parse_info->buff = NULL;
	parse_info->ret = 0;
	parse_info->line_nb = 1;
	parse_info->line = NULL;
	parse_info->prefix = NULL;
	parse_info->prefix_len = 0;
	parse_info->content = NULL;
	parse_info->colors = NULL;
	parse_info->colors_rgb = NULL;
	parse_info->is_floor_color_set = 0;
	parse_info->is_ceil_color_set = 0;
	parse_info->line_nb_map_start = 0;
	parse_info->max_map_width = 0;
	parse_info->is_player_set = 0;
	return (parse_info);
}
