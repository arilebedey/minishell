#include "../../include/token.h"
#include "../../include/lexer.h"
#include "../../../include/error.h"
#include <malloc.h>

static int	handle_pipe(const char **ref_line, t_token **ref_new_token);
static int	handle_in(const char **ref_line, t_token **ref_new_token);
static int	handle_out(const char **ref_line, t_token **ref_new_token);
static int	handle_quote(const char **ref_line, t_token **ref_head_tk, \
	const char quote);

int	handle_special_character(const char **ref_line, t_token **ref_head_tk)
{
	t_token	*new_token;

	new_token = NULL;
	if (**ref_line == '\'' || **ref_line == '\"')
		return (handle_quote(ref_line, ref_head_tk, **ref_line));
	else if (**ref_line == '|')
	{
		if (!handle_pipe(ref_line, &new_token))
			return (0);
	}
	else if (**ref_line == '<')
	{
		if (!handle_in(ref_line, &new_token))
			return (0);
	}
	else if (**ref_line == '>')
	{
		if (!handle_out(ref_line, &new_token))
			return (0);
	}
	else
		return (print_error("BIG LOL\n"), 0);
	add_token(ref_head_tk, new_token);
	return (1);
}

// Handle new T_WORD token between quotes.
// If failed, returns 0.
static int	handle_quote(const char **ref_line, t_token **ref_head_tk, \
	const char quote)
{
	if (quote == '\'')
	{
		if (!handle_word(ref_line, ref_head_tk, "\'"))
			return (0);
	}
	else if (quote == '\"')
	{
		if (!handle_word(ref_line, ref_head_tk, "\""))
			return (0);
	}
	return (1);
}

// Handle new T_PIPE token.
// If failed, returns 0.
static int	handle_pipe(const char **ref_line, t_token **ref_new_token)
{
	*ref_new_token = create_token("|", T_PIPE);
	if (!*ref_new_token)
		return (0);
	*ref_line += 1;
	return (1);
}

// Handle new T_OUT or T_APPEND token.
// If failed, returns 0.
static int	handle_out(const char **ref_line, t_token **ref_new_token)
{
	if (**ref_line && *(*(ref_line) + 1) == '>')
	{
		*ref_new_token = create_token(">>", T_APPEND);
		if (!*ref_new_token)
			return (0);
		*ref_line += 2;
	}
	else
	{
		*ref_new_token = create_token(">", T_OUT);
		if (!*ref_new_token)
			return (0);
		*ref_line += 1;
	}
	return (1);
}

// Handle new T_IN or T_HEREDOC token.
// If failed, returns 0.
static int	handle_in(const char **ref_line, t_token **ref_new_token)
{
	if (**ref_line && *(*(ref_line) + 1) == '<')
	{
		*ref_new_token = create_token("<<", T_HEREDOC);
		if (!*ref_new_token)
			return (0);
		*ref_line += 2;
	}
	else
	{
		*ref_new_token = create_token("<", T_IN);
		if (!ref_new_token)
			return (0);
		*ref_line += 1;
	}
	return (1);
}
