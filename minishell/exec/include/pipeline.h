#ifndef PIPELINE_H
# define PIPELINE_H

# include "../../include/command.h"
# include "../../include/env.h"
# include "../../include/sig/sig.h"
# include "../include/exec.h"

// utils.c
int		create_pipe_if_needed(t_child_ctx *ctx);
void	fork_and_exec_child(t_command *head_cmd, t_command *cmd,
			t_env *head_env, t_child_ctx *ctx);
int		handle_parent_after_fork(pid_t pid, int *in_fd, t_child_ctx *ctx);
void	reap_async_children(pid_t last_async);

#endif
