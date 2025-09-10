#include "../../../libft/libft.h"
#include "../../include/builtins.h"
#include <stdlib.h>
#include <unistd.h>

int	try_exec_builtin(t_command *cmd, t_env *head_env, int is_parent)
{
	if (!cmd->head_arg || !cmd->head_arg->value)
		return (-1);
	if (!ft_strncmp(cmd->head_arg->value, "exit", 5))
		return (builtin_exit(cmd, is_parent));
	if (!ft_strncmp(cmd->head_arg->value, "cd", 3))
		return (builtin_cd(cmd, head_env));
	if (!ft_strncmp(cmd->head_arg->value, "echo", 5))
		return (builtin_echo(cmd, head_env));
	if (!ft_strncmp(cmd->head_arg->value, "env", 4))
		return (builtin_env(cmd, head_env));
	return (-1);
}
