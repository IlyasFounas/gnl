/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:03:06 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/02 16:49:33 by ifounas          ###   ########.fr       */
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
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;

	if (s1 == NULL || s2 == NULL)
		return (0);
	dst = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (dst == NULL)
		return (0);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, ft_strlen(dst) + ft_strlen(s2) + 1);
	return (dst);
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

	len_dest = ft_strlen(dst);
	i = 0;
	if (size <= len_dest)
	{
		return (ft_strlen(src) + size);
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
	return (ft_strlen(src) + len_dest);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}