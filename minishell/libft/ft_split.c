/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:10:01 by agense            #+#    #+#             */
/*   Updated: 2025/06/20 16:15:56 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

// Returns the number of words in s separated by sep
static int	count_words(char const *s, char sep)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] != sep)
		{
			count++;
			while (s[i] != sep && s[i + 1])
				i++;
		}
	}
	return (count);
}

// Returns a new string which contains the char contents in s at the
// index pointed by i until the separator sep or end of s ('\0').
// The index pointed by i is modified to be at the position of the last char
// of the word returned in the string s.
static char	*take_word(char const *s, char sep, int *i)
{
	char	*word;
	int		len;
	int		save_i;
	int		j;

	len = 0;
	save_i = *i;
	while (s[*i] != sep && s[*i])
	{
		(*i)++;
		len++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (save_i < *i)
		word[j++] = s[save_i++];
	word[len] = 0;
	(*i)--;
	return (word);
}

// Free all the strings in tab.
// You must give the number of strings in tab with tab_count.
// Returns a null pointer
static char	**free_string_tab(char **tab, int tab_count)
{
	while (--tab_count >= 0)
		free(tab[tab_count]);
	return (NULL);
}

// Separate the string s with the character c and returns all these
// separated string in an array of string.
char	**ft_split(char const *s, char c)
{
	char	**split_s;
	int		i;
	int		spl_i;

	i = -1;
	spl_i = 0;
	if (!s)
		return (NULL);
	split_s = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split_s)
		return (NULL);
	while (s[++i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			split_s[spl_i] = take_word(s, c, &i);
			if (!split_s[spl_i++])
				return (free_string_tab(split_s, spl_i));
		}
		else
			break ;
	}
	return (split_s[spl_i] = 0, split_s);
}
