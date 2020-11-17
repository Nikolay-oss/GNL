#include "get_next_line.h"

int	copy_to_line(char *str, char **line)
{
	char	*current;

	current = *line;
	*line = ft_strjoin(*line, str);
	free(current);
	if (!*line)
		return (0);
	return (1);
}

int	check_remainder(char **remainder, char **line)
{
	char	*current;
	char	*p_n;

	if (!*remainder)
		return (0);
	if ((p_n = ft_strchr(*remainder, '\n')))
	{
		*p_n = '\0';
		if (!copy_to_line(*remainder, line))
			return (-1);
		current = *remainder;
		*remainder = ft_strdup(++p_n);
		free(current);
		return (1);
	}
	else
	{
		if (!copy_to_line(*remainder, line))
			return (-1);
		free(*remainder);
		*remainder = NULL;
	}
	return (0);
}

int	get_line(int fd, char **line, char **remainder)
{
	int	res;
	char	*current;
	int	isexit;
	char	*buf;

	if (!(buf = (char*)malloc(BUFFER_SIZE + 1)))
		return (-1);
	isexit = 1;
	while (isexit && (res = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		*(buf + res) = '\0';
		if ((current = ft_strchr(buf, '\n')))
		{
			*current = '\0';
			if (!(*remainder = ft_strdup(++current)))
				return (-1);
			isexit = 0;
		}
		if (!copy_to_line(buf, line))
			return (-1);
	}
	free(buf);
	if (!isexit && res > 0)
		return (1);
	return (res == -1 ? -1 : 0);
}

int	get_next_line(int fd, char **line)
{
	static	char	*remainder;
	int		res;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!(*line = ft_strdup("")))
		return (-1);
	if ((res = check_remainder(&remainder, line)) > 0)
		return (1);
	else if (res == -1)
		return (-1);
	if ((res = get_line(fd, line, &remainder)) < 0)
		return (-1);
	return (res);
}
