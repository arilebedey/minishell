/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:04:07 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/02 08:45:31 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/env.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include "../../include/builtins.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static void	safe_exit(t_command **ref_cmd, t_env *env, int status)
{
	if (ref_cmd && *ref_cmd)
		free_cmd_list(ref_cmd);
	if (env)
		free_env_list(env);
	rl_clear_history();
	exit(status);
}

int	count_args(t_args *arg)
{
	int	argc;

	argc = 0;
	while (arg)
	{
		argc++;
		arg = arg->next;
	}
	return (argc);
}

int	validate_exit_args(t_command *cmd, t_env *head_env, int argc)
{
	long	code;

	if (!is_numeric(cmd->head_arg->next->value))
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		safe_exit(&cmd, head_env, 2);
	}
	code = simple_atol(cmd->head_arg->next->value);
	if (argc > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		g_exit_status = 1;
		return (1);
	}
	safe_exit(&cmd, head_env, (unsigned char)code);
	return (0);
}

int	builtin_exit(t_command *cmd, t_env *head_env, int is_parent)
{
	int	argc;

	if (is_parent)
		ft_printf("exit\n");
	argc = count_args(cmd->head_arg);
	if (argc == 1)
		safe_exit(&cmd, head_env, g_exit_status);
	if (argc >= 2)
		return (validate_exit_args(cmd, head_env, argc));
	return (0);
}
