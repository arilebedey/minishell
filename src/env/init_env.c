/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:01:29 by agense            #+#    #+#             */
/*   Updated: 2025/09/30 14:48:05 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int		init_head_env(t_env **ref_head_env);
static int		get_key_and_value(char **envp, t_env *curr_env);
static t_env	*init_env_element(void);
static int		init_env_without_envp(t_env *head_env);

t_env	*init_env_list(char **envp)
{
	t_env	*head_env;
	t_env	*curr_env;

	if (!init_head_env(&head_env))
		return (NULL);
	if (!*envp)
	{
		if (!init_env_without_envp(head_env))
			return (free_env_list(head_env), NULL);
		return (head_env);
	}
	curr_env = head_env;
	while (++envp && *envp)
	{
		if (!get_key_and_value(envp, curr_env))
			return (free_env_list(head_env), NULL);
		if (*(envp + 1))
		{
			curr_env->next = init_env_element();
			if (!curr_env->next)
				return (perror("env malloc"), free_env_list(head_env), NULL);
			curr_env = curr_env->next;
		}
	}
	return (head_env);
}

// Initialize head env (just to save one line for norm xDDDDDDDDD)
// If failed, prints error msg and returns 0.
static int	init_head_env(t_env **ref_head_env)
{
	*ref_head_env = init_env_element();
	if (!*ref_head_env)
		return (perror("head_env malloc"), 0);
	return (1);
}

// Initialize base env in case there's no envp (env -i).
// If failed, prints error msg and returns 0.
static int	init_env_without_envp(t_env *head_env)
{
	char	*pwd;
	char	*exec_path;

	head_env->next = init_env_element();
	if (!head_env->next)
		return (perror("head_env next init"), 0);
	head_env->next->next = init_env_element();
	if (!head_env->next->next)
		return (perror("head_env next next init"), 0);
	pwd = getcwd(NULL, 0);
	exec_path = ft_strjoin(pwd, "/./minishell");
	if (!pwd)
		return (free(pwd), perror("init env path"), 0);
	head_env->key = ft_strdup("SHLVL");
	head_env->value = ft_strdup("2");
	head_env->next->key = ft_strdup("PWD");
	head_env->next->value = pwd;
	head_env->next->next->key = ft_strdup("_");
	head_env->next->next->value = exec_path;
	if (!head_env->key || !head_env->value || !head_env->next->value \
		|| !head_env->next->key || !head_env->next->next->key \
			|| !head_env->next->next->value)
		return (0);
	return (1);
}

// Set key and value for curr_env.
// If failed, prints error msg and returns 0.
static int	get_key_and_value(char **envp, t_env *curr_env)
{
	char	*ptr_equal;
	char	*shlvl_value;
	int		shlvl_int;

	ptr_equal = ft_strchr(*envp, '=');
	curr_env->key = ft_substr(*envp, 0, ptr_equal - *envp);
	if (!curr_env->key)
		return (perror("key_malloc"), 0);
	if (!ft_strncmp(curr_env->key, "SHLVL", 10))
	{
		shlvl_value = getenv("SHLVL");
		if (!shlvl_value)
			curr_env->value = ft_strdup("1");
		else
		{
			shlvl_int = ft_atoi(shlvl_value);
			shlvl_int++;
			curr_env->value = ft_itoa(shlvl_int);
		}
	}
	else
		curr_env->value = ft_strdup(ptr_equal + 1);
	if (!curr_env->value)
		return (perror("value malloc"), 0);
	return (1);
}

// Returns a new env element with all fields set to NULL.
// If failed, returns NULL pointer.
static t_env	*init_env_element(void)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = NULL;
	new_env->value = NULL;
	new_env->next = NULL;
	return (new_env);
}
