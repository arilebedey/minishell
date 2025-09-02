#include "../../../libft/libft.h"
#include "../../include/lexer.h"
#include "../../include/token.h"
#include <stdio.h>
#include <stdlib.h>

static int	is_special_character(char c);

t_token	*lexer(const char *line)
{
	t_token	*head_tk;

	head_tk = NULL;
	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		if (!*line)
			break ;
		if (is_special_character(*line))
		{
			if (!handle_special_character(&line, &head_tk))
				return (free_token_list(&head_tk), NULL);
		}
		else
		{
			if (!handle_word(&line, &head_tk, " |<>\"\'"))
				return (free_token_list(&head_tk), NULL);
		}
	}
	return (head_tk);
}

static int	is_special_character(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"');
}
