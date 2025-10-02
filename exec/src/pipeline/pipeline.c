/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:12:06 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/02 10:38:25 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../include/cmd.h"
#include "../../include/exec.h"
#include "../../include/pipeline.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t	exec_single_command_in_pipeline(t_command *head_cmd,
		t_command *cmd, t_env *head_env, int *in_fd)
{
	pid_t		pid;
	t_child_ctx	ctx;

	ctx.in_fd = *in_fd;
	ctx.need_pipe = (cmd->next != NULL);
	if (!create_pipe_if_needed(&ctx))
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		fork_and_exec_child(head_cmd, cmd, head_env, &ctx);
	return (handle_parent_after_fork(pid, in_fd, &ctx));
}

int	exec_pipeline(t_command *head_cmd, t_env *head_env)
{
	int			in_fd;
	pid_t		last_async;
	pid_t		curr_pid;
	t_command	*cmd;

	in_fd = STDIN_FILENO;
	last_async = -1;
	cmd = head_cmd;
	while (cmd)
	{
		curr_pid = exec_single_command_in_pipeline(head_cmd, cmd, head_env,
				&in_fd);
		if (cmd->next == NULL)
			last_async = curr_pid;
		cmd = cmd->next;
	}
	if (last_async == -1)
	{
		g_exit_status = 1;
		return (0);
	}
	reap_async_children(last_async);
	return (1);
}
