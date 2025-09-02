/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:16:05 by agense            #+#    #+#             */
/*   Updated: 2025/09/02 21:12:38 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// Iterate on the list and apply the f function on the content of each element.
// Create a new list resulting from the successive applications of f.
// The del function is here to delete the content of an element if necessary.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*to_add;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = ft_lstnew((*f)(lst->content));
	if (!new_lst)
		return (NULL);
	while (lst)
	{
		lst = lst->next;
		if (!lst)
			break ;
		to_add = ft_lstnew((*f)(lst->content));
		if (!to_add)
			return (NULL);
		ft_lstadd_back(&new_lst, to_add);
	}
	return (new_lst);
}
