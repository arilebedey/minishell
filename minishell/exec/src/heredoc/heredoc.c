#include "../../../include/command.h"
#include "../../../libft/libft.h"
#include "../../include/heredoc.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*generate_heredoc_filename(int index)
{
	char	*pid_str;
	char	*idx_str;
	char	*tmp;
	char	*filename;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (NULL);
	idx_str = ft_itoa(index);
	if (!idx_str)
		return (free(pid_str), NULL);
	tmp = ft_strjoin("/tmp/minishell_heredoc_", pid_str);
	free(pid_str);
	if (!tmp)
		return (free(idx_str), NULL);
	filename = ft_strjoin(tmp, idx_str);
	free(tmp);
	free(idx_str);
	return (filename);
}

static int	process_heredoc(t_infile *infile, int index)
{
	char	*line;
	int		tmp_fd;
	char	*filename;

	filename = generate_heredoc_filename(index);
	if (!filename)
		return (perror("heredoc filename"), 0);
	tmp_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (tmp_fd < 0)
		return (perror("heredoc tmpfile"), free(filename), 0);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strncmp(line, infile->value, ft_strlen(infile->value) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
	free(infile->value);
	infile->value = filename;
	infile->heredoc_mode = 0;
	return (1);
}

int	process_heredocs(t_command *head_cmd)
{
	t_command	*cmd;
	t_infile	*in;
	int			index;

	cmd = head_cmd;
	index = 0;
	while (cmd)
	{
		in = cmd->head_infile;
		while (in)
		{
			if (in->heredoc_mode)
			{
				if (!process_heredoc(in, index))
					return (0);
				index++;
			}
			in = in->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
