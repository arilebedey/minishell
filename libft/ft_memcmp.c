/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:39:59 by agense            #+#    #+#             */
/*   Updated: 2025/05/06 20:53:54 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns an integer less than, or greater than zero of the first
// byte of s1 which is respectively, to be less than, or be
// greater than the first different byte from s2.
// Each bytes are interpreted as unsigned char.
// Compare until n bytes, if n is NULL, return NULL
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c_s1;
	unsigned char	*c_s2;

	c_s1 = (unsigned char *)s1;
	c_s2 = (unsigned char *)s2;
	i = 0;
	while (c_s1[i] == c_s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (c_s1[i] - c_s2[i]);
}
