/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:40:04 by agense            #+#    #+#             */
/*   Updated: 2025/05/16 14:58:35 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

// Returns a new string resulting from the application of f for all char in s.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new_s;

	new_s = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_s)
		return (0);
	i = -1;
	while (s[++i])
		new_s[i] = (*f)(i, s[i]);
	new_s[i] = 0;
	return (new_s);
}
