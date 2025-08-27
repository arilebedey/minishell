#include "../../include/command.h"
#include <malloc.h>

void	init_cmd_values(t_command *curr_cmd)
{
	curr_cmd->args = NULL;
	curr_cmd->input_file = NULL;
	curr_cmd->output_file = NULL;
	curr_cmd->append_mode = 0;
	curr_cmd->heredoc_mode = 0;
	curr_cmd->heredoc_eof = NULL;
	curr_cmd->next = NULL;
}
