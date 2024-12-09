/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:06:05 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/09 18:15:25 by ifounas          ###   ########.fr       */
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
	
	res = ft_substr(buf, ft_strlen(buf, '\n'), ft_strlen(buf, 0));
	free(buf);
	return (res);
}

char	*ft_readline(int fd, char *buf)
{
	ssize_t	read_c;
	char	*line;

	read_c = -1;
	line = NULL;
	//printf("|%s|\n", buf);
	if (buf && buf[0] != '\0')
	{
		printf("|%s|", line);
		line = ft_strjoin(line, buf);
	}
	if (ft_strrchr(line, '\n') == 1)
	{
		return (line);
	}
	while (read_c != 0)
	{
		read_c = read(fd, buf, BUFFER_SIZE);
		if (read_c < 0)
		{
			free(line);
			return (NULL);
		}
		buf[read_c] = '\0';
		line = ft_strjoin(line, buf);
		if (ft_strrchr(line, '\n') == 1)
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char	*line;
	// int		i;

	// i = 0;
	if (!buf)
		buf = malloc(BUFFER_SIZE + 1);
	line = ft_readline(fd, buf);
	buf = ft_get_rest(buf);
	// while (res[i])
	// {
	// 	buf[i] = res[i];
	// 	i++;
	// }
	// while (i < BUFFER_SIZE)
	// {
	// 	buf[i] = '\0';
	// 	i++;
	// }
	return (line);
}

int	main(void)
{
	int i;
	char *s;
	int fd;

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
			printf("X%sX", s);
		i++;
	}
	close(fd);
}