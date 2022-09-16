#include "cub.h"

/*typedef struct	s_vars {
	void	*mlx;
	void	*window;
}				t_vars;

int	key_hook(int keycode, t_vars *vars)
{
	(void)keycode;
	(void)vars;
	printf("Hello from key_hook!\n");
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
}*/

int	main(int ac, char **av)
{
	t_cub	cub;
	int		map_fd;

	if ((map_fd = check_args(ac, av)) == -1)
		return (1);
	cub = init_cub();
	if (!check_map(map_fd, &cub))
		return (1);
	init_mlx(&cub);
	//mlx_mouse_hook(cub.window, mouse_hook, &cub);
	//mlx_key_hook(cub.window, key_hook, &cub);
	// RENDER CUB
	//mlx_loop(cub.mlx);
	graceful_exit(&cub); // only on key_hook - here it doesn't work
	return (0);
}