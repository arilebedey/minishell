#ifndef PIPELINE_H
# define PIPELINE_H

# include "../../include/command.h"
# include "../../include/env.h"
# include "../../include/sig/sig.h"
# include "../include/exec.h"

// utils.c
int		create_pipe_if_needed(int need_pipe, int pipefd[2]);
void	fork_and_exec_child(t_command *cmd, t_env *head_env, t_child_ctx *ctx);
void	update_exit_status(int wstatus);
int		handle_parent_after_fork(pid_t pid, int *in_fd, int need_pipe,
			int pipefd[2]);
void	reap_async_children(pid_t last_async);

#endif
