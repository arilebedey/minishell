/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:55:51 by alebedev          #+#    #+#             */
/*   Updated: 2025/09/11 13:11:48 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../../include/sig/sig.h"
#include "../../include/builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	count_args(t_args *arg)
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

int	update_env_vars(t_env *head_env, char *oldpwd)
{
	if (update_pwd_and_oldpwd(head_env, oldpwd))
	{
		free(oldpwd);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	builtin_cd(t_command *cmd, t_env *head_env)
{
	int		argc;
	char	*oldpwd;

	argc = count_args(cmd->head_arg);
	if (argc < 2)
		return (1);
	oldpwd = get_oldpwd();
	if (!oldpwd)
		return (1);
	if (change_directory(cmd->head_arg->next->value, oldpwd))
		return (1);
	if (update_env_vars(head_env, oldpwd))
		return (1);
	free(oldpwd);
	g_exit_status = 0;
	return (0);
}
