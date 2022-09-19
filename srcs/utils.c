# include "cub.h"

int has_right_file_ext(char *file_name, char *extension)
{
  size_t  file_len;
  size_t  ext_len;
  size_t  i;

  file_len = ft_strlen(file_name);
  ext_len = ft_strlen(extension);
  if (ext_len < 0 || file_len < ext_len + 2 ||
    file_name[file_len - ext_len - 1] != '.')
    return (0);
  i = 0;
  while (i < ext_len)
  {
    if (file_name[file_len - ext_len + i] != extension[i])
      return (0);
    i++;
  }
  return (1);
}

int	ft_split_len(char **split)
{
	int	len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}
