#include "../../include/env.h"
#include "../../libft/libft.h"
#include <malloc.h>

static int	get_first_equal_index(char *s);

t_env	*init_env_list(char **envp)
{
	int		i;
	int		first_equal_index;
	t_env	*head_env;
	t_env	*current_env;

	i = -1;
	head_env = malloc(sizeof(t_env));
	if (!head_env)
		return (perror("head_env malloc"), NULL);
	current_env = head_env;
	while (envp[++i])
	{
		first_equal_index = get_first_equal_index(envp[i]);
		current_env->key = ft_substr(envp[i], 0, first_equal_index);
		current_env->value = ft_substr(envp[i], first_equal_index + 1, \
			ft_strlen(envp[i] + first_equal_index + 1));
		if (envp[i + 1])
		{
			current_env->next = malloc(sizeof(t_env));
			if (!current_env->next)
				return (perror("env malloc"), free_env_list(head_env), NULL);
			current_env = current_env->next;
		}
	}
	current_env->next = NULL;
	return (head_env);
}

// Returns the index of the first '=' in the string s
// Returns -1 if no '=' have been found
static int	get_first_equal_index(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			return (i);
	}
	return (-1);
}
