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
//# define SPRITE 2 // only bonus?
# define OUT 3

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
	//int	s_fd;
	int		floor_color;
	int		ceil_color;
	int		**map;
	t_pair	*pos;
	t_pair	*dir;
}				t_cub;

typedef enum e_error_code {
	ERRNO = 1,
	WRONG_ARGC,
	WRONG_FILE_EXT,
	FILE_INEXISTENT
}			t_error_code;

/* PARSER */
int		has_right_file_ext(char *str);
int		check_args(int ac, char **av);
t_cub	init_cub(void);

/* GAMEOVER - Error management */
void	error_message(t_error_code error_code);
int		error_and_return(t_error_code error_code, int return_value);

/* SHUT DOWN - Freeing and exiting */

#endif