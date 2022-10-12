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

/* window width and height
 * smaller screen: 1220x720
 * bigger screen: 1920x1080 (just some values we like)
 */
# define WIDTH 1220
# define HEIGHT 720
/* asset/texture size */
# define ASSET_SIZE 512
/* maximum map/navigator window fraction: 1/3 */
# define NAV_FRACT 3
/* pixeis per square of the map/navigator */
# define PIXEL_PER_SQUARE 12

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
#  define MOVE_SPEED 0.07
#  define ROT_SPEED 0.03
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
#  define MOVE_SPEED 0.025
#  define ROT_SPEED 0.005
# endif

/* ENUMS */
typedef enum e_map_code {
	IN = 0,
	WALL,
	OUT,
	PLAYER
}			t_map_code;

typedef enum e_dir_code {
	NO = 0,
	SO,
	WE,
	EA
}	t_dir_code;

typedef enum e_side_code {
	SIDE_X = 0,
	SIDE_Y
}	t_side_code;

typedef enum e_error_code {
	ERRNO = 1,
	WRONG_ARGC,
	WRONG_FILE_EXT,
	FILE_INEXISTENT,
	MAP_INCORRECT,
	MLX_FAILURE
}			t_error_code;

/* STRUCTS */
typedef struct s_pair_d {
	double	x;
	double	y;
}				t_pair_d;

typedef struct s_pair_i {
	int	x;
	int	y;
}				t_pair_i;

typedef struct s_img {
	void		*img_ptr;
	char		*addr;
	int			height;
	int			width;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_img;

typedef struct s_wall {
	char	*path;
	t_img	*tex;
}	t_wall;

typedef struct s_keys {
	int	w;
	int a;
	int s;
	int d;
	int up;
	int left;
	int down;
	int right;
}	t_keys;

typedef struct s_cub {
	/* minilibx */
	void		*mlx;
	void		*window;
	t_img		*img;
	/* parsing map */
	t_wall		walls[4];
	int			f_color;
	int			c_color;
	int			**map;
	int			map_height;
	int			map_width;
	t_pair_d	*pos;
	t_pair_d	*dir;
	t_pair_d	*proj_plane;
	/* raycasting */
	double		camera_x;
	t_pair_d	*ray_dir;
	t_pair_i	*map_pos;
	t_pair_d	*side_dist;
	t_pair_d	*delta_dist;
	double		perp_wall_dist;
	t_pair_i	*step;
	int			hit;
	t_side_code	side;
	/* textures */
	double		wall_x;
	t_pair_i	*texel;
	double		texel_step;
	double		texel_pos;
	/* drawing pixels */
	int			line_height;
	int			draw_start;
	int			draw_end;
	/* movement */
	t_keys		keys;
	/* draw navigator */
	t_img		*nav_img;
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

/* DEAL with user INPUT */
int		check_args(int ac, char **av);

/* *** INITIALIZERS *** */
/* INIT CUB */
t_pair_d		*init_pair_double(t_cub *cub);
t_pair_i		*init_pair_int(t_cub *cub);
t_cub			init_cub(void);
/* INIT PARSE */
t_parse_info	init_parse_info(void);
/* INIT MLX and everything that needs it */
void			init_mlx(t_cub *cub);

/* *** PARSER *** */
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

/* *** RAYCASTING *** */
/* PIXEL */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
/* RAYCAST */
void	initialize_raycasting(t_cub *cub, int x);
void	calculate_step(t_cub *cub);
void	perform_dda(t_cub *cub);
void	calculate_drawline(t_cub *cub);
void	raycast(t_cub *cub);
/* TEXTURES */
void			apply_textures(t_cub *cub, int x);
unsigned int	get_texture_color(t_img *texture, int pixel_x, int pixel_y);
/* NAVIGATOR */
void	draw_navigator(t_cub *cub);

/* *** HOOKS *** */
/* HOOKS */
int	update_display(t_cub *cub);
int	key_up(int keycode, t_cub *cub);
int	key_down(int keycode, t_cub *cub);
/* MOVEMENT */
void	move_forward(t_cub *cub, double edge, double move_speed);
void	move_backward(t_cub *cub, double edge, double move_speed);
void	move_right(t_cub *cub, double edge, double move_speed);
void	move_left(t_cub *cub, double edge, double move_speed);
/* ROTATE */
void	rotate_left(t_cub *cub, double rot_speed);
void	rotate_right(t_cub *cub, double rot_speed);

/* *** TERMINATE *** */
/* FREE MEMORY */
void	free_cub(t_cub *cub);
void	free_split(char **split);
void	free_parse_info(t_parse_info *parse_info);
/* GAMEOVER - Error management */
void	error_message(t_error_code error_code);
int		error_and_return(t_error_code error_code, int return_value);
void	error_and_exit(t_error_code error_code, t_cub *cub);
void	error_and_exit_from_parsing(t_error_code error_code, t_cub *cub,
			t_parse_info *parse_info, int map_fd);
void	*calloc_or_exit(size_t size, int count, t_cub *cub);
/* WINNER EXIT*/
void	graceful_exit(t_cub *cub);

/* UTILS */
int		has_right_file_ext(char *file_name, char *extension);
int		count_appearances(char *str, char c);
int		ft_split_len(char **split);
int		is_number(char *str);

/* Only for DEVelopment */
/* COLOR */
int		get_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
/* DEBUG */
void	print_cub(t_cub *cub);
/* FPS */
unsigned long long	get_time_micros(void);
void				display_fps(t_cub *cub);

#endif
