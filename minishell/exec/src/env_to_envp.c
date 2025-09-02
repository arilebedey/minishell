#include "../../include/env.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static int	env_size(t_env *head_env)
{
	int	count;

	count = 0;
	while (head_env)
	{
		count++;
		head_env = head_env->next;
	}
	return (count);
}

// Convert linked list to char **envp
char	**env_to_envp(t_env *head_env)
{
	char	**envp;
	char	*tmp;
	int		i;

	envp = malloc(sizeof(char *) * (env_size(head_env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (head_env)
	{
		tmp = ft_strjoin(head_env->key, "=");
		if (!tmp)
			return (NULL);
		envp[i] = ft_strjoin(tmp, head_env->value);
		free(tmp);
		if (!envp[i])
			return (NULL);
		i++;
		head_env = head_env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}
