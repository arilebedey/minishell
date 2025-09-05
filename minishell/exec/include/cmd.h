#ifndef CMD_H
# define CMD_H

# include "../../include/command.h"
# include "../../include/env.h"

// get_cmd.c
char	**find_path(t_env *head_env);
char	*resolve_cmd(char *cmd, t_env *head_env);

// get_cmd.c
char	**find_path(t_env *head_env);
char	*resolve_cmd(char *cmd, t_env *head_env);

// exec_pipeline.c
int		exec_pipeline(t_command *cmd, t_env *head_env);

#endif
