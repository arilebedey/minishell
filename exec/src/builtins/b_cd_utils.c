/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:56:47 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/02 11:55:26 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/env.h"
#include "../../../libft/libft.h"
#include "../../include/builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	add_new_env_var(t_env **head_env, const char *key,
		const char *value)
{
	char	*new_key;
	char	*new_val;

	new_key = ft_strdup(key);
	new_val = ft_strdup(value);
	if (!new_key || !new_val)
	{
		perror("cd: malloc");
		free(new_key);
		free(new_val);
		return (1);
	}
	if (append_new_env(head_env, new_key, new_val))
		return (1);
	return (0);
}

int	update_env_var(t_env *head_env, const char *key, const char *value)
{
	t_env	*var;

	var = find_env(head_env, key);
	if (!var)
		return (add_new_env_var(&head_env, key, value));
	free(var->value);
	var->value = ft_strdup(value);
	if (!var->value)
	{
		perror("cd: malloc");
		return (1);
	}
	return (0);
}

int	update_pwd_and_oldpwd(t_env *head_env, const char *oldpwd)
{
	char	*cwd;
	int		ret;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd: getcwd");
		return (1);
	}
	ret = 0;
	if (oldpwd)
	{
		if (update_env_var(head_env, "OLDPWD", oldpwd))
			ret = 1;
	}
	if (update_env_var(head_env, "PWD", cwd))
		ret = 1;
	free(cwd);
	return (ret);
}
