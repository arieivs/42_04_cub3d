/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graceful_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:17:05 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:17:07 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	graceful_exit(t_cub *cub)
{
	if (cub)
		free_cub(cub);
	ft_putstr_fd("Goodbye!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
