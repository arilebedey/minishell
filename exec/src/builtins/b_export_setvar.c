/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_setvar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:04:47 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/02 08:10:28 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/env.h"
#include "../../../libft/libft.h"
#include "../../include/builtins.h"
#include <stdio.h>
#include <stdlib.h>

static int	parse_key_value(const char *arg, char **key, char **value,
		int *append_mode)
{
	char	*eq;
	char	*plus;

	*append_mode = 0;
	eq = ft_strchr(arg, '=');
	if (eq)
	{
		plus = eq - 1;
		if (plus >= arg && *plus == '+')
		{
			*append_mode = 1;
			*key = ft_substr(arg, 0, plus - arg);
		}
		else
			*key = ft_substr(arg, 0, eq - arg);
		*value = ft_strdup(eq + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
	if (!(*key) || (eq && !(*value)))
		return (perror("export parse_key_value malloc"), 1);
	return (0);
}

static int	update_existing_var(t_env *var, char *key, char *value,
		int append_mode)
{
	char	*new_val;

	if (append_mode && var->value && value)
	{
		new_val = ft_strjoin(var->value, value);
		if (!new_val)
			return (perror("export append malloc"), free(key), free(value), 1);
		free(var->value);
		var->value = new_val;
		free(key);
		free(value);
		return (0);
	}
	if (value)
	{
		free(var->value);
		var->value = value;
	}
	else
		free(value);
	free(key);
	return (0);
}

int	set_variable(t_env *head_env, const char *arg)
{
	char	*key;
	char	*value;
	t_env	*var;
	int		append_mode;

	if (parse_key_value(arg, &key, &value, &append_mode))
		return (1);
	var = find_env(head_env, key);
	if (var)
		return (update_existing_var(var, key, value, append_mode));
	if (!value)
		value = ft_strdup("");
	return (append_new_env(&head_env, key, value));
}
