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
	if (!ft_strncmp(cmd->head_arg->value, "cd", 3))
		return (1);
	// add more builtins here later
	return (0);
}

int	exec_builtin(t_command *cmd, t_env *head_env, int is_parent)
{
	if (!cmd->head_arg || !cmd->head_arg->value)
		return (0);
	if (!ft_strncmp(cmd->head_arg->value, "exit", 5))
		return (builtin_exit(cmd, is_parent));
	if (!ft_strncmp(cmd->head_arg->value, "cd", 3))
		return (builtin_cd(cmd, head_env));
	return (0);
}
