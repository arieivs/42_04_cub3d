#ifndef CUB_H
# define CUB_H

# include <unistd.h>

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

/* PARSER */
t_cub	init_cub(void);

#endif