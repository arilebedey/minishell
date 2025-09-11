/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:04:51 by alebedev          #+#    #+#             */
/*   Updated: 2025/09/11 13:04:51 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/env.h"
#include "../../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_env	*find_env(t_env *head_env, const char *key)
{
	while (head_env)
	{
		if (!ft_strncmp(head_env->key, key, ft_strlen(key) + 1))
			return (head_env);
		head_env = head_env->next;
	}
	return (NULL);
}

int	is_valid_identifier(const char *s)
{
	size_t	i;

	if (!s || !*s || ft_isdigit(*s) || *s == '=')
		return (0);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_identifier_error(const char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	append_new_env(t_env **head_env, char *key, char *value)
{
	t_env	*last;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("export malloc"), 1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!*head_env)
	{
		*head_env = new;
		return (0);
	}
	last = *head_env;
	while (last->next)
		last = last->next;
	last->next = new;
	return (0);
}

void	print_env_export(t_env *head_env)
{
	while (head_env)
	{
		if (head_env->value)
		{
			ft_printf("export %s=\"%s\"\n", head_env->key, head_env->value);
		}
		else
			ft_printf("export %s\n", head_env->key);
		head_env = head_env->next;
	}
}
