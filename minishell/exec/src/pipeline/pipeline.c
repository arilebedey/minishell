#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../include/cmd.h"
#include "../../include/exec.h"
#include "../../include/pipeline.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t	exec_single_command_in_pipeline(t_command *cmd, t_env *head_env,
		int *in_fd)
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
		fork_and_exec_child(cmd, head_env, &ctx);
	return (handle_parent_after_fork(pid, in_fd, &ctx));
}

int	exec_pipeline(t_command *cmd, t_env *head_env)
{
	int		in_fd;
	pid_t	last_async;
	pid_t	curr_pid;

	in_fd = STDIN_FILENO;
	last_async = -1;
	while (cmd)
	{
		curr_pid = exec_single_command_in_pipeline(cmd, head_env, &in_fd);
		if (curr_pid == -1 && cmd->next == NULL && in_fd == -1)
			return (0);
		if (cmd->next == NULL)
			last_async = curr_pid;
		cmd = cmd->next;
	}
	reap_async_children(last_async);
	return (1);
}
