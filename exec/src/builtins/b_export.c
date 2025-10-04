/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:04:42 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/04 07:18:09 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include "../../include/builtins.h"
#include <stdio.h>
#include <stdlib.h>

static int	join_split_args(t_args *arg)
{
	t_args	*next;
	char	*joined;
	size_t	len;

	while (arg && arg->next)
	{
		len = ft_strlen(arg->value);
		if (len && arg->value[len - 1] == '=')
		{
			next = arg->next;
			joined = ft_strjoin(arg->value, next->value);
			if (!joined)
				return (perror("export join malloc"), 0);
			free(arg->value);
			arg->value = joined;
			arg->next = next->next;
			free(next->value);
			free(next);
			continue ;
		}
		arg = arg->next;
	}
	return (1);
}

static int	handle_export_no_args(t_env *head_env)
{
	print_env_export(head_env);
	g_exit_status = 0;
	return (0);
}

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
	int	err;

	err = 0;
	if (!join_split_args(arg))
		return (1);
	while (arg)
	{
		err |= process_export_arg(head_env, arg->value);
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
