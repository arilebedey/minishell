/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_exec_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:04:57 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/02 08:45:58 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include "../../include/builtins.h"

int	try_exec_builtin(t_command *cmd, t_env *head_env, int is_parent)
{
	if (!cmd->head_arg || !cmd->head_arg->value)
		return (-1);
	if (!ft_strncmp(cmd->head_arg->value, "exit", 5))
		return (builtin_exit(cmd, head_env, is_parent));
	if (!ft_strncmp(cmd->head_arg->value, "cd", 3))
		return (builtin_cd(cmd, head_env));
	if (!ft_strncmp(cmd->head_arg->value, "echo", 5))
		return (builtin_echo(cmd, head_env));
	if (!ft_strncmp(cmd->head_arg->value, "env", 4))
		return (builtin_env(cmd, head_env));
	if (!ft_strncmp(cmd->head_arg->value, "export", 7))
		return (builtin_export(cmd, head_env));
	if (!ft_strncmp(cmd->head_arg->value, "pwd", 4))
		return (builtin_pwd());
	if (!ft_strncmp(cmd->head_arg->value, "unset", 6))
		return (builtin_unset(cmd, &head_env));
	return (-1);
}
