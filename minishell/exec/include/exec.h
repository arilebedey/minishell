#ifndef EXEC_H
# define EXEC_H

# include "../../include/command.h"
# include "../../include/env.h"

// exec.c

// Main exec function.
int	exec(t_command *head_cmd, t_env *head_env);

#endif