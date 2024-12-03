/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:42:29 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/03 17:55:15 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_realloc(char *tmp, char *c)
{
    char *tmp2;

    tmp2 = malloc(ft_strlen_ult(tmp) + ft_strlen_ult(c) +  1);
    if (!tmp2)
        return (NULL);
    ft_strlcpy(tmp2, tmp, ft_strlen_ult(tmp) + 1);
    free(tmp);
    return (tmp2);
}

char *ft_static_str(char *c, size_t i, size_t j)
{
    char *s;
    if (c[i+1] != '\0' && c[i+1] != '\n')
    {
        i++;
        j = 0;
        s = malloc(ft_strlen_ult(c+i)+1);
        if (!s)
            return (NULL);
        while (c[i+j])
        {
            s[j] = c[i+j];
            j++;
        }
        s[j] = '\0';
    }
    else
        s = malloc(0);
    return (s);
}

char	*get_next_line(int fd)
{
    char c[BUFFER_SIZE + 1];
    char *tmp;
    char *s_tmp;
    static char *s;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t r_c = 0;
    
    r_c = read(fd, c, BUFFER_SIZE);
    
    if (s && s[0] != '\0')
    {
        tmp = malloc(ft_strlen_ult(c) + ft_strlen_ult(s) + 1);
        if (!tmp)
            return (NULL);
        while (s[k] && s[k] != '\n')
        {
            tmp[k] = s[k];
            k++;
        }
        if (s[k] == '\n')
            k++;
    }
    else
    {
        tmp = malloc(ft_strlen_ult(c) + 1);
        if (!tmp)
            return (NULL);
    }
    if (r_c == 0 )
    {
        if (!s && s[0] == '\0')
            return (NULL);
        
        s_tmp = ft_substr(&s[ft_strlen_ult(s)]+1, 0, ft_strlen_ult(s));
        free(s);
        s = malloc(ft_strlen_ult(s_tmp)+1);
        if (!s)
            return (NULL);
        ft_strlcpy(s, s_tmp, ft_strlen_ult(s_tmp)+1);
        free(s_tmp);
    }
    while (c[i] != '\n' && i < r_c)
    {
        tmp[k + j + i] = c[i];
        i++;
        if (i == r_c && c[r_c - 1] != '\n')
        {
            r_c = read(fd, c, BUFFER_SIZE);
            tmp = ft_realloc(tmp, c);
            i = 0;
            k = 0;
            j = ft_strlen_ult(tmp);
        }
    }
    tmp[k + j + i] = '\0';
    if (!s)
        s = ft_static_str(c, i, j);
    if (r_c == 0 && !tmp && tmp[0] != '\0')
        return (NULL);
    return (tmp);
}
 	/*
     
    static size_t   i;
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
	return ("(NULL)"); 
    
}*/

/* int	main(void)
{
	char *s;
	int fd = open("text_simple.txt", O_RDONLY);
	//int fd2 = open("test.txt", O_RDONLY);
	int i;
	
 	i = -1;
	while (++i < 4)
	{
		s = get_next_line(fd);
		printf("%s\n", s);
		free(s);
	}
 	printf("////////////////////////////////////////////////////////////////////////////////////\n");
 	i = -1;
	while (++i < 59)
	{
		s = get_next_line(fd2);
		printf("%s\n", s);
		free(s);
	}
	close(fd);
	//close(fd2);
} */
