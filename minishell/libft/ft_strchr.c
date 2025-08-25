/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:53:19 by agense            #+#    #+#             */
/*   Updated: 2025/05/16 16:50:08 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns a pointer to the first occurence of the character c in the string s.
char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (s[0])
		;
	if (!s)
		return (NULL);
	if (!(char)c)
		return ((char *)(s + ft_strlen(s)));
	i = -1;
	while (s[++i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
	}
	return (0);
}
