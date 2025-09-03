#include "../../../include/command.h"
#include "../../../libft/libft.h"
#include "../../include/heredoc.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

// Concatenate all heredocs of a command into one temp file
int	process_cmd_heredocs(t_command *cmd, int index)
{
	t_infile	*in;
	char		*filename;
	int			fd;
	int			has_heredoc;
	t_infile	*curr;
	t_infile	*last;
	t_infile	*to_free;

	has_heredoc = 0;
	// Generate one temp file for all heredocs of this command
	filename = generate_heredoc_filename(index);
	if (!filename)
		return (perror("heredoc filename"), 0);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (perror("heredoc tmpfile"), free(filename), 0);
	// Write all heredocs sequentially into the same file
	in = cmd->head_infile;
	while (in)
	{
		if (in->heredoc_mode)
		{
			has_heredoc = 1;
			if (!write_heredoc_to_fd(in, fd))
				return (close(fd), free(filename), 0);
		}
		in = in->next;
	}
	close(fd);
	if (!has_heredoc)
		return (free(filename), 1);
	// Replace the first heredoc node with the temp file
	in = cmd->head_infile;
	while (in)
	{
		if (in->heredoc_mode)
		{
			// replace this one
			free(in->value);
			in->value = filename;
			in->heredoc_mode = 0;
			// remove all *other* heredoc nodes
			curr = in->next;
			last = in;
			while (curr)
			{
				if (curr->heredoc_mode)
				{
					to_free = curr;
					last->next = curr->next;
					curr = curr->next;
					free(to_free->value);
					free(to_free);
				}
				else
				{
					last = curr;
					curr = curr->next;
				}
			}
			break ;
		}
		in = in->next;
	}
	return (1);
}
