#include "../include/command.h"
#include <malloc.h>

// Free all values of the command given.
// Does not free the command itself.
// Does not touch next elements.
static void	free_cmd_element(t_command *current_cmd);
// Free args of the command given
static void	free_cmd_args(t_command *current_cmd);

void	free_cmd_list(t_command *head_cmd)
{
	if (head_cmd->next)
		free_cmd_list(head_cmd->next);
	free_cmd_element(head_cmd);
	head_cmd = NULL;
}

static void	free_cmd_element(t_command *current_cmd)
{
	if (!current_cmd)
		return ;
	if (current_cmd->args)
		free_cmd_args(current_cmd);
	if (current_cmd->input_file)
		free(current_cmd->input_file);
	if (current_cmd->output_file)
		free(current_cmd->output_file);
	if (current_cmd->heredoc_eof)
		free(current_cmd->heredoc_eof);
	free(current_cmd);
}

static void	free_cmd_args(t_command *current_cmd)
{
	int	i;

	i = -1;
	while (current_cmd->args[++i])
		free(current_cmd->args[i]);
	free(current_cmd->args);
}
