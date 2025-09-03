#include "../../../include/command.h"
#include "../../../libft/libft.h"
#include "../../include/heredoc.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int	process_heredocs(t_command *head_cmd)
{
	t_command	*cmd;
	int			index;

	cmd = head_cmd;
	index = 0;
	while (cmd)
	{
		if (!process_cmd_heredocs(cmd, index))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}

void	cleanup_heredocs(t_command *head_cmd)
{
	t_command	*cmd;
	t_infile	*in;

	cmd = head_cmd;
	while (cmd)
	{
		in = cmd->head_infile;
		while (in)
		{
			if (in->value && ft_strnstr(in->value, "/tmp/minishell_heredoc_",
					23))
				unlink(in->value);
			in = in->next;
		}
		cmd = cmd->next;
	}
}
