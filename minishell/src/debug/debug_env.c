#include "../../include/env.h"
#include "../../include/debug.h"
#include "../../libft/libft.h"

void	debug_env_list(t_env *head_env)
{
	t_env	*curr_env;

	if (!DEBUG_ENV)
		return ;
	curr_env = head_env;
	while (curr_env)
	{
		ft_printf("\nkey: %s", curr_env->key);
		ft_printf("\nvalue: %s", curr_env->value);
		ft_printf("\n");
		curr_env = curr_env->next;
	}
	ft_printf("\n");
}
