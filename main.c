/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:38:00 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/11 18:14:39 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		i;
	char	*s;
	int		fd;

	i = 0;
	fd = open("text_simple.txt", O_RDONLY);
	s = get_next_line(fd);
	while (i < 3)
	{
		
		printf("%s", s);
		free(s);
		s = get_next_line(fd);
		i++;
	}
	close(fd);
}
