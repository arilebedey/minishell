#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

// free_env.c

// free the env element given and all next elements.
void	free_env_list(t_env *head_env);

#endif