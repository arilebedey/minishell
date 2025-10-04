/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:07:26 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/04 07:37:38 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include "../../include/heredoc.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	process_infile_node(t_infile *in, int *idx, t_command *cmd)
{
	int		fd;
	int		ok;
	char	*filename;

	if (!in->heredoc_mode)
		return (1);
	fd = open_temp_infile(&filename, (*idx)++);
	if (fd < 0)
		return (0);
	ok = write_heredoc_to_fd(in, fd, filename, cmd);
	close(fd);
	if (!ok)
	{
		unlink(filename);
		free(filename);
		if (g_exit_status == 130)
			return (-1);
		return (0);
	}
	if (!replace_heredoc_with_file(in, filename))
		return (unlink(filename), free(filename), 0);
	return (1);
}

static int	process_command_infiles(t_command *cmd, int *idx)
{
	t_infile	*in;
	int			res;

	in = cmd->head_infile;
	while (in)
	{
		res = process_infile_node(in, idx, cmd);
		if (res <= 0)
			return (res);
		in = in->next;
	}
	return (1);
}

int	process_infiles(t_command *head_cmd)
{
	t_command	*cmd;
	int			idx;
	int			res;

	cmd = head_cmd;
	idx = 0;
	while (cmd)
	{
		res = process_command_infiles(cmd, &idx);
		if (res <= 0)
			return (res);
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
					24))
			{
				unlink(in->value);
				free(in->value);
				in->value = NULL;
			}
			in = in->next;
		}
		cmd = cmd->next;
	}
}
