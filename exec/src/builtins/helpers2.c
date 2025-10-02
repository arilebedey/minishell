/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:04:54 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/02 11:24:10 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include <fcntl.h>
#include <unistd.h>

static int	redirect_infiles(t_infile *in)
{
	int	fd;

	while (in)
	{
		fd = open(in->value, O_RDONLY);
		if (fd < 0)
			return (0);
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			close(fd);
			return (0);
		}
		close(fd);
		in = in->next;
	}
	return (1);
}

static int	redirect_outfiles(t_outfile *out)
{
	int	fd;
	int	flags;

	while (out)
	{
		flags = O_CREAT | O_WRONLY;
		if (out->append_mode)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(out->value, flags, 0644);
		if (fd < 0)
			return (0);
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			close(fd);
			return (0);
		}
		close(fd);
		out = out->next;
	}
	return (1);
}

int	setup_parent_redirections(t_command *cmd, int *saved_fds)
{
	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	if (saved_fds[0] < 0 || saved_fds[1] < 0)
		return (0);
	if (!redirect_infiles(cmd->head_infile))
		return (0);
	if (!redirect_outfiles(cmd->head_outfile))
		return (0);
	return (1);
}

void	restore_fds(int *saved_fds)
{
	if (saved_fds[0] >= 0)
	{
		dup2(saved_fds[0], STDIN_FILENO);
		close(saved_fds[0]);
	}
	if (saved_fds[1] >= 0)
	{
		dup2(saved_fds[1], STDOUT_FILENO);
		close(saved_fds[1]);
	}
}
