#include "../../include/env.h"
#include "../include/token.h"
#include "../../libft/libft.h"
#include "../../include/error.h"
#include <stdio.h>
#include <malloc.h>

static int	is_special_character(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"');
}

static void	add_token(t_token **ref_head_tk, t_token *new_token)
{
	t_token	*curr_tk;

	if (!(*ref_head_tk))
	{
		*ref_head_tk = new_token;
		return ;
	}
	curr_tk = (*ref_head_tk);
	while (curr_tk->next)
		curr_tk = curr_tk->next;
	curr_tk->next = new_token;
}

static t_token *create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	if (!value)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
		return (NULL);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

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
		{
			len_word = 2;
			*ref_line += 2;
			return (ft_strndup(start, len_word));
		}
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

static int	handle_word(const char **ref_line, t_token **ref_head_tk, const char *delim)
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

static int	handle_special_character(const char **ref_line, t_token **ref_head_tk)
{
	t_token	*new_token;

	new_token = NULL;
	if (**ref_line == '\'')
	{
		if (!handle_word(ref_line, ref_head_tk, "\'"))
			return (0);
	}
	else if (**ref_line == '\"')
	{
		if (!handle_word(ref_line, ref_head_tk, "\""))
			return (0);
	}
	else if (**ref_line == '|')
	{
		new_token = create_token("|", T_PIPE);
		if (!new_token)
			return (0);
		*ref_line += 1;
	}
	else if (**ref_line == '<')
	{
		if (**ref_line && *(*(ref_line) + 1) == '<')
		{
			new_token = create_token("<<", T_HEREDOC);
			if (!new_token)
				return (0);
			*ref_line += 2;
		}
		else
		{
			new_token = create_token("<", T_IN);
			if (!new_token)
				return (0);
			*ref_line += 1;
		}
	}
	else if (**ref_line == '>')
	{
		if (**ref_line && *(*(ref_line) + 1) == '>')
		{
			new_token = create_token(">>", T_APPEND);
			if (!new_token)
				return (0);
			*ref_line += 2;
		}
		else
		{
			new_token = create_token(">", T_OUT);
			if (!new_token)
				return (0);
			*ref_line += 1;
		}
	}
	else
		return (print_error("BIG LOL\n"), 0);
	add_token(ref_head_tk, new_token);
	return (1);
}

t_token	*lexer(const char *line)
{
	t_token *head_tk;

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
