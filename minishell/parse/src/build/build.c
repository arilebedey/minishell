#include "../../../include/command.h"
#include "../../../include/error.h"
#include "../../../libft/libft.h"
#include "../../include/token.h"
#include "../../include/build.h"
#include <stdlib.h>

static int	build_from_token(t_token **ref_curr_tk, t_command **ref_curr_cmd);
static int	redir_handlers(t_token **ref_curr_tk, t_command **ref_curr_cmd);
static int	check_args(t_command *head_cmd);

t_command	*build_command_list(t_token *head_tk)
{
	t_command	*head_cmd;
	t_command	*curr_cmd;
	t_token		*curr_tk;

	head_cmd = init_cmd();
	if (!head_cmd)
		return (NULL);
	curr_cmd = head_cmd;
	curr_tk = head_tk;
	while (curr_tk)
	{
		if (!build_from_token(&curr_tk, &curr_cmd))
			return (free_cmd_list(&head_cmd), NULL);
	}
	if (!check_args(head_cmd))
		return (print_error("error: no command"), free_cmd_list(&head_cmd),
			NULL);
	return (head_cmd);
}

// Build a component of a command (or alloc it) according to the token.
// If failed, returns 0.
static int	build_from_token(t_token **ref_curr_tk, t_command **ref_curr_cmd)
{
	if ((*ref_curr_tk)->type == T_PIPE)
	{
		if (!handle_pipe(*ref_curr_tk, ref_curr_cmd))
			return (0);
		*ref_curr_tk = (*ref_curr_tk)->next;
	}
	else if ((*ref_curr_tk)->type == T_WORD)
	{
		if (!handle_arg(*ref_curr_tk, *ref_curr_cmd))
			return (0);
		*ref_curr_tk = (*ref_curr_tk)->next;
	}
	else if (!redir_handlers(ref_curr_tk, ref_curr_cmd))
		return (0);
	return (1);
}

// Build redir component of a command according to the token.
// If failed, returns 0.
static int	redir_handlers(t_token **ref_curr_tk, t_command **ref_curr_cmd)
{
	if ((*ref_curr_tk)->type == T_IN || (*ref_curr_tk)->type == T_HEREDOC)
	{
		if (!handle_infile(*ref_curr_tk, &(*ref_curr_cmd)->head_infile))
			return (0);
		*ref_curr_tk = (*ref_curr_tk)->next->next;
	}
	else if ((*ref_curr_tk)->type == T_OUT || (*ref_curr_tk)->type == T_APPEND)
	{
		if (!handle_outfile(*ref_curr_tk, &(*ref_curr_cmd)->head_outfile))
			return (0);
		*ref_curr_tk = (*ref_curr_tk)->next->next;
	}
	return (1);
}

// Check if there is at least one argument for each command
static int	check_args(t_command *head_cmd)
{
	t_command	*curr_cmd;

	curr_cmd = head_cmd;
	while (curr_cmd)
	{
		if (!curr_cmd->head_arg)
			return (0);
		curr_cmd = curr_cmd->next;
	}
	return (1);
}
