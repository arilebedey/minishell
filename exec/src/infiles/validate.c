/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:07:26 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/04 08:14:22 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/error.h"
#include "../../../libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	print_file_error(const char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)filename, 2);
	if (errno == ENOENT)
		print_error(": No such file or directory");
	else if (errno == EACCES)
		print_error(": Permission denied");
	else
		print_error(": error opening file");
}

static int	open_and_validate_infile(t_infile *in, int *cmd_has_error,
		int *has_error)
{
	int	fd;

	fd = open(in->value, O_RDONLY);
	if (fd < 0)
	{
		if (!(*cmd_has_error))
		{
			print_file_error(in->value);
			*cmd_has_error = 1;
			*has_error = 1;
		}
		return (0);
	}
	close(fd);
	return (1);
}

static void	process_infiles(t_command *cmd, int *has_error, int *cmd_has_error)
{
	t_infile	*in;

	in = cmd->head_infile;
	while (in)
	{
		if (!in->heredoc_mode)
			open_and_validate_infile(in, cmd_has_error, has_error);
		in = in->next;
	}
}

static int	validate_command_infiles(t_command *cmd, int *has_error)
{
	int	cmd_has_error;

	cmd_has_error = 0;
	process_infiles(cmd, has_error, &cmd_has_error);
	return (!cmd_has_error);
}

int	validate_infiles_access(t_command *head_cmd)
{
	t_command	*cmd;
	int			has_error;

	has_error = 0;
	cmd = head_cmd;
	while (cmd)
	{
		validate_command_infiles(cmd, &has_error);
		cmd = cmd->next;
	}
	return (!has_error);
}
