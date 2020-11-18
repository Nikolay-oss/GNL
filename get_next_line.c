/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:35:22 by dkenchur          #+#    #+#             */
/*   Updated: 2020/11/18 13:05:28 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int		copy_to_line(char **str, char **line)
{
	char	*current;

	current = *line;
	*line = ft_strjoin(*line, *str);
	free(current);
	if (!*line)
	{
		free(*str);
		return (0);
	}
	return (1);
}

static	int		check_remainder(char **remainder, char **line)
{
	char	*current;
	char	*p_n;

	if (!*remainder)
		return (0);
	if ((p_n = ft_strchr(*remainder, '\n')))
	{
		*p_n = '\0';
		if (!copy_to_line(remainder, line))
			return (-1);
		current = *remainder;
		*remainder = ft_strdup(++p_n);
		free(current);
		return (1);
	}
	else
	{
		if (!copy_to_line(remainder, line))
			return (-1);
		free(*remainder);
		*remainder = NULL;
	}
	return (0);
}

static	int		get_line(int fd, char **line, char **remainder, char **buf)
{
	int		res;
	char	*current;
	int		isexit;

	isexit = 1;
	while (isexit && (res = read(fd, *buf, BUFFER_SIZE)) > 0)
	{
		*(*buf + res) = '\0';
		if ((current = ft_strchr(*buf, '\n')))
		{
			*current = '\0';
			if (!(*remainder = ft_strdup(++current)))
			{
				free(*buf);
				return (-1);
			}
			isexit = 0;
		}
		if (!copy_to_line(buf, line))
			return (-1);
	}
	free(*buf);
	if (!isexit && res > 0)
		return (1);
	return (res == -1 ? -1 : 0);
}

int				get_next_line(int fd, char **line)
{
	static	char	*remainder;
	int				res;
	char			*buf;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!(*line = ft_strdup("")))
		return (-1);
	if ((res = check_remainder(&remainder, line)) > 0)
		return (1);
	else if (res == -1)
		return (-1);
	if (!(buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if ((res = get_line(fd, line, &remainder, &buf)) < 0)
		return (-1);
	return (res);
}
