# include "cub.h"

int	ft_split_len(char **split)
{
	int	len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}
