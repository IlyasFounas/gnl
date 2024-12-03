/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:38:00 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/03 17:55:37 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	char *s;
	//int fd = open("text_simple.txt", O_RDONLY);
	int fd2 = open("test.txt", O_RDONLY);
	int i;
	
 	/* i = -1;
	while (++i < 5)
	{
		s = get_next_line(fd);
		printf("%s\n", s);
		free(s);
	}
 	printf("////////////////////////////////////////////////////////////////////////////////////\n");
 	 */i = -1;
	while (++i < 59)
	{
		s = get_next_line(fd2);
		printf("%s\n", s);
		free(s);
	}
	//close(fd);
	close(fd2);
}