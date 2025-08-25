#ifndef PARSE_H
# define PARSE_H

# include "../command.h"
# include "../env.h"

// parse.c

// Main parse function.
int	parse(const char* line, t_command *head_cmd, t_env *head_env);

#endif