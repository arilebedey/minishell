#include "../../include/command.h"
#include "../../include/error.h"
#include "../include/token.h"
#include <malloc.h>

// Returns a new arg initialized with each fields set to NULL.
// If failed, returns NULL pointer.
static t_args	*init_arg(void);

t_command	*init_cmd(void)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
	{
		perror("command malloc");
		return (NULL);
	}
	new_cmd->head_arg = NULL;
	new_cmd->input_file = NULL;
	new_cmd->output_file = NULL;
	new_cmd->append_mode = 0;
	new_cmd->heredoc_mode = 0;
	new_cmd->heredoc_eof = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

int	add_arg(t_args **ref_head_arg, char *value)
{
	t_args	*curr_arg;

	if (!*ref_head_arg)
	{
		*ref_head_arg = init_arg();
		if (!*ref_head_arg)
			return (print_error("error: head_arg malloc"), 0);
		(*ref_head_arg)->value = value;
		return (1);
	}
	curr_arg = *ref_head_arg;
	while (curr_arg->next)
		curr_arg = curr_arg->next;
	curr_arg->next = init_arg();
	if (!curr_arg->next)
		return (print_error("error: curr_arg malloc"), 0);
	curr_arg->next->value = value;
	return (1);
}

static t_args	*init_arg(void)
{
	t_args	*new_arg;

	new_arg = malloc(sizeof(t_args));
	if (!new_arg)
		return (NULL);
	new_arg->value = NULL;
	new_arg->next = NULL;
	return (new_arg);
}
