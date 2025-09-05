#include "../../../include/command.h"
#include "../../include/heredoc.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static void	prune_extra_heredocs(t_infile *first)
{
	t_infile	*curr;
	t_infile	*last;
	t_infile	*to_free;

	curr = first->next;
	last = first;
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
}

void	replace_first_heredoc_with_file(t_command *cmd, char *filename)
{
	t_infile	*in;

	in = cmd->head_infile;
	while (in)
	{
		if (in->heredoc_mode)
		{
			free(in->value);
			in->value = filename;
			in->heredoc_mode = 0;
			prune_extra_heredocs(in);
			break ;
		}
		in = in->next;
	}
}
