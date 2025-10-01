/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:12:31 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/01 11:46:00 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec/include/builtins.h"
#include "../../include/command.h"
#include "../../include/env.h"
#include "../../libft/libft.h"
#include "../include/cmd.h"
#include "../include/exec.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	handle_builtin_or_exit(t_command *head_cmd, t_command *cmd,
		t_env *head_env)
{
	int	status;

	if (!cmd->head_arg)
		exit(0);
	status = try_exec_builtin(cmd, head_env, 0);
	if (status != -1)
	{
		free_cmd_list(&head_cmd);
		free_env_list(head_env);
		exit(status);
	}
}

static void	prepare_exec(t_command *cmd, t_env *head_env, char ***argv,
		char ***envp)
{
	*argv = args_to_argv(cmd->head_arg);
	if (!*argv)
		exit(1);
	*envp = env_to_envp(head_env);
	if (!*envp)
	{
		free_argv(*argv);
		exit(1);
	}
	setup_redirections(cmd);
}

static void	execute_binary(char **argv, char **envp, t_env *head_env,
		t_command *head_cmd)
{
	char	*resolved;

	resolved = resolve_cmd(argv[0], head_env);
	if (!resolved)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_argv(argv);
		free_envp(envp);
		free_env_list(head_env);
		free_cmd_list(&head_cmd);
		exit(127);
	}
	free(argv[0]);
	argv[0] = resolved;
	execve(argv[0], argv, envp);
	perror(argv[0]);
	free_argv(argv);
	free_envp(envp);
	if (errno == EACCES)
		exit(126);
	else
		exit(127);
}

void	exec_command(t_command *head_cmd, t_command *cmd, t_env *head_env)
{
	char	**argv;
	char	**envp;

	handle_builtin_or_exit(head_cmd, cmd, head_env);
	prepare_exec(cmd, head_env, &argv, &envp);
	execute_binary(argv, envp, head_env, head_cmd);
}
