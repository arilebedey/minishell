/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:04:04 by agense            #+#    #+#             */
/*   Updated: 2025/05/16 15:37:53 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Iterate in the list and apply the f function on the content of each element.
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst)
	{
		if (lst->next)
			ft_lstiter(lst->next, f);
		f(lst->content);
	}
}
