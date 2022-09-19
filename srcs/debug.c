#include "cub.h"

void  print_cub(t_cub *cub)
{
  printf("\n***  🎨 CUB 🍻  ***\n");
  printf("NO fd: %d, SO fd: %d, WE fd: %d, EA fd: %d\n",
    cub->no_fd, cub->so_fd, cub->we_fd, cub->ea_fd);
  printf("Floor color: #%X%X%X%X or rgb(%d, %d, %d)\n", get_t(cub->floor_color),
    get_r(cub->floor_color), get_g(cub->floor_color), get_b(cub->floor_color),
    get_r(cub->floor_color), get_g(cub->floor_color), get_b(cub->floor_color));
  printf("Ceiling color: #%X%X%X%X or rgb(%d, %d, %d)\n", get_t(cub->ceil_color),
    get_r(cub->ceil_color), get_g(cub->ceil_color), get_b(cub->ceil_color),
    get_r(cub->ceil_color), get_g(cub->ceil_color), get_b(cub->ceil_color));
  printf("\n");
}
