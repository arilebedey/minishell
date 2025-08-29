#include "../../include/command.h"
#include "../../include/env.h"
#include "../../libft/libft.h"
#include "../include/parse.h"
#include "../include/token.h"

static void	debug_token_list(t_token *head_tk);

t_command	*parse(const char* line, t_env *head_env)
{
	(void)head_env;
	t_token		*head_tk;
	t_command	*head_cmd;

	head_tk = lexer(line);
	if (!head_tk)
		return (NULL);
	debug_token_list(head_tk);
	// TODO: check_syntax
	head_cmd = build_command_list(head_tk);
	if (!head_cmd)
		return (free_token_list(&head_tk), NULL);
	// TODO: expansion
	free_token_list(&head_tk);
	return (head_cmd);
}

// Prints value and type of all token elements.
static void	debug_token_list(t_token *head_tk)
{
	t_token	*curr_tk;

	curr_tk = head_tk;
	while (curr_tk)
	{
		ft_printf("\nType: ");
		switch (curr_tk->type)
		{
			case T_WORD:
				ft_printf("T_WORD");
				break;
			case T_PIPE:
				ft_printf("T_PIPE");
				break;
			case T_IN:
				ft_printf("T_IN");
				break;
			case T_OUT:
				ft_printf("T_OUT");
				break;
			case T_APPEND:
				ft_printf("T_APPEND");
				break;
			case T_HEREDOC:
				ft_printf("T_HEREDOC");
				break;
			default:
				ft_printf("ERROR DEBUG TOKEN LIST");
				break;
		}
		ft_printf("\nValue: %s", curr_tk->value);
		curr_tk = curr_tk->next;
	}
	ft_printf("\n\n");
}
