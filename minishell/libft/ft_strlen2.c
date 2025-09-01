/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:05:18 by agense            #+#    #+#             */
/*   Updated: 2025/09/01 15:21:32 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Calculates the length of the string pointed to by s until '\0' or delim.
size_t	ft_strlen2(const char *s, const char delim)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
	{
		if (s[i] == delim)
			return (i);
	}
	return (i);
}
