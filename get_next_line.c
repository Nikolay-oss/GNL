#include "get_next_line.h"
#include <stdio.h>

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
		//printf("start while\n");
		*(*buf + res) = '\0';
		//printf("buf good\n");
		if ((current = ft_strchr(*buf, '\n')))
		{
			//printf("find \\n\n");
			*current = '\0';
			//printf("nu ne\n");
			if (!(*remainder = ft_strdup(++current)))
				return (-1);
			isexit = 0;
		}
		//printf("work with line\n");
		current = *line;
		*line = ft_strjoin(*line, *buf);
		//printf("mb strjoin\n");
		free(current);
		//printf("mb free\n");
		if (!*line)
			return (-1);
		//printf("|%s|\n", *line);
	}
	free(*buf);
	return (res);
}

int	get_next_line(int fd, char **line)
{
	static	char	*remainder = NULL;
	char		*current;
	int		res;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!(*line = ft_strdup("")) || !(buf = (char*)malloc(BUFFER_SIZE + 1)))
		return (-1);
	if (check_remainder(&remainder, line))
		return (1);
	//printf("SEGA NO TUT\n");
	if ((res = get_line(fd, line, &remainder, &buf)) < 0)
		return (-1);
	return (res > 0 ? 1 : 0);
}
