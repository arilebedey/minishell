/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:56:47 by alebedev          #+#    #+#             */
/*   Updated: 2025/09/11 13:02:39 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/env.h"
#include "../../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static t_env	*find_env(t_env *head_env, const char *key)
{
	while (head_env)
	{
		if (!ft_strncmp(head_env->key, key, ft_strlen(key) + 1))
			return (head_env);
		head_env = head_env->next;
	}
	return (NULL);
}

int	update_env_var(t_env *head_env, const char *key, const char *value)
{
	t_env	*var;

	var = find_env(head_env, key);
	if (!var)
		return (0);
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
