#include "../../exec/include/builtins.h"
#include "../../include/command.h"
#include "../../include/env.h"
#include "../../include/sig/sig.h"
#include "../include/cmd.h"
#include "../include/exec.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	exec_command(t_command *cmd, t_env *head_env)
{
	char	**argv;
	char	**envp;
	char	*resolved;
	int		status;

	if (!cmd->head_arg)
		exit(0);
	if (is_builtin(cmd))
	{
		status = exec_builtin(cmd, head_env, 0);
		exit(status);
	}
	argv = args_to_argv(cmd->head_arg);
	if (!argv)
		exit(1);
	envp = env_to_envp(head_env);
	if (!envp)
		return (free_argv(argv), exit(1));
	setup_redirections(cmd);
	resolved = resolve_cmd(argv[0], head_env);
	if (!resolved)
	{
		perror(argv[0]);
		free_argv(argv);
		free_envp(envp);
		exit(127);
	}
	free(argv[0]);
	argv[0] = resolved;
	execve(argv[0], argv, envp);
	perror(argv[0]);
	free_argv(argv);
	free_envp(envp);
	exit(127);
}
