#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_args
{
	char	*value;
	struct s_args	*next;
}		t_args;

typedef struct s_command
{
	t_args				*head_arg;
	char				*input_file;
	char				*output_file;
	int					append_mode;
	int					heredoc_mode;
	char				*heredoc_eof;
	struct s_command	*next;
}		t_command;

// command.c

// Returns a new command with all values init to 0/NULL.
// If failed, returns NULL pointer.
t_command	*init_cmd(void);
// Add a new arg to the args list.
int			add_arg(t_args **ref_head_arg, char *value);

// free_cmd.c

// Free the command linked list.
void		free_cmd_list(t_command *head_cmd);

#endif
