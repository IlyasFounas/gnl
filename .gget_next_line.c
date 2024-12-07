/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:02:13 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/04 16:40:54 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// fill the static str to dont loose some characters in the .txt
char	*ft_filling_static_string(char *c, size_t read_c, char *str)
{
	char	*static_str;
	size_t	i;

	i = 0;
	if (ft_strlen_ult(c) == 0)
	{
		static_str = malloc(ft_strlen_ult(str + ft_strlen_ult(str) + 1));
		ft_strlcpy(static_str, str + ft_strlen_ult(str) + 1, ft_strlen_ult(str
				+ ft_strlen_ult(str) + 1) + 1);
		return (static_str);
	}
	while (c[i] != '\n')
		i++;
	i++;
	static_str = malloc((read_c - i) + 1);
	if (!static_str)
		return (NULL);
	ft_strlcpy(static_str, c + i, (read_c - i) + 1);
	return (static_str);
}

// concat a line with the new buffer (like a strjoin)
char	*ft_cat_line(char *str, int fd, char *c)
{
	char	*res;

	read(fd, c, BUFFER_SIZE);
	res = malloc(ft_strlen_ult(c) + ft_strlen_ult(str));
	if (!res)
		return (NULL);
	ft_strlcpy(res, str, ft_strlen_ult(str) + 1);
	ft_strlcat(res, c, ft_strlen_ult(c) + ft_strlen_ult(str) + 1);
	free(str);
	return (res);
}

// return a line
char	*ft_line(int fd, char *c)
{
	char	*str;
	char	*str_while;

	fd = fd;
	str = ft_substr(c, 0, ft_strlen_ult(c) + 1);
	if (!str)
		return (NULL);
	// while the line is not finished (we concat)
	while (c[BUFFER_SIZE - 1] != '\n' && c[BUFFER_SIZE - 1] != '\0')
	{
		str_while = ft_cat_line(str, fd, c);
		if (!str_while)
			return (NULL);
		str = malloc(ft_strlen_ult(str_while));
		if (!str)
			return (NULL);
		ft_strlcpy(str, str_while, ft_strlen_ult(str_while) + 1);
		//printf("&|%c|&\n", c[BUFFER_SIZE - 1]);
        if (c[BUFFER_SIZE - 1] == '\n' || c[BUFFER_SIZE - 1] == '\0')
        {
            read(fd, c, BUFFER_SIZE);
            return (str);
        }
            //printf("&|%c|&&|%s|&\n", c[BUFFER_SIZE - 1], str);
	}
	return (str);
}

// the static str is already fill so we cpy it in str
char	*ft_str_fill_static_str(char *static_str, char *c, int fd)
{
	char	*str;
	char	*str_line;

	str = malloc(ft_strlen_ult(static_str) + ft_strlen_ult(c));
	if (!str)
		return (NULL);
	ft_strlcpy(str, static_str, ft_strlen_ult(static_str) + 1);
	str_line = ft_line(fd, c);
	ft_strlcat(str, str_line, ft_strlen_ult(static_str) + ft_strlen_ult(c) + 1);
	free(str_line);
	return (str);
}

// return the next line of a .txt
char	*get_next_line(int fd)
{
	char		c[BUFFER_SIZE + 1];
	char		*str;
	static char	*static_str;
	size_t		read_c;

	if (static_str != NULL)
	{
		read_c = read(fd, c, BUFFER_SIZE);
		c[read_c] = '\0';
		if (read_c == 0 && ft_strlen_ult(static_str) <= 0)
			return (NULL);
		str = ft_str_fill_static_str(static_str, c, fd);
		if (ft_strlen_ult(c) > 0)
			free(static_str);
		static_str = ft_filling_static_string(c, read_c, static_str);
		return (str);
	}
	else
		read_c = read(fd, c, BUFFER_SIZE);
	if (read_c == 0)
		return (NULL);
	str = ft_line(fd, c);
    //printf("|str:%s||clen:%zu||reafd:%zu|\n",str, ft_strlen_ult(c) , read_c);
	if (ft_strlen_ult(c) < read_c)
		static_str = ft_filling_static_string(c, read_c, NULL);
	return (str);
}
