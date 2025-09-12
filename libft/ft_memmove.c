/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:10:22 by agense            #+#    #+#             */
/*   Updated: 2025/05/20 11:43:47 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Copies n bytes from memory area src to memory area dest.
// The memory areas may overlap: copying takes place as though
// the bytes in src are first copied into a temporary array that
// does not overlap src or dest, and the bytes are then copied
// from the temporary array to dest.
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dest && !src)
		return (NULL);
	if (!n)
		return (dest);
	if (dest < src)
	{
		while (++i < n)
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
	}
	else
	{
		i = n;
		while (--i >= 1)
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		*(unsigned char *)(dest) = *(unsigned char *)(src);
	}
	return (dest);
}
