#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../include/command.h"
# include "../../include/env.h"

// builtins.c
int	is_builtin(t_command *cmd);
int	exec_builtin(t_command *cmd, t_env *head_env, int is_parent);

// exit.c
int	builtin_exit(t_command *cmd, int is_parent);

// helpers.c
int	is_numeric(const char *s);

#endif
