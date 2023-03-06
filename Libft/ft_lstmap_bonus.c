/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:39:58 by crigonza          #+#    #+#             */
/*   Updated: 2022/05/01 10:36:53 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*aux;
	t_list	*newlst;

	aux = NULL;
	newlst = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		aux = ft_lstnew(f(lst->content));
		if (!aux)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		else
			ft_lstadd_back(&newlst, aux);
		lst = lst->next;
	}
	return (newlst);
}
