#ifndef CMD_H
# define CMD_H

# include "../../include/command.h"

// get_cmd.c
char	**find_path(t_env *head_env);
char	*resolve_cmd(char *cmd, t_env *head_env);

#endif
