/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:55:26 by alebedev          #+#    #+#             */
/*   Updated: 2025/09/11 12:55:26 by alebedev         ###   ########.fr       */
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

int	exec(t_command *head_cmd, t_env *head_env)
{
	int	res;
	int	status;

	if (!head_cmd)
		return (1);
	if (!head_cmd->next)
	{
		status = try_exec_builtin(head_cmd, head_env, 1);
		if (status != -1)
		{
			g_exit_status = status;
			return (1);
		}
	}
	res = process_infiles(head_cmd);
	if (res == 0)
		return (0);
	if (res == -1)
		return (1);
	if (!exec_pipeline(head_cmd, head_env))
		return (0);
	cleanup_infiles(head_cmd);
	return (1);
}
