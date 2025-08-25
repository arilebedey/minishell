/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:53:00 by agense            #+#    #+#             */
/*   Updated: 2025/05/13 09:08:10 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

// Returns a pointer to a new string which is a duplicate of the string s.
// Memory for the new string is obtained with malloc, and can be freed
// with free().
// Returns NULL if insufficient memory was available.
char	*ft_strdup(const char *s)
{
	char	*dup;
	int		s_len;
	int		i;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	dup = malloc(sizeof(char) * s_len + 1);
	if (!dup)
		return (0);
	i = -1;
	while (++i < s_len)
		dup[i] = s[i];
	dup[i] = 0;
	return (dup);
}
