#include "cub.h"

void	print_cub(t_cub *cub)
{
	int	i;
	int	j;

	printf("\n***	🎨 CUB 🍻	***\n\n");
	printf("NO fd: %d, SO fd: %d, WE fd: %d, EA fd: %d\n",
		cub->no_fd, cub->so_fd, cub->we_fd, cub->ea_fd);
	printf("Floor color: #%X%X%X%X or rgb(%d, %d, %d)\n", get_t(cub->floor_color),
		get_r(cub->floor_color), get_g(cub->floor_color), get_b(cub->floor_color),
		get_r(cub->floor_color), get_g(cub->floor_color), get_b(cub->floor_color));
	printf("Ceiling color: #%X%X%X%X or rgb(%d, %d, %d)\n", get_t(cub->ceil_color),
		get_r(cub->ceil_color), get_g(cub->ceil_color), get_b(cub->ceil_color),
		get_r(cub->ceil_color), get_g(cub->ceil_color), get_b(cub->ceil_color));
	printf("\n");
	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (j < cub->map_width)
			printf("%d", cub->map[i][j++]);
		printf("\n");
		i++;
	}
	printf("\n");
}
