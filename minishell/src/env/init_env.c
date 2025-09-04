#include "../../include/env.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static int		get_key_and_value(char **envp, t_env *curr_env);
static t_env	*init_env_element(void);

t_env	*init_env_list(char **envp)
{
	t_env	*head_env;
	t_env	*curr_env;

	head_env = init_env_element();
	if (!head_env)
		return (perror("head_env malloc"), NULL);
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

// Set key and value for curr_env.
// If failed, prints error msg and returns 0.
static int	get_key_and_value(char **envp, t_env *curr_env)
{
	char	*ptr_equal;
	char	*SHLVL_value;
	int		SHLVL_int;

	ptr_equal = ft_strchr(*envp, '=');
	curr_env->key = ft_substr(*envp, 0, ptr_equal - *envp);
	if (!curr_env->key)
		return (perror("key_malloc"), 0);
	if (!ft_strncmp(curr_env->key, "SHLVL", 10))
	{
		SHLVL_value = getenv("SHLVL");
		if (!SHLVL_value)
			curr_env->value = ft_strdup("1");
		else
		{
			SHLVL_int = ft_atoi(SHLVL_value);
			SHLVL_int++;
			curr_env->value = ft_itoa(SHLVL_int);
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
