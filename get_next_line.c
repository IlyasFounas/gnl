/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:42:29 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/02 18:10:54 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static size_t	i;
	size_t	i_cpy = i;
	size_t	read_counter;
	size_t	j = 0;
    char    *s;
    char    *s2;
    char    *s3;
    char    c[BUFFER_SIZE];

    if (i == 0)
        read_counter = read(fd, c, BUFFER_SIZE);
    while (i_cpy >= 0)
    {
        s = malloc((ft_strlen_ult(c)));
        if (!s)
            return (NULL);
        while (j < read_counter && c[j] != '\n')
        {
            s[j] = c[j];
            j++;
        }
        s[j] = '\0';
        if (j == read_counter && c[j] != '\n')
        {
/*             while (1)
            {
                read_counter = read(fd, c, BUFFER_SIZE);
                s2 = malloc(ft_strlen_ult(c));
                if (!s2)
                    return (NULL);
                ft_strlcpy(s2,c,ft_strlen_ult(c));
                s3 = ft_strjoin(s, s2);
                free(s);
                s = malloc(ft_strlen_ult(s3));
                if (!s)
                    return (NULL);
                ft_strlcpy(s,s3,ft_strlen_ult(s3));
                printf("val s3: %s", s3);
                if (c[ft_strlen_ult(s2) + 1] == '\n')
                {
                    free(s2);
                    free(s3);
                    break ;
                }
                
            } */
            read_counter = read(fd, c, BUFFER_SIZE);
            s2 = malloc(ft_strlen_ult(c));
            if (!s2)
                return (NULL);
            ft_strlcpy(s2,c,ft_strlen_ult(c));
            s3 = ft_strjoin(s, s2);
            free(s);
            s = malloc(ft_strlen_ult(s3));
            if (!s)
                return (NULL);
            ft_strlcpy(s,s3,ft_strlen_ult(s3));
            free(s2);
            free(s3);
        }
        if (i_cpy == 0)
        {
            i++;
            return (s);
        }
        i_cpy--;
        free(s);
    }
    return ("(NULL)");
	/*static size_t	read_counter = 0;
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
