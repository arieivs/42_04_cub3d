#include "cub.h"

int	has_right_file_ext(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 5)
		return (0);
	if (str[len - 4] == '.' && str[len - 3] == 'c' && str[len - 2] == 'u' &&
		str[len - 1] == 'b')
		return (1);
	return (0);
}

int	check_args(int ac, char **av)
{
	int	file_fd;

	if (ac != 2)
		return (error_and_return(WRONG_ARGC, -1));
	if (!has_right_file_ext(av[1]))
		return (error_and_return(WRONG_FILE_EXT, -1));
	file_fd = open(av[1], O_RDONLY);
	if (file_fd == -1)
		return (error_and_return(FILE_INEXISTENT, -1));
	return (file_fd);
}

t_cub	init_cub(void)
{
	t_cub	cub;

	cub.mlx = NULL;
	cub.window = NULL;
	cub.img = NULL;
	cub.addr = NULL;
	cub.no_fd = 0;
	cub.so_fd = 0;
	cub.we_fd = 0;
	cub.ea_fd = 0;
	cub.floor_color = 0;
	cub.ceil_color = 0;
	cub.map = NULL;
	cub.pos = calloc_or_exit(sizeof(t_pair *), 1, &cub);
	cub.pos->x = 0.0;
	cub.pos->y = 0.0;
	cub.dir = calloc_or_exit(sizeof(t_pair *), 1, &cub);
	cub.dir->x = 0.0;
	cub.dir->y = 0.0;
	cub.proj_plane = calloc_or_exit(sizeof(t_pair *), 1, &cub);
	cub.proj_plane->x = 0.0;
	cub.proj_plane->y = 0.0;
	return (cub);
}

int	check_map(int map_fd, t_cub	*cub)
{
	char	*buff;
	int		ret;
	int		line;

	(void)cub;
	printf("Checking map");
	while ((ret = get_next_line(map_fd, &buff)) > 0)
		printf("%d-%d: %s\n", ret, line++, buff);
	printf("%d-%d: %s\n", ret, line++, buff);
	if (ret == 0)
		printf("Reached EOF\n");
	if (ret == -1)
		printf("An Error occurred\n");
	close(map_fd);
	free(buff);
	return (0);
}

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Let's play!");
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel,
			&cub->line_length, &cub->endian);
}