/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:15:59 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:16:00 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	evaluate_map_line_size(t_parse_info *parse_info)
{
	parse_info->buff = replace_tab_with_spaces(parse_info->buff);
	if (ft_strlen(parse_info->buff) > parse_info->max_map_width)
		parse_info->max_map_width = ft_strlen(parse_info->buff);
	parse_info->line_nb++;
}

/* Goes through the map for the first time and checks its height and width,
 * so later the appropriate memory can be allocated.
 * need to go until the end of the file, else it won't restart properly
 */
void	evaluate_map_size(t_cub *cub, t_parse_info* parse_info)
{
	parse_info->line_nb_map_start = parse_info->line_nb;
	while (parse_info->ret > 0 && !line_is_empty(parse_info->buff))
	{
		evaluate_map_line_size(parse_info);
		free(parse_info->buff);
		parse_info->ret = get_next_line(cub->map_fd, &parse_info->buff);
	}
	if (parse_info->ret == -1)
		error_and_exit(READ_FAIL);
	if (!line_is_empty(parse_info->buff))
		evaluate_map_line_size(parse_info);
	free(parse_info->buff);
	if (parse_info->ret > 0)
	{
		while ((parse_info->ret = get_next_line(cub->map_fd, &parse_info->buff)) > 0)
			free(parse_info->buff);
		free(parse_info->buff);
	}
	cub->map_height = parse_info->line_nb - parse_info->line_nb_map_start;
	cub->map_width = parse_info->max_map_width;
}
