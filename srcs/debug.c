#include "cub.h"

void	print_cub(t_cub *cub)
{
	int	i;
	int	j;

	printf("\n***	🎨 CUB 🍻	***\n\n");
	// printf("NO fd: %d, SO fd: %d, WE fd: %d, EA fd: %d\n",
	// 	cub->walls.no_fd, cub->walls.so_fd, cub->walls.we_fd, cub->walls.ea_fd);
	printf("Floor color: #%X%X%X or rgb(%d, %d, %d)\n",
		get_r(cub->floor_color), get_g(cub->floor_color), get_b(cub->floor_color),
		get_r(cub->floor_color), get_g(cub->floor_color), get_b(cub->floor_color));
	printf("Ceiling color: #%X%X%X or rgb(%d, %d, %d)\n",
		get_r(cub->ceil_color), get_g(cub->ceil_color), get_b(cub->ceil_color),
		get_r(cub->ceil_color), get_g(cub->ceil_color), get_b(cub->ceil_color));
	printf("\n🗺  Map height %d x width %d\n", cub->map_height, cub->map_width);
	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (j < cub->map_width)
			printf("%d", cub->map[i][j++]);
		printf("\n");
		i++;
	}
	printf("\n😎 Player\n");
	printf("Position (x, y) = (%.2f, %.2f)\n", cub->pos->x, cub->pos->y);
	printf("Direction (x, y) = (%.2f, %.2f)\n", cub->dir->x, cub->dir->y);
	printf("\n");
}
