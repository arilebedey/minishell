#include "../../../include/env.h"
#include "../../../libft/libft.h"
#include "../../include/builtins.h"
#include <stdio.h>
#include <stdlib.h>

static int	parse_key_value(const char *arg, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
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

static int	update_existing_var(t_env *var, char *key, char *value, int has_eq)
{
	if (has_eq)
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
	int		has_eq;

	if (parse_key_value(arg, &key, &value))
		return (1);
	has_eq = (ft_strchr(arg, '=') != NULL);
	var = find_env(head_env, key);
	if (var)
		return (update_existing_var(var, key, value, has_eq));
	return (append_new_env(&head_env, key, value));
}
