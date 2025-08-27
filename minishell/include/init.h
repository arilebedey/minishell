#ifndef INIT_H
# define INIT_H

# include "../include/env.h"
# include "../include/command.h"

// Initialize a envp linked list
// If failed, returns 0.
int	init_env_list(char **envp, t_env *head_env);

// Initialize heads of command and env linked list.
// If failed, prints error msg and returns 0.
int	init_heads(t_command **ref_head_cmd, t_env **ref_head_env);

#endif