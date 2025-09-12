/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:07:38 by alebedev          #+#    #+#             */
/*   Updated: 2025/09/11 13:09:01 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include "../../include/heredoc.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	replace_heredoc_with_file(t_infile *in, char *filename)
{
	if (in->value)
		free(in->value);
	in->value = filename;
	in->heredoc_mode = 0;
	return (1);
}

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

void	heredoc_sigint(int signum)
{
	(void)signum;
	g_exit_status = 130;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 1);
}

int	write_heredocs_to_file(t_command *cmd, int fd, char *filename)
{
	t_infile	*in;
	int			has_heredoc;

	(void)filename;
	in = cmd->head_infile;
	has_heredoc = 0;
	while (in)
	{
		if (in->heredoc_mode)
		{
			has_heredoc = 1;
			if (!write_heredoc_to_fd(in, fd, filename, cmd))
				return (0);
		}
		in = in->next;
	}
	return (has_heredoc);
}
