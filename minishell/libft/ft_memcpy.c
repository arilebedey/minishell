/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:50:30 by agense            #+#    #+#             */
/*   Updated: 2025/05/14 12:44:17 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copies n bytes from memory area src to memory area dest.
// The memory areas must not overlap.
// Use memmove if the memory areas do overlap.
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dest && !src)
		return (NULL);
	while (++i < n)
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
	return (dest);
}
