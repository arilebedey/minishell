/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:12:35 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/04 10:16:27 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	setup_infiles(t_command *cmd)
{
	int			fd;
	t_infile	*in;

	in = cmd->head_infile;
	while (in)
	{
		fd = open(in->value, O_RDONLY);
		if (fd < 0)
		{
			perror(in->value);
			exit(1);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2 infile");
			close(fd);
			exit(1);
		}
		close(fd);
		in = in->next;
	}
}

static void	setup_outfiles(t_command *cmd)
{
	int			fd;
	t_outfile	*out;

	out = cmd->head_outfile;
	while (out)
	{
		if (out->append_mode)
			fd = open(out->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(out->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(out->value);
			exit(1);
		}
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 outfile");
			close(fd);
			exit(1);
		}
		close(fd);
		out = out->next;
	}
}

void	setup_redirections(t_command *cmd)
{
	setup_infiles(cmd);
	setup_outfiles(cmd);
}
