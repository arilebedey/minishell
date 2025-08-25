/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:19:35 by agense            #+#    #+#             */
/*   Updated: 2025/05/13 09:04:25 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

// Allocates memory for an array of n_elem elements of size bytes each and
// returns a pointer to the allocated memory.
// The memory is set to zero.
// If n_elem or size is 0, returns a unique pointer value that can later
// be successfully passed to free().
// Error if n_elem * size results to integer overflow
void	*ft_calloc(size_t n_elem, size_t size)
{
	char	*p;
	size_t	i;

	if (!n_elem || !size)
	{
		p = malloc(0);
		if (!p)
			return (0);
		return (p);
	}
	p = malloc(n_elem * size);
	if (!p)
		return (0);
	i = -1;
	while (++i < n_elem * size)
		p[i] = 0;
	return (p);
}
