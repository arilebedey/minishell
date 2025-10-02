/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_exec_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:04:57 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/02 11:32:27 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../../libft/libft.h"
#include "../../include/builtins.h"
#include <fcntl.h>
#include <unistd.h>

static int	exec_builtin_function(t_command *cmd, t_env *head_env,
		int is_parent)
{
	if (!ft_strncmp(cmd->head_arg->value, "echo", 5))
		return (builtin_echo(cmd, head_env));
	else if (!ft_strncmp(cmd->head_arg->value, "cd", 3))
		return (builtin_cd(cmd, head_env));
	else if (!ft_strncmp(cmd->head_arg->value, "pwd", 4))
		return (builtin_pwd());
	else if (!ft_strncmp(cmd->head_arg->value, "export", 7))
		return (builtin_export(cmd, head_env));
	else if (!ft_strncmp(cmd->head_arg->value, "unset", 6))
		return (builtin_unset(cmd, &head_env));
	else if (!ft_strncmp(cmd->head_arg->value, "env", 4))
		return (builtin_env(cmd, head_env));
	else if (!ft_strncmp(cmd->head_arg->value, "exit", 5))
		return (builtin_exit(cmd, head_env, is_parent));
	return (-1);
}

int	try_exec_builtin(t_command *cmd, t_env *head_env, int is_parent)
{
	int	fds[2];
	int	status;

	if (!cmd || !cmd->head_arg)
		return (-1);
	fds[0] = -1;
	fds[1] = -1;
	if (is_parent && cmd->head_outfile)
	{
		if (!setup_parent_redirections(cmd, fds))
		{
			restore_fds(fds);
			return (1);
		}
	}
	status = exec_builtin_function(cmd, head_env, is_parent);
	if (is_parent && (fds[0] >= 0 || fds[1] >= 0))
		restore_fds(fds);
	return (status);
}
