/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:42:29 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/04 12:55:42 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

char *ft_realloc(char *tmp, char *c)
{
    char *tmp2;
    //printf("[%zu||%zu||TMP:%s]",ft_strlen_ult(tmp), ft_strlen_ult(c),tmp);
    tmp2 = malloc(ft_strlen_ult(tmp) + ft_strlen_ult(c) +  1);
    if (!tmp2)
        return (NULL);
    ft_strlcpy(tmp2, tmp, ft_strlen_ult(tmp) + 1);
    free(tmp);
    return (tmp2);
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
    
    //printf("|%s|", s);
    r_c = read(fd, c, BUFFER_SIZE);
    if (s && s[0] != '\0')
    {
        tmp = malloc(ft_strlen_ult(c) + ft_strlen_ult(s));
        if (!tmp)
            return (NULL);
        while (s[k] && s[k] != '\n')
        {
            tmp[k] = s[k];
            k++;
        }
        tmp[k] = '\0';
        if (s[k] == '\n')
            k++;
    }
    else
    {
        tmp = malloc(ft_strlen_ult(c) + 1);
        if (!tmp)
            return (NULL);
    }
    if (r_c == 0 && tmp[0] != '\0')
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
        s[ft_strlen_ult(s)] = '\0';
    }
    while (i < r_c)
    {
        tmp[k + j + i] = c[i];
        i++;
        if (i == r_c && c[r_c - 1] != '\n' && c[i] != '\n')
        {
            tmp[k + j + i] = '\0';
            r_c = read(fd, c, BUFFER_SIZE);
            tmp = ft_realloc(tmp, c);
            i = 0;
            k = 0;
            j = ft_strlen_ult(tmp);
        }
        if (c[i] == '\n')
        {
            i++;
            s = malloc(ft_strlen_ult(c + i)+1);
            while (i+k < r_c)
            {
                s[k] = c[i+k];
                k++;
            }
            s[k] = '\0';
            i += k;
            //printf("[S:%s||TMP:%s]",s,tmp);
            break ;
        }
    }
    tmp[k + j + i] = '\0';
    return (tmp);
}
