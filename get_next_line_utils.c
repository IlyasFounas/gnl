/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifounas <ifounas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:25:28 by ifounas           #+#    #+#             */
/*   Updated: 2024/12/06 15:20:39 by ifounas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	if (content == NULL)
		new->content = NULL;
	else
		new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	/*t_list	*ptr;


	printf("%s", (char *)lst->content);
	 if (lst == NULL)
		return (0); */
	while (lst)
	{
		/* ptr = lst;
		lst = lst->next; */
		if (lst == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst)
	{

/* 		printf("%s", (char *)new->content);
 */		ft_lstlast(*lst);
 		(*lst)->next = new;
		//printf("%s", (char *)(*lst)->content);
	}
	else
		*lst = new;
	//printf("%s", (char *)(*lst)->content);
}
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (del == NULL || lst == NULL)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;

	if (del == NULL)
		return ;
	ptr = *lst;
	while (*lst)
	{
		*lst = (*lst)->next;
		ft_lstdelone(ptr, del);
		ptr = *lst;
	}
	*lst = NULL;
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f == NULL)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_lstiter_print(t_list *lst)
{
	while (lst)
	{
		printf("%s", (char *)lst->content);
		lst = lst->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *ptr;
	t_list *new_list;
	void *ptr_tof;

	new_list = NULL;
	while (lst)
	{
		ptr_tof = f(lst->content);
		if (ptr_tof == NULL)
		{
			ft_lstclear(&new_list, del);
			return (0);
		}
		ptr = ft_lstnew(ptr_tof);
		if (ptr == NULL)
		{
			ft_lstclear(&new_list, del);
			del(ptr_tof);
			return (0);
		}
		ft_lstadd_back(&new_list, ptr);
		lst = lst->next;
	}
	return (new_list);
}