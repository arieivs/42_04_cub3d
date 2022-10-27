/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:14:29 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/10/27 14:14:31 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	has_right_file_ext(char *file_name, char *extension)
{
	size_t	file_len;
	size_t	ext_len;
	size_t	i;

	if (!file_name || !extension)
		return (0);
	file_len = ft_strlen(file_name);
	ext_len = ft_strlen(extension);
	if (file_len < ext_len + 2 || file_name[file_len - ext_len - 1] != '.')
		return (0);
	i = 0;
	while (i < ext_len)
	{
		if (file_name[file_len - ext_len + i] != extension[i])
			return (0);
		i++;
	}
	return (1);
}

int	count_appearances(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_split_len(char **split)
{
	int	len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Get TRGB color */
int	get_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
