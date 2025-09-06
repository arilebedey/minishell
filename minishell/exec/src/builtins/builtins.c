#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include "../../include/builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	is_builtin(t_command *cmd)
{
	if (!cmd->head_arg || !cmd->head_arg->value)
		return (0);
	if (!ft_strncmp(cmd->head_arg->value, "exit", 5))
		return (1);
	// add more builtins here later
	return (0);
}

int	exec_builtin(t_command *cmd, t_env *head_env, int is_parent)
{
	(void)head_env;
	if (!cmd->head_arg || !cmd->head_arg->value)
		return (0);
	if (!ft_strncmp(cmd->head_arg->value, "exit", 5))
		return (builtin_exit(cmd, is_parent));
	return (0);
}

static long	simple_atol(const char *s)
{
	long	sign;
	long	res;

	sign = 1;
	res = 0;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && ft_isdigit(*s))
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res * sign);
}

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
