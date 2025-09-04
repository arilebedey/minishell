#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../../include/sig/sig.h"
#include "../../include/cmd.h"
#include "../../include/exec.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	create_pipe_if_needed(int need_pipe, int pipefd[2])
{
	if (need_pipe && pipe(pipefd) < 0)
	{
		perror("pipe");
		return (0);
	}
	return (1);
}

void	fork_and_exec_child(t_command *cmd, t_env *head_env, t_child_ctx *ctx)
{
	if (!init_child_sigaction())
		exit(1);
	if (ctx->in_fd != STDIN_FILENO)
	{
		dup2(ctx->in_fd, STDIN_FILENO);
		close(ctx->in_fd);
	}
	if (ctx->need_pipe)
	{
		close(ctx->pipefd[0]);
		dup2(ctx->pipefd[1], STDOUT_FILENO);
		close(ctx->pipefd[1]);
	}
	exec_command(cmd, head_env);
}

void	update_exit_status(int wstatus)
{
	int	sig;

	if (WIFEXITED(wstatus))
		g_exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		sig = WTERMSIG(wstatus);
		g_exit_status = 128 + sig;
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	}
}

int	handle_parent_after_fork(pid_t pid, int *in_fd, int need_pipe,
		int pipefd[2])
{
	int	wstatus;

	if (!init_parent_sigaction())
		return (-1);
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (need_pipe)
	{
		close(pipefd[1]);
		*in_fd = pipefd[0];
		return (pid);
	}
	else
	{
		*in_fd = STDIN_FILENO;
		if (waitpid(pid, &wstatus, 0) < 0)
		{
			perror("waitpid");
			return (-1);
		}
		update_exit_status(wstatus);
	}
	return (-1);
}

void	reap_async_children(pid_t last_async)
{
	int	wstatus;

	while (last_async > 0 && waitpid(-1, &wstatus, 0) > 0)
		update_exit_status(wstatus);
}
