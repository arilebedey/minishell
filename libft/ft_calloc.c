/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:19:35 by agense            #+#    #+#             */
/*   Updated: 2025/09/02 21:09:22 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// Allocates memory for an array of n_elem elements of size bytes each and
// returns a pointer to the allocated memory.
// The memory is set to zero.
// If n_elem or size is 0, returns a unique pointer value that can later
// be successfully passed to free().
// Error if n_elem * size results to integer overflow

static void	*zeroalloc(size_t size)
{
	void	*mem_ptr;

	mem_ptr = malloc(size);
	if (!mem_ptr)
		return (NULL);
	ft_bzero(mem_ptr, size);
	return (mem_ptr);
}

void	*ft_calloc(size_t count, size_t size)
{
	if (size != 0 && count > ((size_t)-1 / size))
		return (NULL);
	return (zeroalloc(count * size));
}
