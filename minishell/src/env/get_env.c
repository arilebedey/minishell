#include "../../libft/libft.h"
#include "../../include/env.h"

char	*get_env_value(t_env *head_env, const char *key)
{
	t_env	*curr_env;
	size_t	len_key;

	len_key = ft_strlen(key);
	curr_env = head_env;
	while (curr_env)
	{
		if (!ft_strncmp(curr_env->key, key, len_key))
			return (curr_env->value);
		curr_env = curr_env->next;
	}
	return (NULL);
}
