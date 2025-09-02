/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:25:42 by agense            #+#    #+#             */
/*   Updated: 2025/09/02 21:10:21 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// Returns 1 if a char in the string set is equal to the char s.
// Otherwise returns 0.
static int	detec_set(char const s, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		if ((unsigned char)set[i] == (unsigned char)s)
			return (1);
	}
	return (0);
}

// int	ft_strlen_int(const char *s)
//{
//	int	i;

//	i = -1;
//	while (s[++i])
//		;
//	return (i);
//}

// Returns a new string which is a copy of s1 without chars in the string set
// at start and end of s1.
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_s;
	size_t	i;
	size_t	start;
	size_t	end;

	i = -1;
	while (detec_set(s1[++i], set))
		;
	start = i;
	if (start == ft_strlen(s1))
	{
		new_s = malloc(1);
		return (*new_s = 0, new_s);
	}
	i--;
	while (s1[++i])
	{
		if (!detec_set(s1[i], set))
			end = i;
	}
	new_s = malloc(sizeof(char) * (end - start + 2));
	if (!new_s)
		return (NULL);
	return (ft_strlcpy(new_s, s1 + start, end - start + 2), new_s);
}
