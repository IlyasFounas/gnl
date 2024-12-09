/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:26:57 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/09 17:03:17 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// read in the file
static ssize_t	ft_readline(int fd, t_list *ptr)
{
	ssize_t	read_count;
	t_list	*ptr_tmp;
	char	buf[BUFFER_SIZE + 1];
	char	*tmp_malloc;

	read_count = 1;
	read_count = read(fd, buf, BUFFER_SIZE);
	if (read_count <= 0)
		return (read_count);
	buf[read_count] = '\0';
	tmp_malloc = malloc(read_count + 1);
	if (!tmp_malloc)
		return (0);
	ft_strlcpy(tmp_malloc, buf, read_count + 1);
	ptr_tmp = ft_lstnew((void *)tmp_malloc);
	if (!ptr_tmp)
		return (-1);
	ft_lstadd_back(&ptr, ptr_tmp);
	return (read_count);
}

// read in the file while the line is finished
static char	*ft_readline_while(int fd, t_list *ptr)
{
	ssize_t	read_count;
	ssize_t	i;
	ssize_t	j;
	char	*str;
	char	*str_rest;
	char	*line;
	t_list	*current;

	i = 0;
	j = 1;
	line = NULL;
	read_count = ft_readline(fd, ptr);
	while (1)
	{
		ptr = ptr->next;
		str = (char *)ptr->content;
		str[read_count] = '\0';
		while (str[i] != '\n' && str[i] != '\0')
			i++;
		if (str[i] == '\n')
		{
			while (str[i + j] != '\0')
				j++;
			str_rest = malloc(j + 1);
			if (!str_rest)
				return (NULL);
			ft_strlcpy(str_rest, str + i + 1, j);
			line = malloc(i + 1);
			if (line)
			{
				ft_strlcpy(line, str, i + 2);
				current = ft_lstnew((void *)line);
				if (!current)
					return (NULL);
				free(ptr->content);
				ptr->content = current->content;
			}
			return (str_rest);
		}
		read_count = ft_readline(fd, ptr);
		if (read_count <= 0)
			return (NULL);
		i = 0;
		j = 1;
	}
	return (line);
}

// Join all the lists of ptr and return a char*
char	*ft_strjoin_structs(int fd, t_list *ptr_to_first, t_list *ptr, char *str_rest)
{
	t_list	*current;
	char	*line;
	char	*tmp;
	
	str_rest = ft_readline_while(fd, ptr);
	current = ptr_to_first->next;
	line = NULL;
	current = current->next;
	while (current)
	{
		if (current->content)
		{
			if (!line)
				line = ft_strdup((char *)current->content);
			else
			{
				tmp = ft_strjoin(line, (char *)current->content);
				free(line);
				line = tmp;
			}
		}
		current = current->next;
	}
	ptr_to_first->next = current;
	return (line);
}


// return the lst
char	*get_next_line(int fd)
{
	t_list	*ptr_to_first;
	t_list			*ptr;
	t_list			*ptr_last;
	ssize_t			read_count;
	static char		*str_rest;
	
	ptr_to_first = ft_lstnew(NULL);
	ptr = ft_lstnew(NULL);
	if (!ptr)
		return (NULL);
	ft_lstadd_back(&ptr_to_first, ptr);
	if (str_rest)
	{
		ft_lstadd_back(&ptr, ft_lstnew((void *)str_rest));
		free(str_rest);
	}
	read_count = ft_readline(fd, ptr);
	if (read_count <= 0)
		return (NULL);
	ptr_last = ptr;
	while (ptr_last->next)
		ptr_last = ptr_last->next;
	if (*(char *)ptr_last->content + BUFFER_SIZE - 1 == '\n'
		|| *(char *)ptr_last->content + BUFFER_SIZE - 1 == '\0')
		return (ptr_last->content);
	else
		return (ft_strjoin_structs(fd, ptr_to_first, ptr_last, str_rest));
}

/* char	*ft_strjoin_ult(t_list *new_list, t_list *ptr_first)
{
	t_list *tmp_list;
	ssize_t i = 0;
	ssize_t j = 0;*
	while (tmp_list)
	{
		if (tmp_list->content)
		{
			line = malloc((ft_strlen((char *)tmp_list->content)) + 1);
			ft_strlcpy(ft_strlen((char *)tmp_list->content) + 1);
			while (line[i] != '\n')
				i++;
			if (line[i + 1] != '\0')
			{
				while (line[j + i] != '\0')
					j++;
				rest_line = malloc(j + 1);
				ft_strlcpy(rest_line, line + i + 1, j + 1);
			}
			final_line = malloc(i + 1);
			ft_strlcpy(final_line, line, i + 1);
			free(line);
		}
		new_list = new_list->next;	
	}
	return (final_line);
}
char *ft_strjoin_ult(t_list *new_list, t_list *ptr_first)
{
    t_list *tmp_list;
    t_list *tmp_ptr_first_list;
    ssize_t i = 0;
	ssize_t j = 0;
	ssize_t total_len = 0;
    char *line;
    char *final_line;
    char *rest_line;

    tmp_list = new_list;
    while (tmp_list)
    {
        if (tmp_list->content)
        {
			while (*(char *)tmp_list->content + total_len != '\n' 
			|| *(char *)tmp_list->content + total_len != '\n')
				total_len += total_len + 1;
        }
		printf("|%zu|\n", total_len);
        tmp_list = tmp_list->next;
    }

    final_line = malloc(total_len + 1);
    if (!final_line)
        return (NULL);

    tmp_list = new_list;
    while (tmp_list)
    {
        if (tmp_list->content)
        {
            line = (char *)tmp_list->content;
            while (line[i] != '\0' && line[i] != '\n')
            {
                final_line[i + j] = line[i];
                i++;
            }
            if (line[i] == '\n')
            {
                final_line[i + j] = '\n';
                final_line[i + j + 1] = '\0';
                rest_line = malloc(ft_strlen(line + i + 1) + 1);
                if (rest_line)
                {
                    ft_strlcpy(rest_line, line + i + 1, ft_strlen(line + i + 1) + 1);
                    tmp_ptr_first_list = ft_lstnew(rest_line);
					ft_lstadd_back(&ptr_first, tmp_ptr_first_list);
                    free(rest_line);
                }
                break;
            }

            i = 0;
        }
        j += i;
        tmp_list = tmp_list->next;
    }
    return (final_line);
}


void	*ft_readline(int fd)
{
	ssize_t	read_count;
	char	buf[BUFFER_SIZE + 1];
	void	*tmp_malloc;

	read_count = read(fd, buf, BUFFER_SIZE);
	if (read_count <= 0)
		return (NULL);
	buf[read_count] = '\0';
	tmp_malloc = malloc(read_count + 1);
	if (!tmp_malloc)
		return (NULL);
	ft_strlcpy((char *)tmp_malloc, buf, read_count + 1);
	return (tmp_malloc);
}

char	*ft_lstmap(int fd, void (*del)(void *), t_list *ptr_first)
{
	t_list	*ptr;
	t_list	*new_list;
	void	*ptr_tof;
	int		i;


	printf("4\n");
	i = 0;
	new_list = NULL;
	while (1)
	{
		
		ptr_tof = ft_readline(fd);
		if (!ptr_tof)
		{
			return (ft_strjoin_ult(new_list, ptr_first));
		}
		ptr = ft_lstnew(ptr_tof);
		if (!ptr)
		{
			ft_lstclear(&new_list, del);
			del(ptr_tof);
			return (NULL);
		}
		ft_lstadd_back(&new_list, ptr);
		while (1)
		{
			printf("|%c|",*(char *)ptr_tof + i);
			if (*(char *)ptr_tof + i == '\n')
				return (ft_strjoin_ult(new_list, ptr_first));
			
			if (*(char *)ptr_tof + i == '\0')
				break;
			i++;
		}
	}
	return (ft_strjoin_ult(new_list, ptr_first));
}

char	*get_next_line(int fd)
{
	char			*line1;
	char			*line2;
	char			*final_line;
	static t_list	*ptr_first;

	line1 = NULL;
	if (ptr_first)
	{
		line1 = malloc(ft_strlen(ptr_first->content) + 1);
		ft_strlcpy(line1, ptr_first->content, ft_strlen(ptr_first->content)
			+ 1);
	}
	line2 = ft_lstmap(fd, &free, ptr_first);
	printf("3\n");
	final_line = malloc(ft_strlen(line1) + ft_strlen(line2) + 1);
	ft_strlcpy(final_line, line1, ft_strlen(line1) + 1);
	ft_strlcpy(final_line + ft_strlen(line1), line2, ft_strlen(line2) + 1);
	return (final_line);
}
 */
int	main(void)
{
	int		i;
	char	*s;
	int		fd;

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
