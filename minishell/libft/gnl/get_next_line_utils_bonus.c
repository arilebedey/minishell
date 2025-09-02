/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:36:02 by agense            #+#    #+#             */
/*   Updated: 2025/09/02 21:11:45 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc_edit(size_t n_elem, size_t size)
{
	char	*p;
	size_t	i;
	size_t	total;

	if (n_elem == 0 || size == 0)
		return (NULL);
	total = n_elem * size;
	p = malloc(total);
	if (!p)
		return (NULL);
	i = 0;
	while (i < total)
		p[i++] = 0;
	return (p);
}

size_t	ft_strlen_edit(const char *s, char c)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (i);
}

char	*ft_strchr_edit(const char *s, int c, size_t s_len)
{
	int	i;

	if (!s)
		return (NULL);
	if (!(char)c)
		return ((char *)(s + s_len));
	i = -1;
	while (s[++i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
	}
	return (0);
}

char	*ft_strjoin_edit(char const *s1, char const *s2)
{
	char	*conc_s;
	int		len_s1;
	int		len_s2;
	int		i;
	int		j;

	len_s1 = ft_strlen_edit(s1, 0);
	len_s2 = ft_strlen_edit(s2, 0);
	conc_s = ft_calloc_edit(len_s1 + len_s2 + 1, sizeof(char));
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
