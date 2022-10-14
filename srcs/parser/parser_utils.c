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

/* REPLACE TAB w SPACES
 * Replaces 1 tab for 4 spaces - the usual configuration
 */
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

/* STR_REPLACE
 * replaces any character from a given set for another one.
 * used to replace all forms of white space for a space,
 * to simplify the parsing
 */
static int	belongs_to_set(char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strreplace(char *org, char *old_set, char new_set)
{
	char	*replaced;
	int		i;

	if (!org || !old_set)
		return (NULL);
	replaced = (char *)calloc_or_exit(sizeof(char), ft_strlen(org) + 1);
	i = 0;
	while (org[i])
	{
		if (belongs_to_set(old_set, org[i]))
			replaced[i] = new_set;
		else
			replaced[i] = org[i];
		i++;
	}
	return (replaced);
}

/* SPLIT PREFIX from CONTENT
 * note that ft_strlcpy returns the length of source, thus the end of line
 * if things go wrong, prefix and content will both be empty freeable strings
 * for prefix, i points to the start and j at end;
 * for content, j points to the start and i at end (it required less code)
 */
void	split_prefix_from_content(t_parse_info *parse_info)
{
	int	i;
	int	j;

	i = 0;
	while (parse_info->line[i] && parse_info->line[i] == ' ')
		i++;
	j = i;
	while (parse_info->line[j] && parse_info->line[j] != ' ')
		j++;
	parse_info->prefix = (char *)calloc_or_exit(sizeof(char), j - i + 1);
	parse_info->prefix_len = j - i;
	ft_strlcpy(parse_info->prefix, parse_info->line + i, j - i + 1);
	while (parse_info->line[j] && parse_info->line[j] == ' ')
		j++;
	i = ft_strlen(parse_info->line);
	while (parse_info->line[i - 1] && parse_info->line[i - 1] == ' ')
		i--;
	if (i < j)
	{
		parse_info->content = ft_strdup("");
		return ;
	}
	parse_info->content = (char *)calloc_or_exit(sizeof(char), i - j + 1);
	ft_strlcpy(parse_info->content, parse_info->line + j, i - j + 1);
}
