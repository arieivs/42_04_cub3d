#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define WIDTH 1600
# define HEIGHT 900
# define IN 0
# define WALL 1
# define OUT 2

// Macros for testing
# define mapWidth 24
# define mapHeight 24

typedef struct s_pair_d {
	double	x;
	double	y;
}				t_pair_d;

typedef struct s_pair_i {
	int	x;
	int	y;
}				t_pair_i;

typedef struct s_cub {
	/* minilibx */
	void			*mlx;
	void			*window;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	/* parsing map */
	int				no_fd;
	int				so_fd;
	int				we_fd;
	int				ea_fd;
	int				floor_color;
	int				ceil_color;
	int				**map;
	t_pair_d		*pos;
	t_pair_d		*dir;
	t_pair_d		*proj_plane;
	/* raycasting */
    double          camera_x;
    t_pair_d        *ray_dir;
    t_pair_i        *map_pos;
    t_pair_d        *side_dist;
    t_pair_d        *delta_dist;
    double          perp_wall_dist;
    t_pair_i        *step;
    int             hit;
    int             side;
    int             line_height;
    int             draw_start;
    int             draw_end;
}				t_cub;

typedef enum e_error_code {
	ERRNO = 1,
	WRONG_ARGC,
	WRONG_FILE_EXT,
	FILE_INEXISTENT,
	MAP_INCORRECT,
	MLX_FAILURE
}			t_error_code;

/* PARSER */
int		has_right_file_ext(char *str);
int		check_args(int ac, char **av);
t_cub	init_cub(void);
int		check_map(int map_fd, t_cub	*cub);
void	init_mlx(t_cub *cub); // should go elsewhere

/* RAYCASTING */
void	initialize_map_pos(t_cub *cub);
void	set_ray_dir(t_cub *cub);
void	set_delta_dist(t_cub *cub);
void	initialize_raycasting(t_cub *cub, int x);
void	free_raycasting_vars(t_cub *cub);
void	calculate_step(t_cub *cub);
void	perform_dda(t_cub *cub);
void	calculate_dist(t_cub *cub);
void	raycast_loop(t_cub *cub);

/* DRAWING LINES TO THE SCREEN */
void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void	verLine(t_cub *cub, int x, unsigned int color);
int	set_pixel_color(t_cub *cub);
unsigned int	draw_pixels(t_cub *cub);

/* GAMEOVER - Error management */
void	error_message(t_error_code error_code);
int		error_and_return(t_error_code error_code, int return_value);
void	error_and_exit(t_error_code error_code, t_cub *cub);
void	*calloc_or_exit(size_t size, int count, t_cub *cub);

/* SHUT DOWN - Freeing and exiting */
void	free_cub(t_cub *cub);
void	graceful_exit(t_cub *cub);

/* WORLD MAP FOR TESTING */
extern int g_worldMap[mapWidth][mapHeight];

#endif