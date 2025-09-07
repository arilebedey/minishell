#include "../../../include/command.h"
#include "../../../libft/libft.h"
#include "../../include/heredoc.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
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
	char		*dup;

	in = cmd->head_infile;
	while (in)
	{
		if (in->heredoc_mode)
		{
			dup = ft_strdup(filename);
			if (!dup)
			{
				perror("heredoc malloc");
				return ;
			}
			free(in->value);
			in->value = dup;
			in->heredoc_mode = 0;
			prune_extra_heredocs(in);
			break ;
		}
		in = in->next;
	}
}

int	open_temp_infile(char **filename, int index)
{
	int	fd;

	*filename = generate_heredoc_filename(index);
	if (!*filename)
		return (perror("heredoc filename"), -1);
	fd = open(*filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (perror("heredoc tmpfile"), free(*filename), -1);
	return (fd);
}
