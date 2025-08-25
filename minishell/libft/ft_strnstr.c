/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:05:15 by agense            #+#    #+#             */
/*   Updated: 2025/05/16 17:09:45 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns the first occurence of s2 in s1, where not more than n characters are
// searched. Characters that appear after '\0' are not searched.
// If s2 is an empty string, returns s1; if s2 occurs nowhere in s1,
// returns NULL; otherwise a pointer to the first character of the first
// occurence of s2 is returned.
char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	save_i;
	size_t	j;

	i = -1;
	if (s1[0])
		;
	if (!(*s2))
		return ((char *)s1);
	if (!s1 || !s2 || !n || (!s1[0] && s2[0]))
		return (NULL);
	while (s1[++i] && i < n)
	{
		j = 0;
		save_i = i;
		while ((s1[i] == s2[j] && i < n) || !s2[j])
		{
			if (!s2[j])
				return ((char *)(s1 + save_i));
			i++;
			j++;
		}
		i = save_i;
	}
	return (NULL);
}
