#ifndef EXEC_H
# define EXEC_H

# include "command.h"
# include "env.h"

// Main exec function
int		exec(t_command *head_cmd, t_env *head_env);

// Convert env list to envp
char	**env_to_envp(t_env *head_env);
void	free_envp(char **envp);

#endif
