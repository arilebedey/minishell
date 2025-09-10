#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"

int	builtin_env(t_command *cmd, t_env *head_env)
{
	t_env	*curr;
	t_args	*arg;

	(void)cmd;
	arg = cmd->head_arg;
	if (arg)
		arg = arg->next;
	if (arg)
	{
		ft_putendl_fd("env: too many arguments", 2);
		g_exit_status = 1;
		return (1);
	}
	curr = head_env;
	while (curr)
	{
		ft_printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	g_exit_status = 0;
	return (0);
}
