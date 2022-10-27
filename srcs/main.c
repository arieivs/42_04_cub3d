/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:12:42 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:13:26 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av)
{
	t_cub	*cub;
	int		map_fd;

	map_fd = check_args(ac, av);
	if (map_fd == -1)
		return (1);
	cub = init_cub(map_fd);
	validate_map(av[1], cub);
	init_mlx(cub);
	render(cub);
	mlx_hook(cub->window, ON_KEYUP, 1L << 1, key_up, cub);
	mlx_hook(cub->window, ON_KEYDOWN, 1L << 0, key_down, cub);
	mlx_hook(cub->window, ON_MOUSEMOVE, 1L << 6, mouse_hook, cub);
	mlx_hook(cub->window, ON_DESTROY, 0, graceful_exit, cub);
	mlx_loop_hook(cub->mlx, update_display, cub);
	mlx_loop(cub->mlx);
	return (0);
}
