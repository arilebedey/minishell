#include "../../../include/command.h"
#include "../../../libft/libft.h"
#include "../../include/heredoc.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	process_infiles(t_command *head_cmd)
{
	t_command	*cmd;
	int			index;
	int			fd;
	char		*filename;

	cmd = head_cmd;
	index = 0;
	while (cmd)
	{
		fd = open_temp_infile(&filename, index++);
		if (fd < 0)
			return (0);
		if (write_heredocs_to_file(cmd, fd))
		{
			close(fd);
			replace_first_heredoc_with_file(cmd, filename);
		}
		else
		{
			close(fd);
			free(filename);
		}
		cmd = cmd->next;
	}
	return (1);
}

void	cleanup_infiles(t_command *head_cmd)
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
