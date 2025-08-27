#ifndef PARSE_H
# define PARSE_H

# include "../../include/command.h"
# include "../../include/env.h"
# include "token.h"

// lexer.c

// Returns a linked list of token according to the line.
// If failed, prints error msg and returns a NULL pointer.
t_token		*lexer(const char *line);

// build.c

// Returns a new command linked list.
// If failed, returns a NULL pointer.
t_command	*build_command_list(t_token *head_tk);

#endif
