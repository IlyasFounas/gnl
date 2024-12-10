/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:43:12 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/10 10:34:42 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>

char	*get_next_line(int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(char const *s, int c);
char	*ft_strjoin(char *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif