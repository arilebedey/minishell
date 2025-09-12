/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:43:46 by agense            #+#    #+#             */
/*   Updated: 2025/05/16 17:33:46 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Scans the initial n bytes of the memory area pointed to by s.
// Returns a pointer to the first occurence of c if c is in the n bytes,
// otherwise returns NULL.
// Both c and the bytes of the memory area pointed to by s are interpreted
// as unsigned char.
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return ((void *)(s + i));
	}
	return (NULL);
}
