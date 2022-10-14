#include "cub.h"

void	print_cub(t_cub *cub)
{
	int	i;
	int	j;

	printf("\n***	🎨 CUB 🍻	***\n\n");
	printf("Floor color: #%X%X%X%X or rgb(%d, %d, %d)\n", get_t(cub->f_color),
		get_r(cub->f_color), get_g(cub->f_color), get_b(cub->f_color),
		get_r(cub->f_color), get_g(cub->f_color), get_b(cub->f_color));
	printf("Ceiling color: #%X%X%X%X or rgb(%d, %d, %d)\n", get_t(cub->c_color),
		get_r(cub->c_color), get_g(cub->c_color), get_b(cub->c_color),
		get_r(cub->c_color), get_g(cub->c_color), get_b(cub->c_color));
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

void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		printf("%s ", split[i]);
		i++;
	}
	printf("\n");
}
