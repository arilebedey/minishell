#include "../../../include/command.h"
#include "../../../include/error.h"
#include "../../../libft/libft.h"
#include "../../include/token.h"
#include <malloc.h>

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

int	handle_in_file(t_token *curr_tk, t_command *curr_cmd)
{
	if (curr_cmd->input_file != NULL)
		return (print_error("error: already an input file"), 0);
	if (curr_cmd->heredoc_mode == 1)
		return (print_error("error: already heredoc, input fail"), 0);
	if (!curr_tk->next)
		return (print_error("error: no input file"), 0);
	if (curr_tk->next->type != T_WORD)
		return (print_error("error: what did u put next to < ??"), 0);
	curr_cmd->input_file = ft_strdup(curr_tk->next->value);
	if (!curr_cmd->input_file)
		return (perror("in_file malloc"), 0);
	return (1);
}

int	handle_heredoc(t_token *curr_tk, t_command *curr_cmd)
{
	if (curr_cmd->input_file != NULL)
		return (print_error("error: input file already set"), 0);
	if (curr_cmd->heredoc_mode == 1)
		return (print_error("error: dont heredoc multiple times!"), 0);
	curr_cmd->heredoc_mode = 1;
	if (!curr_tk->next)
		return (print_error("error: no heredoc eof"), 0);
	if (curr_tk->next->type != T_WORD)
		return (print_error("error: what did u put next to << ??"), 0);
	curr_cmd->heredoc_eof = ft_strdup(curr_tk->next->value);
	if (!curr_cmd->heredoc_eof)
		return (perror("in_file malloc"), 0);
	return (1);
}

int	handle_out_file(t_token *curr_tk, t_command *curr_cmd)
{
	if (curr_cmd->output_file != NULL)
		return (print_error("error: already an output file"), 0);
	if (curr_tk->type == T_APPEND)
		curr_cmd->append_mode = 1;
	if (!curr_tk->next)
		return (print_error("error: no output file"), 0);
	if (curr_tk->next->type != T_WORD)
	{
		if (curr_tk->type == T_APPEND)
			return (print_error("error: what did u put next to >> ??"), 0);
		else if (curr_tk->type == T_OUT)
			return (print_error("error: what did u put next to > ??"), 0);
		else
			return (print_error("wtf?"), 0);
	}
	curr_cmd->output_file = ft_strdup(curr_tk->next->value);
	if (!curr_cmd->output_file)
		return (perror("out_file malloc"), 0);
	return (1);
}
