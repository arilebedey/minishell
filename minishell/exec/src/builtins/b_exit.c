#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include "../../include/builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	builtin_exit(t_command *cmd, int is_parent)
{
	int		argc;
	t_args	*arg;
	long	code;

	argc = 0;
	arg = cmd->head_arg;
	if (is_parent)
		ft_printf("exit\n");
	while (arg)
	{
		argc++;
		arg = arg->next;
	}
	if (argc == 1)
		exit(g_exit_status);
	if (argc >= 2)
	{
		if (!is_numeric(cmd->head_arg->next->value))
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			exit(2);
		}
		code = simple_atol(cmd->head_arg->next->value);
		if (argc > 2)
		{
			ft_putendl_fd("exit: too many arguments", 2);
			g_exit_status = 1;
			return (1);
		}
		exit((unsigned char)code);
	}
	return (0);
}
