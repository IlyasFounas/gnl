/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:26:57 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/06 15:23:43 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//read in the file
static ssize_t	ft_readline(int fd, t_list *ptr)
{
	ssize_t	read_count;
	t_list	*ptr_tmp;
	char	buf[BUFFER_SIZE + 1];

	read_count = 1;
	read_count = read(fd, buf, BUFFER_SIZE);
	if (read_count <= 0)
		return (-1);
	buf[read_count] = '\0';
	ptr_tmp = ft_lstnew((void *)buf);
	if (!ptr_tmp)
		return (-1);
	
	//printf("%s",(char *)ptr_tmp->content);
	ft_lstadd_back(&ptr, ptr_tmp);
	
	return (read_count);
}

//read in the file while the line is finished
static char	*ft_readline_while(int fd, t_list *ptr)
{
	ssize_t	read_count;

	while (*(char *)ptr->content + BUFFER_SIZE - 1 != '\n'
		&& *(char *)ptr->content + BUFFER_SIZE - 1 != '\0')
	{
		ptr = ft_lstlast(ptr);
		read_count = ft_readline(fd, ptr);
		if (read_count <= 0)
			return (NULL);
	}
	return ((char *)ptr->content);
}

//return the lst
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
	{
		ft_readline_while(fd, ptr);
		ptr_to_first = ptr_to_first->next;
		
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
		//free(s);
	}
	close(fd);
}