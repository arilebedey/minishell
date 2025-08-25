/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:27:30 by agense            #+#    #+#             */
/*   Updated: 2025/05/13 09:08:28 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

// Returns a new string which is the concatenation of s1 and s2.
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*conc_s;
	int		len_s1;
	int		len_s2;
	int		i;
	int		j;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	conc_s = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!conc_s)
		return (0);
	i = -1;
	while (++i < len_s1)
		conc_s[i] = s1[i];
	j = -1;
	while (i < len_s1 + len_s2)
		conc_s[i++] = s2[++j];
	conc_s[i] = 0;
	return (conc_s);
}
