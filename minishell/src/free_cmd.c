#include "../include/command.h"
#include <malloc.h>

static void	free_cmd_element(t_command *current_cmd);
static void	free_cmd_args(t_args *curr_arg);

void	free_cmd_list(t_command *head_cmd)
{
	if (!head_cmd)
		return ;
	if (head_cmd->next)
		free_cmd_list(head_cmd->next);
	free_cmd_element(head_cmd);
	head_cmd = NULL;
}

// Free all values of the command given.
// Does not free the command itself.
// Does not touch next elements.
static void	free_cmd_element(t_command *current_cmd)
{
	if (!current_cmd)
		return ;
	free_cmd_args(current_cmd->head_arg);
	free(current_cmd->input_file);
	free(current_cmd->output_file);
	free(current_cmd->heredoc_eof);
	free(current_cmd);
}

// Free args of the command given
static void	free_cmd_args(t_args *curr_arg)
{
	if (!curr_arg)
		return ;
	if (curr_arg->next)
		free_cmd_args(curr_arg->next);
	free(curr_arg->value);
	free(curr_arg);
}
