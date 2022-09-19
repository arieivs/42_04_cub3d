#include "cub.h"

int	main(int ac, char **av)
{
	t_cub	cub;
	int		map_fd;

	if ((map_fd = check_args(ac, av)) == -1)
		return (1);
	cub = init_cub();
	check_map(map_fd, &cub);
  print_cub(&cub);
  free_cub(&cub); // just for now
	//init_mlx(&cub);
	//mlx_mouse_hook(cub.window, mouse_hook, &cub);
	//mlx_key_hook(cub.window, key_hook, &cub);
	// RENDER CUB
	//mlx_loop(cub.mlx);
	//graceful_exit(&cub); // only on key_hook - here it doesn't work
	return (0);
}
