#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

// init_env.c

// Return a pointer to a new env linked list.
// If failed, prints error msg and returns 0.
t_env	*init_env_list(char **envp);

// free_env.c

// Free all env elements.
void	free_env_list(t_env *head_env);

#endif