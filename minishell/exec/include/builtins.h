#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../include/command.h"
# include "../../include/env.h"

int		try_exec_builtin(t_command *cmd, t_env *head_env, int is_parent);

// b_exit.c
int		builtin_exit(t_command *cmd, int is_parent);

// b_cd.c
int		builtin_cd(t_command *cmd, t_env *head_env);

// b_env.c
int		builtin_env(t_command *cmd, t_env *head_env);

// helpers.c
int		is_numeric(const char *s);
long	simple_atol(const char *s);

#endif
