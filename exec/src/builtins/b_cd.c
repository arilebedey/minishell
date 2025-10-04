/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:55:51 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/04 08:58:14 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include "../../include/builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	count_args_cd(t_args *arg)
{
	int	count;

	count = 0;
	while (arg)
	{
		count++;
		arg = arg->next;
	}
	return (count);
}

char	*get_oldpwd(void)
{
	return (getcwd(NULL, 0));
}

int	change_directory(const char *path, char *oldpwd)
{
	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

static char	*get_cd_target(t_command *cmd, t_env *head_env)
{
	int		argc;
	char	*target;

	argc = count_args_cd(cmd->head_arg);
	if (argc < 2)
	{
		target = get_env_value(head_env, "HOME");
		if (!target)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			g_exit_status = 1;
			return (NULL);
		}
	}
	else
		target = cmd->head_arg->next->value;
	return (target);
}

int	builtin_cd(t_command *cmd, t_env *head_env)
{
	char	*oldpwd;
	char	*target;

	oldpwd = get_oldpwd();
	if (!oldpwd)
		return (1);
	target = get_cd_target(cmd, head_env);
	if (!target)
		return (free(oldpwd), 1);
	if (change_directory(target, oldpwd))
		return (1);
	if (update_env_vars(head_env, oldpwd))
		return (1);
	free(oldpwd);
	g_exit_status = 0;
	return (0);
}
