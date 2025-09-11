/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:04:07 by alebedev          #+#    #+#             */
/*   Updated: 2025/09/11 13:04:39 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include "../../include/builtins.h"
#include <stdlib.h>
#include <unistd.h>

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

int	validate_exit_args(t_command *cmd, int argc)
{
	long	code;

	if (!is_numeric(cmd->head_arg->next->value))
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		exit(2);
	}
	code = simple_atol(cmd->head_arg->next->value);
	if (argc > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		g_exit_status = 1;
		return (1);
	}
	exit((unsigned char)code);
	return (0);
}

int	builtin_exit(t_command *cmd, int is_parent)
{
	int	argc;

	if (is_parent)
		ft_printf("exit\n");
	argc = count_args(cmd->head_arg);
	if (argc == 1)
		exit(g_exit_status);
	if (argc >= 2)
		return (validate_exit_args(cmd, argc));
	return (0);
}
