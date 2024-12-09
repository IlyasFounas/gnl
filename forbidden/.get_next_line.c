/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:42:29 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/06 10:48:25 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//This function allow more memory in tmp
char	*ft_realloc(char *tmp, char *c)
{
	char	*tmp2;

	tmp2 = malloc((ft_strlen_ult(tmp)) + (ft_strlen_ult(c) + 1));
	if (!tmp2)
		return (NULL);
	ft_strlcpy(tmp2, tmp, ft_strlen_ult(tmp) + 1);
	free(tmp);
	return (tmp2);
}
//like strjoin for the static string
char	*ft_str_tmp(char *s, char *c, int yes_or_no)
{
	char	*s_tmp;
	
	if (yes_or_no == 1)
	{
		s_tmp = malloc(ft_strlen_ult(s) + ft_strlen_ult(c) + 1);
		ft_strlcpy(s_tmp, &s[ft_strlen_ult(s) + 1] + 1, ft_strlen_ult(s) + 1);
		ft_strlcat(s_tmp, c, ft_strlen_ult(s) + ft_strlen_ult(c));
	}
	else
		s_tmp = ft_substr(&s[ft_strlen_ult(s) + 1] + 1, 0, ft_strlen_ult(s) + 1);
	printf("s_tmp|%s|", s_tmp);
	return (s_tmp);
}

//This function is endless ? 23 31 ... 30000
char	*get_next_line(int fd)
{
	char		c[BUFFER_SIZE + 1];
	char		*tmp;
	static char	*s;
	ssize_t		i;
	ssize_t		j;
	ssize_t		k;
	ssize_t		r_c;

	i = 0;
	j = 0;
	k = 0;
	r_c = 0;
	r_c = read(fd, c, BUFFER_SIZE);
	if (r_c < 0)
		return (NULL);
	c[r_c] = '\0';
	if (c[0] == '\0' && !s)
		return (NULL);
	if (s && s[0] != '\0')
	{
		tmp = malloc(ft_strlen_ult(c) + ft_strlen_ult(s) + 2);
		if (!tmp)
			return (NULL);
		while (s[k] && s[k] != '\n')
		{
			tmp[k] = s[k];
			k++;
		}
		tmp[k] = '\0';
		if (s[ft_strlen_ult(tmp)] == '\0')
		{
			free(s);
			s = malloc(1);
			s[0] = '\0';
		}
		if (s[k] == '\n' && s[k + 1] == '\0')
		{
			free(s);
			k = 0;
			s = malloc(ft_strlen_ult(c) + 1);
			while (k <= (ssize_t)ft_strlen_ult(c))
			{
				s[k] = c[k];
				k++;
			}
			s[k] = '\0';
			return (tmp);
		}
	}
	else
	{
		tmp = malloc(r_c + 1);
		if (!tmp)
			return (NULL);
		if (r_c == 0)
			tmp[0] = '\0';
	}
	if ((r_c == 0 && s && s[0] != '\0') || (s && s[k] == '\n' && s[k
			+ 1] != '\0'))
	{
		if (s && s[k] == '\n' && s[k + 1] != '\0')
		{
			s = ft_str_tmp(s, c, 1);
			return (tmp);
		}
		s = ft_str_tmp(s, c, 0);
	}
	if (r_c == 0 && s && s[0] == '\0' && tmp[0] == '\0')
		return (NULL);
	while (i < r_c)
	{
		tmp[k + j + i] = c[i];
		i++;
		if (i == r_c && c[r_c - 1] != '\n' && c[i] != '\n')
		{
			tmp[k + j + i] = '\0';
			r_c = read(fd, c, BUFFER_SIZE);
			c[r_c] = '\0';
			tmp = ft_realloc(tmp, c);
			i = 0;
			k = 0;
			j = ft_strlen_ult(tmp);
		}
		if (c[i - 1] == '\n')
		{
			s = ft_str_tmp(c, NULL, 0);
			printf("c_str|%s|\n", s);
			i += ft_strlen_ult(s);
			break ;
		}
	}
	tmp[i + j + k] = '\0';

	return (tmp);
}
