#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Struct for passing into keypress functions
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
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	/* parsing map */
	int		    no_fd;
	int		    so_fd;
	int		    we_fd;
	int		    ea_fd;
	int		    floor_color;
	int		    ceil_color;
	int		    **map;
	
    // hendrik
    t_pair_d	    *pos;
	t_pair_d	    *dir;
	t_pair_d	    *proj_plane;

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
    unsigned int    color;      // maybe remove some of these...

}				t_cub;