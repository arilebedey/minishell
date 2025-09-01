#ifndef BUILD_H
# define BUILD_H

# include "../../include/command.h"

// build_handler.c

// Handle a single arg.
// If failed, prints error msg and returns 0.
int		handle_arg(t_token *curr_tk, t_command *curr_cmd);
// Handle in file
// If failed, prints error msg and returns 0.
int		handle_in_file(t_token *curr_tk, t_command *curr_cmd);
// Handle heredoc
// If failed, prints error msg and returns 0.
int		handle_heredoc(t_token *curr_tk, t_command *curr_cmd);
// Handle out file.
// If failed, prints error msg and returns 0.
int		handle_out_file(t_token *curr_tk, t_command *curr_cmd);
// Handle pipe. Creates new command.
// If failed, prints error msg and returns 0.
int		handle_pipe(t_token *curr_tk, t_command **ref_curr_cmd);

// build_error.c

// Should be called if parse error before return
// Returns 0
int		parse_exit(const char c, t_command *head_cmd);
// Prints parse error msg in stderr.
void	print_parse_error(const char c);

#endif