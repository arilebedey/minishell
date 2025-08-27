#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_command
{
	char				**args;
	char				*input_file;
	char				*output_file;
	int					append_mode;
	int					heredoc_mode;
	char				*heredoc_eof;
	struct s_command	*next;
}		t_command;

// init_cmd.c

// Initialize all values of the command to 0/NULL.
void	init_cmd_values(t_command *curr_cmd);

// free_cmd.c

// Free the command linked list.
void	free_cmd_list(t_command *head_cmd);

#endif
