/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:12:09 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:12:11 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_args(int ac, char **av)
{
	int	file_fd;

	if (ac != 2)
		return (error_and_return(WRONG_ARGC, -1));
	if (!has_right_file_ext(av[1], "cub"))
		return (error_and_return(WRONG_FILE_EXT, -1));
	file_fd = open(av[1], O_RDONLY);
	if (file_fd == -1)
		return (error_and_return(FILE_INEXISTENT, -1));
	return (file_fd);
}
