#include "../../include/env.h"
#include <stdlib.h>

void	free_env_list(t_env *head_env)
{
	if (!head_env)
		return ;
	if (head_env->next)
		free_env_list(head_env->next);
	free(head_env->key);
	free(head_env->value);
	free(head_env);
}
