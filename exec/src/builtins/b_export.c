/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:04:42 by alebedev          #+#    #+#             */
/*   Updated: 2025/09/11 13:04:42 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include "../../include/builtins.h"
#include <stdio.h>
#include <stdlib.h>

static int	handle_export_no_args(t_env *head_env)
{
	print_env_export(head_env);
	g_exit_status = 0;
	return (0);
}

static char	*try_join_split_value(t_args **arg)
{
	char	*joined;
	char	*eq;

	eq = ft_strchr((*arg)->value, '=');
	joined = NULL;
	if (eq && eq[1] == '\0' && (*arg)->next)
	{
		joined = ft_strjoin((*arg)->value, (*arg)->next->value);
		if (joined)
			*arg = (*arg)->next;
	}
	return (joined);
}

// Only uses functions from _setvar and _utils
static int	process_export_arg(t_env *head_env, char *param)
{
	if (!is_valid_identifier(param))
	{
		print_identifier_error(param);
		return (1);
	}
	else if (set_variable(head_env, param))
		return (1);
	return (0);
}

static int	handle_export_args(t_args *arg, t_env *head_env)
{
	int		err;
	char	*param;
	char	*joined;

	err = 0;
	while (arg)
	{
		param = arg->value;
		joined = try_join_split_value(&arg);
		if (!joined && ft_strchr(param, '=') && arg->next && ft_strchr(param,
				'=')[1] == '\0')
		{
			perror("export");
			return (1);
		}
		if (joined)
			param = joined;
		err |= process_export_arg(head_env, param);
		free(joined);
		arg = arg->next;
	}
	return (err);
}

int	builtin_export(t_command *cmd, t_env *head_env)
{
	t_args	*arg;
	int		err;

	arg = cmd->head_arg;
	if (arg)
		arg = arg->next;
	if (!arg)
		return (handle_export_no_args(head_env));
	err = handle_export_args(arg, head_env);
	g_exit_status = err;
	return (err);
}
