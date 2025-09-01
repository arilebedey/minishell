#include "../../include/command.h"
#include "../../include/debug.h"
#include "../../libft/libft.h"

// Prints each fields of each command in the command list
void	debug_command_list(t_command *head_cmd)
{
	t_command	*curr_cmd;
	t_args		*curr_arg;

	if (!DEBUG_COMMAND)
		return ;
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
