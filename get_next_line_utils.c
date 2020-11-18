/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:04:48 by dkenchur          #+#    #+#             */
/*   Updated: 2020/11/18 13:04:47 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*(s + count))
		count++;
	return (count);
}

char			*ft_strchr(const char *s, int c)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	str = (char*)s;
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == c)
			return (str + i);
		i++;
	}
	if (*(str + i) == c)
		return (str + i);
	return (NULL);
}

char			*ft_strdup(const char *s1)
{
	size_t	size;
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1);
	str = (char*)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (str);
	i = 0;
	while (i < size)
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	size;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	size = s1 ? ft_strlen(s1) : 0;
	size += s2 ? ft_strlen(s2) : 0;
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (str);
	i = 0;
	while (s1 && *s1)
	{
		*(str + i++) = *s1;
		s1++;
	}
	while (s2 && *s2)
	{
		*(str + i++) = *s2;
		s2++;
	}
	*(str + i) = '\0';
	return (str);
}
