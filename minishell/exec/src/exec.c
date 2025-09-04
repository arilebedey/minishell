#include "../../include/command.h"
#include "../../include/env.h"
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
	if (!head_cmd)
		return (1);
	if (!process_infiles(head_cmd))
		return (0);
	if (!exec_pipeline(head_cmd, head_env))
		return (0);
	cleanup_infiles(head_cmd);
	return (1);
}
