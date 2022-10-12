#include "cub.h"

/* SINGLETONS
 * The concept of a singleton is to create an object once
 * and then be able to access it any time
 * while not using global variable thanks to a stored pointer.
 */

t_cub	*get_cub(t_cub *cub)
{
	static t_cub	*cub_ptr = NULL;

	if (!cub_ptr && cub)
		cub_ptr = cub;
	return (cub_ptr);
}

t_parse_info	*get_parse_info(t_parse_info *parse_info)
{
	static t_parse_info	*parse_info_ptr = NULL;

	if (!parse_info_ptr && parse_info)
		parse_info_ptr = parse_info;
	return (parse_info);
}
