#include "../../include/command.h"
#include "../../include/env.h"
#include "../../libft/libft.h"
#include "../include/parse.h"
#include "../include/token.h"

#define DEBUG_TOKEN 0
#define DEBUG_COMMAND 1

static void	debug_token_list(t_token *head_tk);
static void	debug_command_list(t_command *head_cmd);

t_command	*parse(const char* line, t_env *head_env)
{
	(void)head_env;
	t_token		*head_tk;
	t_command	*head_cmd;

	head_tk = lexer(line);
	if (!head_tk)
		return (NULL);
	if (DEBUG_TOKEN)
		debug_token_list(head_tk);
	head_cmd = build_command_list(head_tk);
	free_token_list(&head_tk);
	if (!head_cmd)
		return (NULL);
	if (DEBUG_COMMAND)
		debug_command_list(head_cmd);
	// TODO: expansion
	return (head_cmd);
}

// Prints each fields of each command in the command list
static void	debug_command_list(t_command *head_cmd)
{
	t_command	*curr_cmd;
	t_args		*curr_arg;

	curr_cmd = head_cmd;
	while (curr_cmd)
	{
		ft_printf("\nargs: ");
		curr_arg = curr_cmd->head_arg;
		while (curr_arg)
		{
			ft_printf("%s ", curr_arg->value);
			curr_arg = curr_arg->next;
		}
		ft_printf("\ninput file: %s", curr_cmd->input_file);
		ft_printf("\noutput file: %s", curr_cmd->output_file);
		ft_printf("\nappend mode: %d", curr_cmd->append_mode);
		ft_printf("\nheredoc mode: %d", curr_cmd->heredoc_mode);
		ft_printf("\nheredoc eof: %s", curr_cmd->heredoc_eof);
		ft_printf("\n");
		curr_cmd = curr_cmd->next;
	}
	ft_printf("\n");
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
