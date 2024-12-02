/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:42:29 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/02 22:56:50 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"

char *is_new_line(char *s, char *c, int fd, size_t read_counter)
{
    char *tmp;
    char *tmp2;
    size_t i = 0;
    
    if (ft_strlen_ult(s) == read_counter)
        read_counter = read(fd, c, BUFFER_SIZE);
    else
        return (s);
    while (c[i] != '\n' && i < read_counter)
        i++;
    tmp = malloc(ft_strlen_ult(s) + 1);
    ft_strlcpy(tmp,s,ft_strlen_ult(s)+1);
    tmp2 = ft_strjoin(tmp, c);
    free(tmp);
    free(s);
    printf("%zu t%ct",i, c[i]);
    if (c[i] != '\n')
        printf("AHAHAHAHA");
    return (tmp2);
}

char	*get_next_line(int fd)
{
	static size_t	i;
	static size_t	read_counter;
    static char    c[BUFFER_SIZE];
    char    *s;
    char    *s_cpy;
    
    if (i == read_counter)
    {
        read_counter = read(fd, c, BUFFER_SIZE);
        i = 0;
    }
    s = malloc(read_counter +  1);
    if (!s)
        return (NULL);
    ft_strlcpy(s, c, read_counter + 1);
    i += ft_strlen_ult(s);
    s_cpy = is_new_line(s, c , fd, read_counter);
    return (s_cpy);
    




	/*
    stqtic size_t   i;
    static size_t	read_counter = 0;
	static char		c[BUFFER_SIZE];

    
    
	char			*s;
	char			*s2;
	char			*s3;
	size_t			j;
    
	j = 0;
	if (i == read_counter - 1 || i == read_counter)
	{
		read_counter = read(fd, c, BUFFER_SIZE);
		i = 0;
	}
	while (i < read_counter - 1)
	{
		s = malloc((ft_strlen_ult(c + i)) * sizeof(char));
		if (s == NULL)
			return (NULL);
		// jump the \n, to continuing the fill of the string
		if (i != 0 && c[i + 1] == '\n')
		{
			s[j] = c[i];
			i += 2;
		}
        //printf("val %zu %zu", ft_strlen_ult(c + i), j);
		// fill the string we will return
		while (j < ft_strlen_ult(c + i))
		{
			s[j] = c[i + j];
			j++;
		}
       
		s[j] = '\0';
        
		i += ft_strlen_ult(s) - 1;
        //printf("val %zu, %c", i, c[i + j]);
		// when the string end before the end of the line
		if (i != 0 && i == read_counter - 1 && c[i + j] != '\n')
		{
			i = 0;
			while (c[i] != '\n')
			{
				read_counter = read(fd, c, BUFFER_SIZE);
				// end of file
				if (read_counter == 0)
					return (s);
				s2 = malloc(ft_strlen_ult(c + i));
				if (s2 == NULL)
					return (NULL);
				ft_strlcpy(s2, c, ft_strlen_ult(c + i) + 1);
				s3 = malloc(ft_strlen_ult(c + i));
				if (s3 == NULL)
					return (NULL);
				s3 = ft_strjoin(s, s2);
				i = ft_strlen_ult(s2);
				free(s);
				free(s2);
			}
			i++;
			return (s3);
		}
        return (s);
	}
	return ("(NULL)"); */
    
}
