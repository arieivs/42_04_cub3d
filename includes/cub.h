#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "mlx.h"
# include "libft.h"

# define WIDTH 1920
# define HEIGHT 1080
# define IN 0
# define WALL 1
# define OUT 2

typedef struct s_pair {
	double	x;
	double	y;
}				t_pair;

typedef struct s_cub {
	/* minilibx */
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	/* parsing map */
	int		no_fd;
	int		so_fd;
	int		we_fd;
	int		ea_fd;
	int		floor_color;
	int		ceil_color;
	int		**map;
	t_pair	*pos;
	t_pair	*dir;
	t_pair	*proj_plane;
}				t_cub;

typedef enum e_error_code {
	ERRNO = 1,
	WRONG_ARGC,
	WRONG_FILE_EXT,
	FILE_INEXISTENT,
	MAP_INCORRECT
}			t_error_code;

typedef struct s_parse_info {
	char	*buff;
	int		ret;
	int		line_nb;
	int		is_floor_color_set;
	int		is_ceil_color_set;
	char	**line_content;
}				t_parse_info;

/* PARSER */
int		has_right_file_ext(char *str);
int		check_args(int ac, char **av);
t_cub	init_cub(void);
int		check_map(int map_fd, t_cub	*cub);
void	init_mlx(t_cub *cub); // should go elsewhere

/* GAMEOVER - Error management */
void	error_message(t_error_code error_code);
int		error_and_return(t_error_code error_code, int return_value);
void	error_and_exit(t_error_code error_code, t_cub *cub);
void	*calloc_or_exit(size_t size, int count, t_cub *cub);

/* SHUT DOWN - Freeing and exiting */
void	free_cub(t_cub *cub);
void	graceful_exit(t_cub *cub);

#endif