#include "../../includes/minishell.h"

static int	is_operator(t_token_type type)
{
	return (type == T_PIPE || type == T_REDIR_OUT);
}

/* Fonctoin deguelatssse */
int	syntax_error(t_token *tok)
{
	if (!tok)
		return (0);
	// First token cannot be a pipe or redirection
	if (tok->type == T_PIPE || tok->type == T_REDIR_OUT)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (tok->type == T_PIPE && tok->next && tok->next->type == T_PIPE)
			ft_putstr_fd("||", 2);
		else
			ft_putstr_fd(tok->text, 2);
		ft_putendl_fd("'", 2);
		return (1);
	}
	while (tok)
	{
		// Detect double pipe "||"
		if (tok->type == T_PIPE && tok->next && tok->next->type == T_PIPE)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `||'\n",
				2);
			return (1);
		}
		// Operator at the end or followed by another operator
		if (is_operator(tok->type))
		{
			if (!tok->next) // last token is operator
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `",
					2);
				ft_putstr_fd(tok->text, 2);
				ft_putendl_fd("'", 2);
				return (1);
			}
			if (is_operator(tok->next->type))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `",
					2);
				ft_putstr_fd(tok->next->text, 2);
				ft_putendl_fd("'", 2);
				return (1);
			}
		}
		tok = tok->next;
	}
	return (0);
}
