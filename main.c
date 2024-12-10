/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:38:00 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/10 16:45:17 by ifounas          ###   ########.fr       */
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
	while (i < 5)
	{
		s = get_next_line(fd);
		if (s)
		{
			printf("%s", s);
			free(s);
		}
		else
			printf("%s", s);
		i++;
	}
	close(fd);
}
