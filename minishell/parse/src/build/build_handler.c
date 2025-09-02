#include "../../../include/command.h"
#include "../../../include/error.h"
#include "../../../libft/libft.h"
#include "../../include/token.h"
#include <stdio.h>
#include <stdlib.h>

int	handle_pipe(t_token *curr_tk, t_command **ref_curr_cmd)
{
	if (!curr_tk->next || curr_tk->next->type == T_PIPE)
		return (print_error("error: nothing after pipe >:("), 0);
	(*ref_curr_cmd)->next = init_cmd();
	if (!(*ref_curr_cmd)->next)
		return (0);
	*ref_curr_cmd = (*ref_curr_cmd)->next;
	return (1);
}

int	handle_arg(t_token *curr_tk, t_command *curr_cmd)
{
	char	*value;

	value = ft_strdup(curr_tk->value);
	if (!value)
		return (perror("handle arg malloc"), 0);
	if (!add_arg(&curr_cmd->head_arg, value))
		return (0);
	return (1);
}

int	handle_infile(t_token *curr_tk, t_infile **ref_head_infile)
{
	if (!curr_tk->next)
		return (print_error("error: no input file"), 0);
	if (curr_tk->type == T_IN)
	{
		if (curr_tk->next->type != T_WORD)
			return (print_error("error: what did u put next to < ??"), 0);
		if (!add_infile(ref_head_infile, ft_strdup(curr_tk->next->value), 0))
			return (0);
	}
	else if (curr_tk->type == T_HEREDOC)
	{
		if (curr_tk->next->type != T_WORD)
			return (print_error("error: what did u put next to << ??"), 0);
		if (!add_infile(ref_head_infile, ft_strdup(curr_tk->next->value), 1))
			return (0);
	}
	else
		return (print_error("wtf?(in)"), 0);
	return (1);
}

int	handle_outfile(t_token *curr_tk, t_outfile **ref_head_outfile)
{
	if (!curr_tk->next)
		return (print_error("error: no output file"), 0);
	if (curr_tk->type == T_OUT)
	{
		if (curr_tk->next->type != T_WORD)
			return (print_error("error: what did u put next to > ??"), 0);
		if (!add_outfile(ref_head_outfile, ft_strdup(curr_tk->next->value), 0))
			return (0);
	}
	else if (curr_tk->type == T_APPEND)
	{
		if (curr_tk->next->type != T_WORD)
			return (print_error("error: what did u put next to >> ??"), 0);
		if (!add_outfile(ref_head_outfile, ft_strdup(curr_tk->next->value), 1))
			return (0);
	}
	else
		return (print_error("wtf?(out)"), 0);
	return (1);
}
