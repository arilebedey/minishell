#include "../../include/command.h"
#include "../include/token.h"
#include <malloc.h>

t_command	*build_command_list(t_token *head_tk)
{
	(void)head_tk;
	t_command *head_cmd;

	head_cmd = malloc(sizeof(t_command));
	init_cmd_values(head_cmd);
	if (!head_cmd)
		return (NULL);
	return (head_cmd);
}
