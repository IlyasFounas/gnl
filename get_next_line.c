/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:42:29 by ifounas           #+#    #+#             */
/*   Updated: 2024/11/27 17:29:06 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
    size_t i;
    char c[BUFFER_SIZE + 1];
	char *s;
    
    i = 0;
    read(fd, c, BUFFER_SIZE);
    s = malloc((ft_strlen_ult(c))*sizeof(char));
    while (i < ft_strlen_ult(c))
    {
        s[i] = c[i];
        i++;
    }
    s[i] = '\0';
    return (s);
}