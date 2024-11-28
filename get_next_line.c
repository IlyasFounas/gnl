/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:42:29 by ifounas           #+#    #+#             */
/*   Updated: 2024/11/28 18:23:34 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static size_t i;
	static size_t i_cpy = 0;
	static size_t read_counter = 0;
	static char c[BUFFER_SIZE];
	char *s;
    char *s2;
    char *s3;
	size_t j;

	j = 0;
	if (i == read_counter - 1 || i_cpy >= 1)
    {
        read_counter = read(fd, c, BUFFER_SIZE);
        i = 0;
        i_cpy = 0;
    }
    while (i < read_counter - 1)
	{
       
		s = malloc((ft_strlen_ult(c + i)) * sizeof(char));
		if (s == NULL)
			return (NULL);
        if (i != 0 && c[i + 1] == '\n')
        {
            s[j] = c[i];
            i += 2;
        }
		while (j < ft_strlen_ult(c + i))
		{
			s[j] = c[i + j];
			j++;
		}
        s[j] = '\0';
		i += ft_strlen_ult(s) - 1;
		if (i != 0 && i == read_counter - 1 && c[i + j] != '\n')
        {
            read_counter = read(fd, c, BUFFER_SIZE);
            i = 0;
            s2 = malloc(ft_strlen_ult(c + i));
            if (s2 == NULL)
                return (NULL);
            ft_strlcpy(s2, c, ft_strlen_ult(c + i)+1);
            s3 = malloc(ft_strlen_ult(c + i));
            if (s3 == NULL)
                return (NULL);
            s3 = ft_strjoin(s, s2);
            free(s);
            free(s2);
            i_cpy = 1;
            return(s3);
        }
		return (s);
	}
	return ("\0");
}
