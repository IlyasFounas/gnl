/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:26:57 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/08 11:13:44 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	//free(tmp_malloc);
	return (read_count);
}

// read in the file while the line is finished
static char	*ft_readline_while(int fd, t_list *ptr)
{
	ssize_t	read_count;

	while (*(char *)ptr->content + BUFFER_SIZE - 1 != '\n'
		&& *(char *)ptr->content + BUFFER_SIZE - 1 != '\0')
	{
		read_count = ft_readline(fd, ptr);
		if (read_count <= 0)
			return (NULL);
		ptr = ptr->next;
	}
	return ((char *)ptr->content);
}

// Join all the lists of ptr and return a char*
char	*ft_strjoin_structs(int fd, t_list *ptr_to_first, t_list *ptr)
{
	t_list	*current;
	char	*line;
	char	*tmp;

	ft_readline_while(fd, ptr);
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
	static t_list	*ptr_to_first;
	t_list			*ptr;
	ssize_t			read_count;

	if (!ptr_to_first)
		ptr_to_first = ft_lstnew(NULL);
	ptr = ft_lstnew(NULL);
	if (!ptr)
		return (NULL);
	ft_lstadd_back(&ptr_to_first, ptr);
	read_count = ft_readline(fd, ptr);
	if (read_count <= 0)
		return (NULL);
	ptr = ft_lstlast(ptr);
	if (*(char *)ptr->content + BUFFER_SIZE - 1 == '\n' || *(char *)ptr->content
		+ BUFFER_SIZE - 1 == '\0')
		return (ptr->content);
	else
		return (ft_strjoin_structs(fd, ptr_to_first, ptr));
}

int	main(void)
{
	int		i;
	char	*s;
	int		fd;

	i = -1;
	fd = open("text_simple.txt", O_RDONLY);
	while (++i < 30)
	{
		s = get_next_line(fd);
		if (s)
		{
			printf("%s", s);
			free(s);
		}
		else
			printf("%s", s);
	}
	close(fd);
}
