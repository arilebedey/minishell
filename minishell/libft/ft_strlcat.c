/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:46:14 by agense            #+#    #+#             */
/*   Updated: 2025/05/16 11:40:31 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Appends the NUL-terminated string src to the end of dest.
// Append at most size - strlen(dest) - 1 bytes.
// NUL-terminating the result (except if size = 0
// or size of dest >= dest_size given)
// Returns the length of the string it tried to create.
size_t	ft_strlcat(char *dest, const char *src, size_t dest_size)
{
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (src[0])
		;
	if (!src)
		return (0);
	if (dest_len >= dest_size)
		return (dest_size + src_len);
	if (src_len < dest_size - dest_len)
		ft_memcpy(dest + dest_len, src, src_len + 1);
	else
	{
		ft_memcpy(dest + dest_len, src, dest_size - dest_len - 1);
		dest[dest_size - 1] = 0;
	}
	return (dest_len + src_len);
}
