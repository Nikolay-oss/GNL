/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:24:53 by dkenchur          #+#    #+#             */
/*   Updated: 2020/11/16 22:15:30 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

/*int main()
{
 	char *line;
 	int fd1 = open("file1.txt", O_RDONLY);
 	int fd2 = open("1_newline", O_RDONLY);
 	int fd3 = open("4_newlines", O_RDONLY);
 	int i = 0;

 	while (i < 5)
 	{
 		printf("gnl -> %d\n", get_next_line(fd1, &line));
 		printf("|%s|\n", line);
 		free(line);
 		get_next_line(fd2, &line);
 		printf("||%s||\n", line);
 		free(line);
 		get_next_line(fd3, &line);
 		printf("|||%s|||\n", line);
 		free(line);
 		i++;
 	}
}*/

int main()
{
	char *line;
	int fd = open("file1.txt", O_RDONLY);
	int fd1 = open("1_newline", O_RDONLY);
	int fd2 = open("4_newlines", O_RDONLY);
//	int fd3 = open("alphabet", O_RDONLY);
	int res;
	int i;
	
	i = 0;
	while (i < 5)
	{
		res = get_next_line(fd, &line);
		printf("<%d>\n", res);
		printf("|%s|\n", line);
		free(line);
		i++;
	}
	// printf("<%d>\n", res);
	// printf("|%s|\n", line);
	// free(line);
	close(fd);
	printf("===================================\n");
	while ((res = get_next_line(fd1, &line)) > 0)
	{
		printf("<%d>\n", res);
		printf("|%s|\n", line);
		free(line);
	}
	printf("<%d>\n", res);
	printf("|%s|\n", line);
	free(line);
	close(fd1);
	printf("===============================\n");
	while ((res = get_next_line(fd2, &line)) > 0)
	{
		printf("<%d>\n", res);
		printf("|%s|\n", line);
		free(line);
	}
	printf("<%d>\n", res);
	printf("|%s|\n", line);
	free(line);
	close(fd2);
}
