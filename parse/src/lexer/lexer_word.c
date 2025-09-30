/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:09:42 by agense            #+#    #+#             */
/*   Updated: 2025/09/30 16:27:44 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/token.h"
#include "../../../libft/libft.h"
#include "../../../include/error.h"
#include <stdio.h>
#include <stdlib.h>

static char	*take_word(const char **ref_line, const char *delim);

int	handle_word(const char **ref_line, t_token **ref_head_tk, const char *delim)
{
	t_token	*new_token;
	char	*word;

	word = take_word(ref_line, delim);
	if (!word)
		return (0);
	new_token = create_token(word, T_WORD);
	free(word);
	if (!new_token)
		return (0);
	add_token(ref_head_tk, new_token);
	return (1);
}

// Returns a new string starting at line until a char in delim.
// Delim is excluded at the end except if it's a quote.
static char	*take_word(const char **ref_line, const char *delim)
{
	const char	*start;
	const char	*end;
	ptrdiff_t	len_word;

	start = *ref_line;
	if (*delim == '\'' || *delim == '\"')
	{
		end = ft_strchr2(*ref_line + 1, delim);
		if (!end)
			return (print_error("quote not closed\n"), NULL);
		if (end == start + 1)
			return (*ref_line += 2, ft_strndup(start, 2));
		end += 1;
	}
	else
	{
		end = ft_strchr2(*ref_line, delim);
		if (!end)
			end = start + ft_strlen(start);
	}
	len_word = end - start;
	*ref_line += len_word;
	return (ft_strndup(start, len_word));
}
