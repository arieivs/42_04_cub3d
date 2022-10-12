#include "cub.h"

int	get_t(int trgb)
{
	return ((trgb >> 24) & 255);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 255);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 255);
}

int	get_b(int trgb)
{
	return (trgb & 255);
}
