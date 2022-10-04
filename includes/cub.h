#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include "mlx.h"
# include "libft.h"

# define WIDTH 960//1920
# define HEIGHT 720//1080

/* OS CHECK */
# ifdef APPLE
#  define ESC_KEY 53
#  define UP_KEY 126
#  define DOWN_KEY 125
#  define LEFT_KEY 123
#  define RIGHT_KEY 124
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
# else
#  define ESC_KEY 65307
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
# endif

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
	int				map_height;
	int				map_width;
	t_pair_d		*pos;
	t_pair_d		*dir;
	t_pair_d		*proj_plane;
	/* raycasting */
	double			camera_x;
	t_pair_d		*ray_dir;
	t_pair_i		*map_pos;
	t_pair_d		*side_dist;
	t_pair_d		*delta_dist;
	double			perp_wall_dist;
	t_pair_i		*step;
	int				hit;
	int				side;
	/* fps */
	unsigned long long	time;
	unsigned long long	old_time;
	double				curr_fps;
	double				prev_fps;
	int					fps_counter;
	/* drawing pixels */
	int				line_height;
	int				draw_start;
	int				draw_end;
	/*  */
}				t_cub;

typedef struct s_parse_info {
	char	*buff;
	int		ret;
	int		line_nb;
	char	*line_trimmed;
	char	**line_content;
	char	*prefix;
	int		prefix_len;
	char	**colors;
	int		*colors_rgb;
	int		is_floor_color_set;
	int		is_ceil_color_set;
	char	*file_name;
	int		line_nb_map_start;
	size_t	max_map_width;
	int		is_player_set;
}				t_parse_info;

typedef enum e_map_code {
	IN = 0,
	WALL,
	OUT,
	PLAYER
}			t_map_code;

typedef enum e_error_code {
	ERRNO = 1,
	WRONG_ARGC,
	WRONG_FILE_EXT,
	FILE_INEXISTENT,
	MAP_INCORRECT,
	MLX_FAILURE
}			t_error_code;

/* DEAL with user INPUT */
int		check_args(int ac, char **av);

/* INITIALIZERS */
t_cub			init_cub(void);
t_parse_info	init_parse_info(void);
void			init_mlx(t_cub *cub);

/* PARSER */
void	validate_map(int map_fd, char *map_name, t_cub	*cub);
void	validate_map_info(int map_fd, t_cub *cub, t_parse_info* parse_info);
/* PARSER COLOR and TEXTURE */
int		textures_colors_not_set(t_cub *cub, t_parse_info *parse_info);
int		texture_or_color_is_valid(t_cub *cub, t_parse_info	*parse_info);
/* PARSER MAP */
void	evaluate_map_size(int map_fd, t_cub *cub, t_parse_info* parse_info);
void	validate_map_grid(int map_fd, t_cub *cub, t_parse_info* parse_info);
/* PARSER UTILS */
int		line_is_empty(char *line);
char	*replace_tab_with_spaces(char *line, t_cub *cub);

/* COLOR */
int		get_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

/* DEBUG */
void	print_cub(t_cub *cub);

/* RAYCASTING */
void	initialize_raycasting(t_cub *cub, int x);
void	calculate_step(t_cub *cub);
void	perform_dda(t_cub *cub);
void	calculate_dist(t_cub *cub);
void	raycast(t_cub *cub);

/* DRAWING LINES TO THE SCREEN */
void			my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void			draw_verline(t_cub *cub, int x, unsigned int color);
int				set_pixel_color(t_cub *cub);
unsigned int	set_pixels(t_cub *cub);

/* FPS */
unsigned long long	get_time_micros(void);
int					display_fps(t_cub *cub);
char				*set_fps_string(char *str1, t_cub *cub, int mode);

/* HOOKING */
int	key_hook(int keycode, t_cub *cub);
/* MOVEMENT */
void	move_forward(t_cub *cub, double edge, double move_speed);
void	move_backward(t_cub *cub, double edge, double move_speed);
void	move_right(t_cub *cub, double edge, double move_speed);
void	move_left(t_cub *cub, double edge, double move_speed);
/* ROTATE */
void	rotate_left(t_cub *cub, double rot_speed);
void	rotate_right(t_cub *cub, double rot_speed);

/* FREE MEMORY */
void	free_cub(t_cub *cub);
void	free_split(char **split);
void	free_parse_info(t_parse_info *parse_info);
void	graceful_exit(t_cub *cub);

/* GAMEOVER - Error management */
void	error_message(t_error_code error_code);
int		error_and_return(t_error_code error_code, int return_value);
void	error_and_exit(t_error_code error_code, t_cub *cub);
void	error_and_exit_from_parsing(t_error_code error_code, t_cub *cub,
			t_parse_info *parse_info, int map_fd);
void	*calloc_or_exit(size_t size, int count, t_cub *cub);

/* UTILS */
int		has_right_file_ext(char *file_name, char *extension);
int		count_appearances(char *str, char c);
int		ft_split_len(char **split);
int		is_number(char *str);

#endif
