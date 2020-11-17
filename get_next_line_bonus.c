#include "get_next_line_bonus.h"

int	check_remainder(char **remainder, char **line)
{
	char	*current;
	char	*p_n;

	if (!*remainder)
		return (0);
	if ((p_n = ft_strchr(*remainder, '\n')))
	{
		current = *line;
		*line = ft_strndup(*remainder);
		free(current);
		current = *remainder;
		*remainder = ft_strdup(++p_n);
		free(current);
		return (1);
	}
	else
	{
		current = *line;
		*line = ft_strdup(*remainder);
		free(current);
		free(*remainder);
		*remainder = NULL;
	}
	return (0);
}

int	get_line(int fd, char **line, char **remainder, char **buf)
{
	int	res;
	char	*current;
	int	isexit;

	isexit = 1;
	while (isexit && (res = read(fd, *buf, BUFFER_SIZE)))
	{
		*(*buf + res) = '\0';
		if ((current = ft_strchr(*buf, '\n')))
		{
			*current = '\0';
			if (!(*remainder = ft_strdup(++current)))
				return (-1);
			isexit = 0;
		}
		current = *line;
		*line = ft_strjoin(*line, *buf);
		free(current);
		if (!*line)
			return (-1);
	}
	free(*buf);
	return (res);
}

int	get_next_line(int fd, char **line)
{
	static	char	*remainder[1000];
	int		res;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!(*line = ft_strdup("")) || !(buf = (char*)malloc(BUFFER_SIZE + 1)))
		return (-1);
	if ((res = check_remainder(&remainder[fd], line)) > 0)
		return (1);
	else if (res == -1)
		return (-1);
	if ((res = get_line(fd, line, &remainder[fd], &buf)) < 0)
		return (-1);
	return (res > 0 ? 1 : 0);
}
