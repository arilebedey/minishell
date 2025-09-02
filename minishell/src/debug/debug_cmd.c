#include "../../include/command.h"
#include "../../include/debug.h"
#include "../../libft/libft.h"

void	print_linked_lists(t_command *curr_cmd);

// Prints each fields of each command in the command list
void	debug_command_list(t_command *head_cmd)
{
	t_command	*curr_cmd;

	if (!DEBUG_COMMAND)
		return ;
	curr_cmd = head_cmd;
	while (curr_cmd)
	{
		print_linked_lists(curr_cmd);
		ft_printf("\n");
		curr_cmd = curr_cmd->next;
	}
	ft_printf("\n");
}

// Prints linked list fields
void	print_linked_lists(t_command *curr_cmd)
{
	t_args		*curr_arg;
	t_infile		*curr_infile;
	t_outfile		*curr_outfile;

	ft_printf("\nargs: ");
	curr_arg = curr_cmd->head_arg;
	while (curr_arg)
	{
		ft_printf("%s ", curr_arg->value);
		curr_arg = curr_arg->next;
	}
	ft_printf("\ninput files:");
	curr_infile = curr_cmd->head_infile;
	while (curr_infile)
	{
		ft_printf("(%s, ", curr_infile->value);
		ft_printf("%d), ", curr_infile->heredoc_mode);
		curr_infile = curr_infile->next;
	}
	ft_printf("\noutput files:");
	curr_outfile = curr_cmd->head_outfile;
	while (curr_outfile)
	{
		ft_printf("(%s, ", curr_outfile->value);
		ft_printf("%d), ", curr_outfile->append_mode);
		curr_outfile = curr_outfile->next;
	}
}
