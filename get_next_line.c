/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:26:57 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/06 23:55:36 by marvin           ###   ########.fr       */
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
		return (-1);
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

// return the lst
char	*get_next_line(int fd)
{
	static t_list	*ptr_to_first;
	t_list			*ptr;
	ssize_t			read_count;
	t_list			*current;

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
	{
		ft_readline_while(fd, ptr);
		current = ptr_to_first->next;
		while (current)
		{
			if (current->content)
				printf("%s", (char *)current->content);
			current = current->next;
		}
		return (NULL);
	}
}

int	main(void)
{
	int i = -1;
	char *s;
	int fd = open("text_simple.txt", O_RDONLY);
	while (++i < 4)
	{
		s = get_next_line(fd);
		printf("%s", s);
		// free(s);
	}
	close(fd);
}