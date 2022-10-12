#include "cub.h"

/* Checks if line is empty or only filled by whitespaces */
int	line_is_empty(char *line)
{
	int	i;

	if (!line)
		return (0);
	if (ft_strlen(line) == 0)
		return (1);
	i = 0;
	while (line[i])
	{
		if (!(line[i] >= 9 && line[i] <= 13) && line[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

/* Replaces 1 tab for 4 spaces */
char	*replace_tab_with_spaces(char *line)
{
	int		tab_nb;
	char	*repl;
	int		i;
	int		j;

	tab_nb = count_appearances(line, '\t');
	if (!tab_nb)
		return (line);
	repl = calloc_or_exit(sizeof(char), ft_strlen(line) + tab_nb * 3 + 1);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\t' && line[i++])
		{
			repl[j++] = ' ';
			repl[j++] = ' ';
			repl[j++] = ' ';
			repl[j++] = ' ';
		}
		else
			repl[j++] = line[i++];
	}
	free(line);
	return (repl);
}
