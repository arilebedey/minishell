/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:55:26 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/04 08:37:00 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include "../../include/env.h"
#include "../../include/sig/sig.h"
#include "../include/builtins.h"
#include "../include/cmd.h"
#include "../include/exec.h"
#include "../include/heredoc.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

static int	has_empty_command(t_command *head_cmd)
{
	t_command	*cmd;

	cmd = head_cmd;
	while (cmd)
	{
		if (!cmd->head_arg)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	handle_infiles_and_validation(t_command *head_cmd)
{
	int	res;

	res = process_infiles(head_cmd);
	if (res == 0)
		return (0);
	if (res == -1)
		return (1);
	if (!validate_infiles_access(head_cmd))
	{
		cleanup_infiles(head_cmd);
		g_exit_status = 1;
		return (1);
	}
	if (has_empty_command(head_cmd))
	{
		cleanup_infiles(head_cmd);
		g_exit_status = 0;
		return (1);
	}
	return (-1);
}

int	exec_single_command(t_command *head_cmd, t_env *head_env)
{
	int	status;

	status = try_exec_builtin(head_cmd, head_env, 1);
	if (status != -1)
	{
		cleanup_infiles(head_cmd);
		g_exit_status = status;
		return (1);
	}
	return (0);
}

int	exec_pipeline_or_single(t_command *head_cmd, t_env *head_env)
{
	if (!head_cmd->next)
	{
		if (exec_single_command(head_cmd, head_env))
			return (1);
	}
	if (!exec_pipeline(head_cmd, head_env))
		return (0);
	cleanup_infiles(head_cmd);
	return (1);
}

int	exec(t_command *head_cmd, t_env *head_env)
{
	int	res;

	if (!head_cmd)
		return (1);
	res = handle_infiles_and_validation(head_cmd);
	if (res != -1)
		return (res);
	return (exec_pipeline_or_single(head_cmd, head_env));
}
