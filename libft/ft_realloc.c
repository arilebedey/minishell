/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:13:28 by agense            #+#    #+#             */
/*   Updated: 2025/09/02 21:12:07 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_realloc(char **str_p, int malloc_size)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * malloc_size);
	if (!new_str)
		return (0);
	ft_strlcpy(new_str, *str_p, malloc_size - 1);
	if (str_p)
		free(*str_p);
	*str_p = new_str;
	return (1);
}
