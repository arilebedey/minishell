/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:52 by agense            #+#    #+#             */
/*   Updated: 2025/05/16 16:50:55 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns a pointer to the last occurence of the character c in the string s
char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*p_c;

	if (!(char)c)
		return ((char *)(s + ft_strlen(s)));
	i = -1;
	p_c = 0;
	while (s[++i])
	{
		if (s[i] == (char)c)
			p_c = &(s[i]);
	}
	return ((char *)p_c);
}
