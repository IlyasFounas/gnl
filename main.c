/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:38:00 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/05 14:42:16 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
 	int i = -1;
	char *s;
	int fd = open("text_simple.txt", O_RDONLY);
	while (++i < 4)
	{
		s = get_next_line(fd);
		printf("%s\n", s);
		free(s);
	}
	close(fd);

/* 
 	printf("////////////////////////////////////////////////////////////////////////////////////\n");
 	
	int j = -1;
	char *s2;
	int fd2 = open("test.txt", O_RDONLY);
	while (++j < 59)
	{
		s2 = get_next_line(fd2);
		printf("%s\n", s2);
		free(s2);
	}
	close(fd2); */
}