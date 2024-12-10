/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:06:05 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/10 18:29:34 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strrchr(const char *s, int c)
{
	int	i;
	int	mark;

	i = 0;
	mark = 0;
	c = (char)c;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			mark = i;
		i++;
	}
	if (s[i] == c && s[i] == '\0')
		return (0);
	else if (mark > 0 || s[mark] == c)
		return (1);
	return (0);
}

char	*ft_get_rest(char *buf)
{
	char	*res;

	if (buf && buf[0] == '\0')
		return (NULL);
	res = ft_substr(buf, ft_strlen(buf, '\n'), ft_strlen(buf + ft_strlen(buf,
					'\n'), 0));
	return (res);
}

char	*ft_readline(int fd, char *buf)
{
	ssize_t	read_c;
	char	*line;

	read_c = -1;
	line = NULL;
	if (buf && buf[0] != '\0')
	{
		line = ft_strjoin(line, buf);
		if (!line)
		{
			return (NULL);
		}
	}
	if (ft_strrchr(line, '\n') == 1)
		return (line);
	while (read_c != 0)
	{
		read_c = read(fd, buf, BUFFER_SIZE);
		if (read_c == 0)
			return (line);
		if (read_c < 0)
			return (free(line), NULL);
		buf[read_c] = '\0';
		line = ft_strjoin(line, buf);
		if (ft_strrchr(line, '\n') == 1 || !line)
			break ;
	}
	if (read_c == 0)
		return (free(line), NULL);
	return (line);
}

void	ft_concat_buffer(char *buf, char *res)
{
	int			i;
	
	i = 0;
	while (res[i] != '\0')
	{
		buf[i] = res[i];
		i++;
	}
	while (i < BUFFER_SIZE)
	{
		buf[i] = '\0';
		i++;
	}
	free(res);
}

char	*get_next_line(int fd)
{
	char		*res;
	static char	buf[BUFFER_SIZE + 1];
	char		*line;

	line = ft_readline(fd, buf);
	res = ft_get_rest(buf);
	if (res)
		ft_concat_buffer(buf, res);
	return (line);
}
