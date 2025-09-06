#include "../../include/command.h"
#include "../../include/env.h"
#include "../../include/sig/sig.h"
#include "../include/builtins.h"
#include "../include/cmd.h"
#include "../include/exec.h"
#include "../include/heredoc.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	exec(t_command *head_cmd, t_env *head_env)
{
	int	res;

	if (!head_cmd)
		return (1);
	if (!head_cmd->next && is_builtin(head_cmd))
	{
		g_exit_status = exec_builtin(head_cmd, head_env, 1);
		return (1);
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
