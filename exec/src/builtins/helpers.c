/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:04:54 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/02 07:40:52 by alebedev         ###   ########.fr       */
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

int	is_numeric(const char *s)
{
	if (!s || !*s)
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

long	simple_atol(const char *s)
{
	long	sign;
	long	res;

	sign = 1;
	res = 0;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && ft_isdigit(*s))
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res * sign);
}
