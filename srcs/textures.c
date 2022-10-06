#include "cub.h"

void	init_textures(t_cub *cub)
{
	cub->walls.no_tex = (t_img *)calloc_or_exit(sizeof(t_img), 1, cub);
	cub->walls.no_tex->width = ASSET_SIZE;
	cub->walls.no_tex->height = ASSET_SIZE;
	cub->walls.no_tex->img_ptr = mlx_xpm_file_to_image(cub->mlx, cub->walls.no_path, &(cub->walls.no_tex->width), &(cub->walls.no_tex->height));

	cub->walls.so_tex = (t_img *)calloc_or_exit(sizeof(t_img), 1, cub);
	cub->walls.so_tex->width = ASSET_SIZE;
	cub->walls.so_tex->height = ASSET_SIZE;
	cub->walls.so_tex->img_ptr = mlx_xpm_file_to_image(cub->mlx, cub->walls.no_path, &(cub->walls.so_tex->width), &(cub->walls.so_tex->height));
	
	cub->walls.we_tex = (t_img *)calloc_or_exit(sizeof(t_img), 1, cub);
	cub->walls.we_tex->width = ASSET_SIZE;
	cub->walls.we_tex->height = ASSET_SIZE;
	cub->walls.we_tex->img_ptr = mlx_xpm_file_to_image(cub->mlx, cub->walls.no_path, &(cub->walls.we_tex->width), &(cub->walls.we_tex->height));

	cub->walls.ea_tex = (t_img *)calloc_or_exit(sizeof(t_img), 1, cub);
	cub->walls.ea_tex->width = ASSET_SIZE;
	cub->walls.ea_tex->height = ASSET_SIZE;
	cub->walls.ea_tex->img_ptr = mlx_xpm_file_to_image(cub->mlx, cub->walls.no_path, &(cub->walls.ea_tex->width), &(cub->walls.ea_tex->height));
}