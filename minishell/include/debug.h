#ifndef DEBUG_H
# define DEBUG_H

# include "command.h"
# include "env.h"
# include "../parse/include/token.h"

// DEBUG MACROS
// Set these macros to 0 or 1 to disable or enable each debug functions.
// Do make fclean after setting.

# define DEBUG_ENV 0
# define DEBUG_TOKEN 0
# define DEBUG_COMMAND 1

// debug_env.c

// Prints all fields of each env variables in the list.
// Needs DEBUG_ENV macro set to 1.
void	debug_env_list(t_env *head_env);

// debug_token.c

// Prints all fields of each tokens in the list.
// Needs DEBUG_TOKEN macro set to 1.
void	debug_token_list(t_token *head_tk);

// debug_cmd.c

// Prints all fields of each commands in the list.
// Needs DEBUG_COMMAND macro set to 1.
void	debug_command_list(t_command *head_cmd);

#endif
