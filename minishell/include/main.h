#ifndef MAIN_H
# define MAIN_H

# include "command.h"
# include "env.h"

// parse.c

// Main parse function.
// Returns a linked list of commmands.
// If failed, returns a NULL pointer.
t_command	*parse(const char* line, t_env *head_env);

// exec.c

// Main exec function.
int	exec(t_command *head_cmd, t_env *head_env);

#endif
