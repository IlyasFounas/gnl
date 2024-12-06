/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:03:06 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/06 11:24:47 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_ult(char *s)
{
	size_t i;
    
    i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dest;

	len_dest = ft_strlen_ult(dst);
	i = 0;
	if (size <= len_dest)
	{
		return (ft_strlen_ult((char *)src) + size);
	}
	if (size > 0)
	{
		while (src[i] && i < size - 1 - len_dest)
		{
			dst[len_dest + i] = src[i];
			i++;
		}
		dst[len_dest + i] = '\0';
	}
	return (ft_strlen_ult((char *)src) + len_dest);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (s == NULL)
		return (0);
	if ((size_t)start >= ft_strlen_ult((char *)s) && s != NULL)
	{
		dst = malloc(1);
		return (dst);
	}
	if (len >= ft_strlen_ult((char *)s + start))
		len = ft_strlen_ult((char *)s + start);
	dst = malloc(len + 1);
	if (dst == NULL)
		return (0);
	ft_strlcpy(dst, s + start, len + 1);
	return (dst);
}

